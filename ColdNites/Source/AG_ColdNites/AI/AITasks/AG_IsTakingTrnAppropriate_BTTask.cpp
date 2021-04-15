#include "AG_IsTakingTrnAppropriate_BTTask.h"

#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/EventManager/AG_EventManager.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"
#include "Kismet/GameplayStatics.h"

UAG_IsTakingTrnAppropriate_BTTask::UAG_IsTakingTrnAppropriate_BTTask()
{
	NodeName = TEXT("Is Taking Turn Appropriate");
}

EBTNodeResult::Type UAG_IsTakingTrnAppropriate_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Getting Player
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player) { PlayerCharacter = Cast<AAG_PlayableCharacter>(Player); }

	//Getting EventManager
	TArray<AActor*> EventManagerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_EventManager::StaticClass(), EventManagerActor);
	if (EventManagerActor.Num() > 0) { EventManager = Cast<AAG_EventManager>(EventManagerActor[0]); }

	//Getting AI
	AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	if(PlayerCharacter && EventManager && AIController)
	{
		if(PlayerCharacter->bIsKnockedOut)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}

		if(EventManager->bHasPlayerWon)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}

		if(AIController->AICharacter)
		{
			if(AIController->AICharacter->bIsKnockedOut)
			{
				AIController->AICharacter->bIsMyTurn = false;
				
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				return EBTNodeResult::Failed;
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
