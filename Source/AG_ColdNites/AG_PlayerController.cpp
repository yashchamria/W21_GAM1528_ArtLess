// Fill out your copyright notice in the Description page of Project Settings.
#include "AG_PlayerController.h"
#include "Blueprint/UserWidget.h"

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
