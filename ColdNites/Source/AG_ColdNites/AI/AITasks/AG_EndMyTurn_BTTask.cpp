#include "AG_EndMyTurn_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

UAG_EndMyTurn_BTTask::UAG_EndMyTurn_BTTask()
{
	NodeName = TEXT("End My Turn");
}

EBTNodeResult::Type UAG_EndMyTurn_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAG_BaseGridAIController* const AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	AAG_AIBaseGridCharacter* AICharacter = nullptr;

	if (AIController)
	{
		AICharacter = Cast<AAG_AIBaseGridCharacter>(AIController->GetPawn());
	}

	if (AICharacter)
	{
		AICharacter->bIsMyTurn = false;
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
