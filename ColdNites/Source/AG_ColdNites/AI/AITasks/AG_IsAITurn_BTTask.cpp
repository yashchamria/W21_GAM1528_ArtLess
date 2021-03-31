#include "AG_IsAITurn_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

UAG_IsAITurn_BTTask::UAG_IsAITurn_BTTask()
{
	NodeName = TEXT("Is My Turn");
}

EBTNodeResult::Type UAG_IsAITurn_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAG_BaseGridAIController* const AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	AAG_AIBaseGridCharacter* AICharacter = nullptr;

	if (AIController)
	{
		AICharacter = Cast<AAG_AIBaseGridCharacter>(AIController->GetPawn());
	}

	if (AICharacter)
	{
		if(AICharacter->bIsMyTurn)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
