#include "AG_IsAITurn_BTTask.h"

UAG_IsAITurn_BTTask::UAG_IsAITurn_BTTask()
{
	NodeName = TEXT("Is AI Turn");
}

EBTNodeResult::Type UAG_IsAITurn_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
