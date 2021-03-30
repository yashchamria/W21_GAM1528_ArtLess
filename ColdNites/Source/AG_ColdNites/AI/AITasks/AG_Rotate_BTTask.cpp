#include "AG_Rotate_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

UAG_Rotate_BTTask::UAG_Rotate_BTTask()
{
	NodeName = TEXT("Rotate Actor by 180 Increment");
}

EBTNodeResult::Type UAG_Rotate_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAG_BaseGridAIController* const AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	AAG_AIBaseGridCharacter* AICharacter = nullptr;

	if (AIController)
	{
		AICharacter = Cast<AAG_AIBaseGridCharacter>(AIController->GetPawn());
	}

	if(AICharacter)
	{
		AICharacter->Rotate(180);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
