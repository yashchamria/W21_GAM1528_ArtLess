#include "AG_RotateToNxtPatrolPoint_BTTask.h"
#include "AG_ColdNites/AI/AG_BaseGridAIController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"

UAG_RotateToNxtPatrolPoint_BTTask::UAG_RotateToNxtPatrolPoint_BTTask()
{
	NodeName = TEXT("Rotate the AI to Next Patrol Tile");
}

EBTNodeResult::Type UAG_RotateToNxtPatrolPoint_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<AAG_BaseGridAIController>(OwnerComp.GetAIOwner());


	if (AIController)
	{
		AAG_AIBaseGridCharacter* AICharacter = AIController->AICharacter;
		AfterNextPatrolPoint = AICharacter->PatrolIndex;

		if (AICharacter->PatrolTileCoords.Num() > 0)
		{
			if (AfterNextPatrolPoint < (AICharacter->PatrolTileCoords.Num() - 1))
			{
				AfterNextPatrolPoint++;
			}
			else
			{
				AfterNextPatrolPoint = 0;
			}
			
			FIntPoint NextPatrolTileCoord = AICharacter->PatrolTileCoords[AfterNextPatrolPoint];

			AG_TileInDirection PatrolDirection = AICharacter->TileMap->GetTileInDirection(NextPatrolTileCoord, AICharacter);

			switch (PatrolDirection)
			{
			case AG_TileInDirection::TileAtForward:
				break;

			case AG_TileInDirection::TileAtBackward:
				AICharacter->Rotate(180);
				break;

			case AG_TileInDirection::TileAtLeft:
				AICharacter->Rotate(-90);
				break;

			case AG_TileInDirection::TileAtRight:
				AICharacter->Rotate(90);
				break;

			default:
				GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Red, "InValid Patrol Rotation Direction");
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
