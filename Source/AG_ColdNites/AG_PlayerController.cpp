// Fill out your copyright notice in the Description page of Project Settings.

#include "AG_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "AG_PlayerCharacter.h"
#include "Engine/World.h"

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
}

void AAG_PlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AAG_PlayerCharacter* MyPawn = Cast<AAG_PlayerCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			SetNewMoveDestination(Hit.ImpactPoint);
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

void AAG_PlayerController::ShowPauseMenu()
{
	if(PauseMenuOverlay)
	{
		bPauseMenuVisible = true;
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Visible);
		SetShowMouseCursor(true);
	}
}

void AAG_PlayerController::HidePauseMenu_Implementation()
{
	if (PauseMenuOverlay)
	{
		bPauseMenuVisible = false;
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Hidden);
		SetShowMouseCursor(false);
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

		SetShowMouseCursor(true);
	}
}
