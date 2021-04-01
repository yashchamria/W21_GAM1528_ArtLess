#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AG_IsTakingTrnAppropriate_BTTask.generated.h"

UCLASS()
class AG_COLDNITES_API UAG_IsTakingTrnAppropriate_BTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UAG_IsTakingTrnAppropriate_BTTask();

	class AAG_PlayableCharacter* PlayerCharacter;
	class AAG_EventManager* EventManager;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
