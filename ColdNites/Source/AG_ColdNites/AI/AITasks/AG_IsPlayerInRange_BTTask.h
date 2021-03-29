#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AG_IsPlayerInRange_BTTask.generated.h"

UCLASS()
class AG_COLDNITES_API UAG_IsPlayerInRange_BTTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAG_IsPlayerInRange_BTTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
