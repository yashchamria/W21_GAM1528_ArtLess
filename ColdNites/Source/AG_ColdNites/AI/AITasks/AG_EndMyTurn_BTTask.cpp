#include "AG_EndMyTurn_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

UAG_EndMyTurn_BTTask::UAG_EndMyTurn_BTTask()
{
	NodeName = TEXT("End My Turn");
}

EBTNodeResult::Type UAG_EndMyTurn_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		AIController->AICharacter->bIsMyTurn = false;
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
