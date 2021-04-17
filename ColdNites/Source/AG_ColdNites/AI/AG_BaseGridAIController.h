/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  AI System

 Description - The AI System allows the easy creation of game enemies using the single BaseAI class and Behaviour Tree Task Nodes.

				The main job of the AI Controller is to set up the behaviour tree.
				Every AI is supposed to be using its own AI Controller with different Behaviour Trees and Blackboard.
******************************************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AG_BaseGridAIController.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_BaseGridAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UBlackboardComponent* BlackBoardComponent;

public:
	AAG_BaseGridAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());
	
	void BeginPlay() override;

	void OnPossess(APawn* const pawn) override;

	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return BlackBoardComponent; }

	class AAG_AIBaseGridCharacter* AICharacter;
};
