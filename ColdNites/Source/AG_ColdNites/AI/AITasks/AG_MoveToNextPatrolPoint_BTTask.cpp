#include "AG_MoveToNextPatrolPoint_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"

UAG_MoveToNextPatrolPoint_BTTask::UAG_MoveToNextPatrolPoint_BTTask()
{
	NodeName = TEXT("Move the AI to Next Patrol Tile");
}

EBTNodeResult::Type UAG_MoveToNextPatrolPoint_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());


	if (AIController)
	{
		AAG_AIBaseGridCharacter* AICharacter = AIController->AICharacter;
		
		
		if (AICharacter->PatrolTileCoords.Num() > 0)
		{
			//For Movement
			if ((AICharacter->PatrolIndex) < (AICharacter->PatrolTileCoords.Num() - 1))
			{
				AICharacter->PatrolIndex++;
			}
			else
			{
				AICharacter->PatrolIndex = 0;
			}
			
			AICharacter->CurrentPatrolTileCoord = AICharacter->PatrolTileCoords[AICharacter->PatrolIndex];

			//Handles Movement
			AG_TileInDirection PatrolDirection = AICharacter->TileMap->GetTileInDirection(AICharacter->CurrentPatrolTileCoord, AICharacter);

			switch(PatrolDirection)
			{
			case AG_TileInDirection::TileAtForward:
				AICharacter->MoveForward();
				break;

			case AG_TileInDirection::TileAtBackward:
				AICharacter->MoveBackward();
				break;

			case AG_TileInDirection::TileAtLeft:
				AICharacter->MoveLeft();
				break;

			case AG_TileInDirection::TileAtRight:
				AICharacter->MoveRight();
				break;

			default:
				GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Red, "InValid Patrol Direction");
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
