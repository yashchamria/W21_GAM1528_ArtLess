#include "AG_IsPlayerInRange_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"

UAG_IsPlayerInRange_BTTask::UAG_IsPlayerInRange_BTTask()
{
	NodeName = TEXT("Is Player Is In Forward Tile Range");
}

EBTNodeResult::Type UAG_IsPlayerInRange_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAG_BaseGridAIController* const AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	AAG_AIBaseGridCharacter* AICharacter = nullptr;
	
	if (AIController)
	{
		AICharacter = Cast<AAG_AIBaseGridCharacter>(AIController->GetPawn());
	}
	
	if (AICharacter)
	{
		if (AICharacter->bIsPlayerInRange())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
