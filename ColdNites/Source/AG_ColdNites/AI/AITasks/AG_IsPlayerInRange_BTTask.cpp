#include "AG_IsPlayerInRange_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

UAG_IsPlayerInRange_BTTask::UAG_IsPlayerInRange_BTTask()
{
	NodeName = TEXT("Is Player Is In Forward Tile Range");
}

EBTNodeResult::Type UAG_IsPlayerInRange_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		if (AIController->AICharacter->IsPlayerInRange())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
