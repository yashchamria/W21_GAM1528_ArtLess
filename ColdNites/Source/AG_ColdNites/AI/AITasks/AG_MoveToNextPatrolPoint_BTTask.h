/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  AI System

 Description - The AI System allows the easy creation of game enemies using the single BaseAI class and Behaviour Tree Task Nodes.

				The Behaviour Tree is the one, responsible for the AI Behaviour and what makes every AI unique.
				It uses a set of nodes that determine the tasks AI needs to perform.

				This node is responsible for setting the AI movement to the next patrol point.
******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AG_MoveToNextPatrolPoint_BTTask.generated.h"

UCLASS()
class AG_COLDNITES_API UAG_MoveToNextPatrolPoint_BTTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAG_MoveToNextPatrolPoint_BTTask();

	class AAG_BaseGridAIController* AIController;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
