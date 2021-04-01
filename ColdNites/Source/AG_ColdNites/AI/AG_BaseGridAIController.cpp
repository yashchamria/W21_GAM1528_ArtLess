#include "AG_BaseGridAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"

AAG_BaseGridAIController::AAG_BaseGridAIController(FObjectInitializer const& ObjectInitializer)
{
	BehaviorTree = ObjectInitializer.CreateDefaultSubobject<UBehaviorTree>(this, TEXT("Behavior Tree"));

	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("Behavior Tree Component"));

	BlackBoardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoard Component"));
}

void AAG_BaseGridAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
	
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AAG_BaseGridAIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);

	AICharacter = Cast<AAG_AIBaseGridCharacter>(pawn);
	
	if (BlackBoardComponent)
	{
		BlackBoardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}
