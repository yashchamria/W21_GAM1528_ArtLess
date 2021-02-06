// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_PlayerController.h"
#include "Blueprint/UserWidget.h"

void AAG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bPauseMenuVisible = false;
	
	if (PauseMenuOverlayAsset)
	{
		PauseMenuOverlay = CreateWidget<UUserWidget>(this, PauseMenuOverlayAsset);
		PauseMenuOverlay->AddToViewport();
		PauseMenuOverlay->SetVisibility(ESlateVisibility::Hidden);
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
		ShowPauseMenu();
	}
}