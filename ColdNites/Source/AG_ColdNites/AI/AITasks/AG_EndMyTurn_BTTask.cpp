#include "AG_EndMyTurn_BTTask.h"

UAG_EndMyTurn_BTTask::UAG_EndMyTurn_BTTask()
{
	NodeName = TEXT("End My Turn");
}

EBTNodeResult::Type UAG_EndMyTurn_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
