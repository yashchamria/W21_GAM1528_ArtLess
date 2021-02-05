// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_TestChar.h"
#include "AG_PlayerController.h"

AAG_TestChar::AAG_TestChar()
{
	PrimaryActorTick.bCanEverTick = true;

	bESC_Down = false;
}

void AAG_TestChar::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AAG_PlayerController>(GetController());
}

void AAG_TestChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAG_TestChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ESC", IE_Pressed,  this, &AAG_TestChar::EscKeyDown);
	PlayerInputComponent->BindAction("ESC", IE_Released, this, &AAG_TestChar::EscKeyUp);
}

void AAG_TestChar::EscKeyDown()
{
	bESC_Down = true;

	if(MainPlayerController)
	{
		MainPlayerController->TogglePauseMenu();
	}
}

void AAG_TestChar::EscKeyUp()
{
	bESC_Down = false;
	
	if (MainPlayerController)
	{
		MainPlayerController->TogglePauseMenu();
	}
}
