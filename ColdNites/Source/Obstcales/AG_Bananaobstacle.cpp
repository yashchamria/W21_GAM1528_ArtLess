// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_Bananaobstacle.h"
#include "../Player/AG_PlayableCharacter.h"
void AAG_Bananaobstacle::Slip()
{
	Disable();
	bTrigger = true;
	MoveBack();
}

void AAG_Bananaobstacle::MoveBack()
{
	if (PlayerCharacter->Prev == AG_PreviousMove::Forward)
	{
		PlayerCharacter->MoveBackward();
	}
	else if (PlayerCharacter->Prev == AG_PreviousMove::Backward)
	{
		PlayerCharacter->MoveForward();
	}
	else if (PlayerCharacter->Prev == AG_PreviousMove::Left)
	{
		PlayerCharacter->MoveRight();
	}
	else if (PlayerCharacter->Prev == AG_PreviousMove::Right)
	{
		PlayerCharacter->MoveLeft();
	}

}

void AAG_Bananaobstacle::Disable()
{
	UnRegisterToTileMap();
	SetActorHiddenInGame(true);
}

void AAG_Bananaobstacle::Enable()
{
	SetActorHiddenInGame(false);
}

void AAG_Bananaobstacle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_Bananaobstacle::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(GetActorLocation() + 10.0f);
}

void AAG_Bananaobstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CheckPlayerOnTheTile() && !bTrigger)
	{
		Slip();
	}

}