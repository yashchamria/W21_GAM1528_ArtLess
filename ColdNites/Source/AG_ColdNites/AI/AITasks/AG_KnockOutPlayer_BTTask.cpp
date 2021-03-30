#include "AG_KnockOutPlayer_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

UAG_KnockOutPlayer_BTTask::UAG_KnockOutPlayer_BTTask()
{
	NodeName = TEXT("Knock Out Player");
}

EBTNodeResult::Type UAG_KnockOutPlayer_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAG_BaseGridAIController* const AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	AAG_AIBaseGridCharacter* AICharacter = nullptr;
	
	if (AIController)
	{
		AICharacter = Cast<AAG_AIBaseGridCharacter>(AIController->GetPawn());
	}

	if (AICharacter)
	{
		AICharacter->KnockOutPlayer(AICharacter->GetActorForwardVector());
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
