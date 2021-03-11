#include "AG_AITurnManager.h"

#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"

AAG_AITurnManager::AAG_AITurnManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bLockLocation = true;
	PlayerRestTimer = 2.5f;
}

void AAG_AITurnManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//TArray<AActor*> AIActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_AIBaseGridCharacter::StaticClass(), AIActors);
	//if (AIActors.Num() > 0)
	//{
	//	for (int i = 0; i < AIActors.Num(); i++)
	//	{
	//		AllPresentAIActors.Add(Cast<AAG_AIBaseGridCharacter>(AIActors[i]));
	//	}
	//}
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

	bool Check = CheckIsAITurn();

	if (!Check && PlayerRestTimer <= 0.0f) 
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
	for (AAG_AIBaseGridCharacter* AIActor : AllPresentAIActors)
	{
		PlayerRestTimer = 2.5f;
		AIActor->ResetOnTurnEnd();
	}
}