#include "AG_AITurnManager.h"
#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"

AAG_AITurnManager::AAG_AITurnManager()
{
	PrimaryActorTick.bCanEverTick = true;
	AITurnTimer = 2.5f;
	bShouldRegister = false;
}

void AAG_AITurnManager::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_AITurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode->GetTurnState() == TurnState::IsAITurn)
	{
		AITurnTimer -= DeltaTime;

		if (AITurnTimer <= 0.0f)
		{
			AITurnTimer = 2.5f;
			GameMode->FinishTurn();
		}
	}
}
