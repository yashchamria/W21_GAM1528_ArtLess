#include "AG_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "AG_PlayableCharacter.h"
#include "AG_ColdNites/Pickup/InventoryComponent.h"


AAG_PlayerController::AAG_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

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
		ResOptionsMenu->AddToViewport();
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

	InputComponent->BindAction("ESC", IE_Pressed, this, &AAG_PlayerController::Esc_KeyDown); 
}

void AAG_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//disable mouse input if any menu is open
	if (bPauseMenuVisible || bResOptionsMenuVisible)
	{
		bMoveToMouseCursor = false;
	}
}

///---------------------------------------Player Movement Setup----------------------------------------------------------///
void AAG_PlayerController::MoveRight()
{
	if (Player && bCanPlayerMove) { Player->MoveRight(); bCanPlayerMove = false; }
}

void AAG_PlayerController::MoveLeft()
{
	if (Player && bCanPlayerMove) { Player->MoveLeft(); bCanPlayerMove = false; }
}

void AAG_PlayerController::MoveForward()
{
	if (Player && bCanPlayerMove) { Player->MoveForward(); bCanPlayerMove = false; }
}

void AAG_PlayerController::MoveBackward()
{
	if (Player && bCanPlayerMove) { Player->MoveBackward(); bCanPlayerMove = false; }
}

//Requires an Empty function to feed on KeyRelease after Player Movement
void AAG_PlayerController::StopMove(){}

void AAG_PlayerController::MoveToMouseCursor()
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
///******************************************************************************************************************///

///---------------------------------------Inventory Setup----------------------------------------------------------///
void AAG_PlayerController::NextInventoryItem()
{
	if(Player) { Player->NextInventoryItem(); }
}

void AAG_PlayerController::PreviousInventoryItem()
{
	if (Player) { Player->PreviousInventoryItem(); }
}
///******************************************************************************************************************///


///---------------------------------------UI Setup----------------------------------------------------------///

void AAG_PlayerController::Esc_KeyDown()
{
	/*if (GetWorld()->GetMapName() != L"UEDPIE_0_MainMenu")
	{
	}*/
	TogglePauseMenu();
}


void AAG_PlayerController::ShowPauseMenu()
{
	if(PauseMenu)
	{
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		DefaultMouseCursor = EMouseCursor::Default;
		SetShowMouseCursor(true);
	}
}

void AAG_PlayerController::HidePauseMenu_Implementation()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		DefaultMouseCursor = EMouseCursor::Crosshairs;
		//SetShowMouseCursor(false);
	}
}

void AAG_PlayerController::TogglePauseMenu()
{
	if(bPauseMenuVisible)
	{
		HidePauseMenu_Implementation();
	}
	else
	{
		if(!bResOptionsMenuVisible)
		{
			//ShowPauseMenu();
			if (PauseMenu)
			{
				bPauseMenuVisible = true;
				PauseMenu->SetVisibility(ESlateVisibility::Visible);
				DefaultMouseCursor = EMouseCursor::Default;
				SetShowMouseCursor(true);
			}
		}
	}
}

void AAG_PlayerController::ShowResOptionsMenu_Implementation()
{
	if (ResOptionsMenu)
	{
		bResOptionsMenuVisible = true;
		ResOptionsMenu->SetVisibility(ESlateVisibility::Visible);

		bPauseMenuVisible = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);

		DefaultMouseCursor = EMouseCursor::Default;
		SetShowMouseCursor(true);
	}
}

void AAG_PlayerController::HideResOptionsMenu_Implementation()
{
	if (ResOptionsMenu)
	{
		bResOptionsMenuVisible = false;
		ResOptionsMenu->SetVisibility(ESlateVisibility::Hidden);

		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);

		DefaultMouseCursor = EMouseCursor::Crosshairs;
		SetShowMouseCursor(true);
	}
}

///******************************************************************************************************************///