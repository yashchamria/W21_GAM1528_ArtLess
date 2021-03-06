#include "AG_TempAI.h"
#include "../GameMode/AG_ColdNitesGameModeBase.h"

AAG_TempAI::AAG_TempAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AG_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	AG_Mesh->SetupAttachment(RootComponent);

	TurnTimer = 3.0f;
}

void AAG_TempAI::BeginPlay()
{
	Super::BeginPlay();

}

void AAG_TempAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode->GetTurnState() == TurnState::IsAITurn)
	{
		TurnTimer -= DeltaTime;

		if (TurnTimer <= 0.0f)
		{
			bWalk = true;
			TurnTimer = 3.0f;
		}
	}
}