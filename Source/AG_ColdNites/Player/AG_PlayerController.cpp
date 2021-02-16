#include "AG_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "../TileMap/AG_TileMap.h"
#include "AG_PlayableCharacter.h"
#include "../Pickup/InventoryComponent.h"


AAG_PlayerController::AAG_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AAG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bPauseMenuVisible = false;
	bMainMenuVisible = false;
	bResOptionsMenuVisible = false;
	
	if (PauseMenuOverlayAsset)
	{
		PauseMenuOverlay = CreateWidget<UUserWidget>(this, PauseMenuOverlayAsset);
		PauseMenuOverlay->AddToViewport();
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ResOptionsMenuOverlayAsset)
	{
		ResOptionsMenuOverlay = CreateWidget<UUserWidget>(this, ResOptionsMenuOverlayAsset);
		ResOptionsMenuOverlay->AddToViewport();
		ResOptionsMenuOverlay->SetVisibility(ESlateVisibility::Hidden);
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
	InputComponent->BindAction("SetDestination", IE_Released, this, &AAG_PlayerController::StopMove);//OnSetDestinationReleased);

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

	if (bMoveToMouseCursor)
	{
		//MoveToMouseCursor();
	}
}

///---------------------------------------Player Movement Setup----------------------------------------------------------///
void AAG_PlayerController::MoveRight()
{
	if (Player) { Player->MoveRight(); }
}

void AAG_PlayerController::MoveLeft()
{
	if (Player) { Player->MoveLeft(); }
}

void AAG_PlayerController::MoveForward()
{
	if (Player) { Player->MoveForward(); }
}

void AAG_PlayerController::MoveBackward()
{
	if (Player) { Player->MoveBackward(); }
}


void AAG_PlayerController::StopMove()
{
}

void AAG_PlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit && Hit.Actor->ActorHasTag("AG_Tile") && TileMap && Player)
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
			//SetNewMoveDestination(TargetDestination);
		}
	}
}

//void AAG_PlayerController::SetNewMoveDestination(const FVector DestLocation)
//{
//	if (Player)
//	{
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("MyPawn = NULL"));
//	}
//}
//
//void AAG_PlayerController::OnSetDestinationPressed()
//{
//	bMoveToMouseCursor = true;
//}
//
//void AAG_PlayerController::OnSetDestinationReleased()
//{
//	bMoveToMouseCursor = false;
//}
///---------------------------------------Player Movement Setup----------------------------------------------------------///

///---------------------------------------Inventory Setup----------------------------------------------------------///
void AAG_PlayerController::NextInventoryItem()
{
	if(Player) { Player->NextInventoryItem(); }
}

void AAG_PlayerController::PreviousInventoryItem()
{
	if (Player) { Player->PreviousInventoryItem(); }
}
///---------------------------------------Inventory Setup----------------------------------------------------------///


///---------------------------------------UI Setup----------------------------------------------------------///

void AAG_PlayerController::Esc_KeyDown()
{
	if (GetWorld()->GetMapName() != L"UEDPIE_0_MainMenu")
	{
		TogglePauseMenu();
	}
}


void AAG_PlayerController::ShowPauseMenu()
{
	if(PauseMenuOverlay)
	{
		bPauseMenuVisible = true;
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Visible);
		DefaultMouseCursor = EMouseCursor::Default;
		SetShowMouseCursor(true);
	}
}

void AAG_PlayerController::HidePauseMenu_Implementation()
{
	if (PauseMenuOverlay)
	{
		bPauseMenuVisible = false;
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Hidden);
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
			ShowPauseMenu();
		}
	}
}

void AAG_PlayerController::ShowResOptionsMenu_Implementation()
{
	if (ResOptionsMenuOverlay)
	{
		bResOptionsMenuVisible = true;
		ResOptionsMenuOverlay->SetVisibility(ESlateVisibility::Visible);

		bPauseMenuVisible = false;
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Hidden);

		DefaultMouseCursor = EMouseCursor::Default;
		SetShowMouseCursor(true);
	}
}

void AAG_PlayerController::HideResOptionsMenu_Implementation()
{
	if (ResOptionsMenuOverlay)
	{
		bResOptionsMenuVisible = false;
		ResOptionsMenuOverlay->SetVisibility(ESlateVisibility::Hidden);

		bPauseMenuVisible = true;
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Visible);

		DefaultMouseCursor = EMouseCursor::Crosshairs;
		SetShowMouseCursor(true);
	}
}

///---------------------------------------UI Setup----------------------------------------------------------///