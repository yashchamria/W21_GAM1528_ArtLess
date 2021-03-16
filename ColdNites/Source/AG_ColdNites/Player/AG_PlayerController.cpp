#include "AG_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "AG_PlayableCharacter.h"

AAG_PlayerController::AAG_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	bGamePlayInput = true;
	bUIInput = true;
	
	bCanPlayerMove = false;
}

void AAG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bPauseMenuVisible = false;
	bMainMenuVisible = false;
	bResOptionsMenuVisible = false;

	if(PauseMenuTemplate)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, PauseMenuTemplate);
		PauseMenu->AddToViewport();
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (ResOptionsMenuTemplate)
	{
		ResOptionsMenu = CreateWidget<UUserWidget>(this, ResOptionsMenuTemplate);
		ResOptionsMenu->SetVisibility(ESlateVisibility::Hidden);
	}

	//Getting the Spawned TileMap Actor from the World
	TArray<AActor*> TileMapActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);
	
	if (TileMapActor.Num() > 0)
	{
		TileMap = Cast<AAG_TileMap>(TileMapActor[0]);
	}

	//Getting the current player Actor
	Player = Cast<AAG_PlayableCharacter>(GetPawn());
}

void AAG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//if (bGamePlayInput)
	{
		InputComponent->BindAction("MoveForward", IE_Pressed, this, &AAG_PlayerController::MoveForward);
		InputComponent->BindAction("MoveForward", IE_Released, this, &AAG_PlayerController::StopMove);

		InputComponent->BindAction("MoveBackward", IE_Pressed, this, &AAG_PlayerController::MoveBackward);
		InputComponent->BindAction("MoveBackward", IE_Released, this, &AAG_PlayerController::StopMove);

		InputComponent->BindAction("MoveRight", IE_Pressed, this, &AAG_PlayerController::MoveRight);
		InputComponent->BindAction("MoveRight", IE_Released, this, &AAG_PlayerController::StopMove);

		InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AAG_PlayerController::MoveLeft);
		InputComponent->BindAction("MoveLeft", IE_Released, this, &AAG_PlayerController::StopMove);

		InputComponent->BindAction("SetDestination", IE_Pressed, this, &AAG_PlayerController::MoveToMouseCursor);
		InputComponent->BindAction("SetDestination", IE_Released, this, &AAG_PlayerController::StopMove);

		InputComponent->BindAction("Next", IE_Pressed, this, &AAG_PlayerController::NextInventoryItem);
		InputComponent->BindAction("Prev", IE_Pressed, this, &AAG_PlayerController::PreviousInventoryItem);
	}

	//if(bUIInput)
	{
		InputComponent->BindAction("ESC", IE_Pressed, this, &AAG_PlayerController::OnEscKeyPressed);
	}
}

void AAG_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

///---------------------------------------Player Movement Setup----------------------------------------------------------///

void AAG_PlayerController::EnableGamePlayInput(bool GamePlayInput)
{
	bGamePlayInput = GamePlayInput;
}

void AAG_PlayerController::MoveRight()
{
	if(bGamePlayInput)
	{
		if (Player && bCanPlayerMove)
		{
			Player->MoveRight();
			bCanPlayerMove = false;
		}
	}
}

void AAG_PlayerController::MoveLeft()
{
	if (bGamePlayInput)
	{
		if (Player && bCanPlayerMove)
		{
			Player->MoveLeft();
			bCanPlayerMove = false;
		}
	}
}

void AAG_PlayerController::MoveForward()
{
	if (bGamePlayInput)
	{
		if (Player && bCanPlayerMove)
		{
			Player->MoveForward();
			bCanPlayerMove = false;
		}
	}
}

void AAG_PlayerController::MoveBackward()
{
	if (bGamePlayInput)
	{
		if (Player && bCanPlayerMove)
		{
			Player->MoveBackward();
			bCanPlayerMove = false;
		}
	}
}

//Requires an Empty function to feed on KeyRelease after Player Movement
void AAG_PlayerController::StopMove(){}

void AAG_PlayerController::MoveToMouseCursor()
{
	if (bGamePlayInput)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit && Hit.Actor->ActorHasTag("AG_Tile") && TileMap && Player && bCanPlayerMove)
		{
			FIntPoint CurrentTileCoord = TileMap->GetTileCoord(Player->GetActorLocation());
			FIntPoint TargetTileCoord = TileMap->GetTileCoord(Hit.ImpactPoint);

			bool IsTileNeighbouring = TileMap->IsTileNeighbouring(TargetTileCoord, Player->GetActorLocation(), Player->GetActorForwardVector(), Player->GetActorRightVector());

			if (IsTileNeighbouring)
			{
				FVector TargetTileWorldPosition = TileMap->GetTileWorldPosition(TargetTileCoord);
				FVector CurrentTileWorldPosition = TileMap->GetTileWorldPosition(CurrentTileCoord);
				FVector TargetDirection = TargetTileWorldPosition - CurrentTileWorldPosition;

				Player->MoveTile(TargetDirection);
				bCanPlayerMove = false;
			}
		}
	}
}

///---------------------------------------Inventory Setup----------------------------------------------------------///

void AAG_PlayerController::NextInventoryItem()
{
	if (bGamePlayInput)
	{
		if (Player)
		{
			Player->NextInventoryItem();
		}
	}
}

void AAG_PlayerController::PreviousInventoryItem()
{
	if (bGamePlayInput)
	{
		if (Player)
		{
			Player->PreviousInventoryItem();
		}
	}
}

///---------------------------------------UI Setup----------------------------------------------------------///

void AAG_PlayerController::EnableUIInput(bool UIInput)
{
	bUIInput = UIInput;
}

void AAG_PlayerController::OnEscKeyPressed()
{
	if(bUIInput)
	{
		TogglePauseMenu();
	}
}

void AAG_PlayerController::TogglePauseMenu()
{
	if(!bPauseMenuVisible && !bResOptionsMenuVisible)
	{
		ShowPauseMenu();
	}
	else
	{
		HidePauseMenu();
	}
}


void AAG_PlayerController::ShowPauseMenu()
{
	if(PauseMenu)
	{
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAG_PlayerController::HidePauseMenu()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAG_PlayerController::ToggleResOptionsMenu()
{
	if(!bResOptionsMenuVisible)
	{
		ShowResOptionsMenu();
	}
	else
	{
		HideResOptionsMenu();
	}
}

void AAG_PlayerController::ShowResOptionsMenu()
{
	if (ResOptionsMenu)
	{
		bPauseMenuVisible = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);

		bResOptionsMenuVisible = true;
		ResOptionsMenu->AddToViewport();
		ResOptionsMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAG_PlayerController::HideResOptionsMenu()
{
	if (ResOptionsMenu)
	{
		bResOptionsMenuVisible = false;
		ResOptionsMenu->RemoveFromParent();
		ResOptionsMenu->SetVisibility(ESlateVisibility::Hidden);

		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
	}
}