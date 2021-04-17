/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  AI System

 Description - The AI System allows the easy creation of game enemies using the single BaseAI class and Behaviour Tree Task Nodes.

				The Behaviour Tree is the one, responsible for the AI Behaviour and what makes every AI unique.
				It uses a set of nodes that determine the tasks AI needs to perform.

				This node is responsible for checking for any major events such as player win/lose/knockout ot AI knockout before letting the AI move.
******************************************************************************************************************/

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

	class AAG_BaseGridAIController* AIController;
	class AAG_PlayableCharacter* PlayerCharacter;
	class AAG_EventManager* EventManager;


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
