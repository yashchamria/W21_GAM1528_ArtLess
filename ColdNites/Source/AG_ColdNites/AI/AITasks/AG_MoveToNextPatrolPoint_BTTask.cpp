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
	AAG_BaseGridAIController* const AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());

	AAG_AIBaseGridCharacter* AICharacter = nullptr;

	if (AIController)
	{
		AICharacter = Cast<AAG_AIBaseGridCharacter>(AIController->GetPawn());
	}

	if (AICharacter)
	{
		if (AICharacter->PatrolTileCoords.Num() > 0)
		{
			if ((AICharacter->PatrolIndex) < (AICharacter->PatrolTileCoords.Num() - 1))
			{
				AICharacter->PatrolIndex++;
			}
			else
			{
				AICharacter->PatrolIndex = 0;
			}
			
			AICharacter->CurrentPatrolTileCoord = AICharacter->PatrolTileCoords[AICharacter->PatrolIndex];

			if (AG_TileInDirection::TileAtForward == AICharacter->TileMap->GetTileInDirection(AICharacter->CurrentPatrolTileCoord, AICharacter))
			{
				AICharacter->MoveForward();
			}
			else if (AG_TileInDirection::TileAtBackward == AICharacter->TileMap->GetTileInDirection(AICharacter->CurrentPatrolTileCoord, AICharacter))
			{
				AICharacter->MoveBackward();
			}
			else if (AG_TileInDirection::TileAtRight == AICharacter->TileMap->GetTileInDirection(AICharacter->CurrentPatrolTileCoord, AICharacter))
			{
				AICharacter->MoveRight();
			}
			else if (AG_TileInDirection::TileAtLeft == AICharacter->TileMap->GetTileInDirection(AICharacter->CurrentPatrolTileCoord, AICharacter))
			{
				AICharacter->MoveLeft();
			}
			else if (AG_TileInDirection::TileAtInvalidDirection == AICharacter->TileMap->GetTileInDirection(AICharacter->CurrentPatrolTileCoord, AICharacter))
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Orange, "InValid Patrol Direction");
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
