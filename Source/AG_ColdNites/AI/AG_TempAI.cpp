// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_TempAI.h"
#include "../GameMode/AG_ColdNitesGameModeBase.h"

// Sets default values
AAG_TempAI::AAG_TempAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AG_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	AG_Mesh->SetupAttachment(RootComponent);
	
	TurnTimer = 5.0f;
}

// Called when the game starts or when spawned
void AAG_TempAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAG_TempAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode->GetTurnState() == TurnState::IsAITurn)
	{
		TurnTimer -= DeltaTime;

		if (TurnTimer <= 0.0f)
		{
			bWalk = true;
			TurnTimer = 5.0f;
		}
	}
}

