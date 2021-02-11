// Fill out your copyright notice in the Description page of Project Settings.

#include "AG_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "AG_PlayerCharacter.h"
#include "../TileMap/AG_Tile.h"
#include "../TileMap/AG_TileMap.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "../Pickup/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

void AAG_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	//disable mouse input if any menu is open
	if(bPauseMenuVisible || bResOptionsMenuVisible)
	{
		bMoveToMouseCursor = false;
	}
	
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AAG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AAG_PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AAG_PlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Next", IE_Pressed, this, &AAG_PlayerController::NextInventoryItem);
	InputComponent->BindAction("Prev", IE_Pressed, this, &AAG_PlayerController::PreviousInventoryItem);

	InputComponent->BindAction("ESC", IE_Pressed, this, &AAG_PlayerController::Esc_KeyDown);
}

void AAG_PlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit && Hit.Actor->ActorHasTag("AG_Tile"))
	{
		AAG_TileMap* TileMap = nullptr;
		
		for (TActorIterator<AActor> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
		{
			if (ActorIterator->ActorHasTag("AG_TileMap"))
			{
				TileMap = Cast<AAG_TileMap>(*ActorIterator);
			}
		}
		
		if (TileMap)
		{
			FIntPoint TilePos = TileMap->GetTileCoord(Hit.ImpactPoint);

			if (TileMap->GetTileProperty(TilePos, AG_TileProperty::IsWalkable))
			{
				FVector TargetDestination = TileMap->GetTilePosition(TilePos);
				SetNewMoveDestination(TargetDestination);
			}
		}
	}
}

void AAG_PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MyPawn = NULL"));
	}
}

void AAG_PlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void AAG_PlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}

void AAG_PlayerController::NextInventoryItem()
{
	//AAG_PlayerCharacter* Character = Cast<AAG_PlayerCharacter>(GetPawn());
	//Character->NextInventoryItem();
	APawn* MyPawn = GetPawn();
	Cast<AAG_PlayerCharacter>(MyPawn)->NextInventoryItem();
}

void AAG_PlayerController::PreviousInventoryItem()
{
	//AAG_PlayerCharacter* Character = Cast<AAG_PlayerCharacter>(GetPawn());
	//Character->PreviousInventoryItem();
	APawn* MyPawn = GetPawn();
	Cast<AAG_PlayerCharacter>(MyPawn)->PreviousInventoryItem();
}

///****** UI ******

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
