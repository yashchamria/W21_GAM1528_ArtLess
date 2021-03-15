#include "AG_AITurnManager.h"

#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"

AAG_AITurnManager::AAG_AITurnManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bLockLocation = true;
	PlayerRestTimer = 3.25f;
}

void AAG_AITurnManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_AITurnManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AAG_ColdNitesGameModeBase>(GetWorld()->GetAuthGameMode());
}


void AAG_AITurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerRestTimer -= DeltaTime;

	if (!CheckIsAITurn() && PlayerRestTimer <= 0.0f)
	{
		GameMode->FinishTurn();
		ResetAfterAITurn();
	}
}

void AAG_AITurnManager::RegisterToAIManager(AAG_AIBaseGridCharacter* AIActor)
{
	uint32 ActorIndex = AllPresentAIActors.Find(AIActor);

	if (ActorIndex == INDEX_NONE)
	{
		AllPresentAIActors.Add(AIActor);
	}
}


void AAG_AITurnManager::UnRegisterToAIManager(AAG_AIBaseGridCharacter* AIActor)
{
	uint32 ActorIndex = AllPresentAIActors.Find(AIActor);

	if (AllPresentAIActors.IsValidIndex(ActorIndex))
	{
		AllPresentAIActors.RemoveAt(ActorIndex);
	}
}

bool AAG_AITurnManager::CheckIsAITurn()
{
	for (AAG_AIBaseGridCharacter* AIActor : AllPresentAIActors)
	{
		if (AIActor->bIsMyTurn)
		{
			return true;
		}
	}
	return false;
}

void AAG_AITurnManager::ResetAfterAITurn()
{
	PlayerRestTimer = 3.25f;

	for (AAG_AIBaseGridCharacter* AIActor : AllPresentAIActors)
	{
		AIActor->ResetOnTurnEnd();
	}
}