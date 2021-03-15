#include "AG_PatrollingAICharacter.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"

AAG_PatrollingAICharacter::AAG_PatrollingAICharacter()
{
	Tags.Add("AG_PatrollingAI");
}

void AAG_PatrollingAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_PatrollingAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_PatrollingAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAITurn && bIsMyTurn)
	{
		bIsMyTurn = false;

		if (IsActorInRange("AG_PlayableCharacter", GetActorForwardVector(), 1))
		{
			KnockOutPlayer(GetActorForwardVector());
		}
		else
		{
			MoveToNextPatrolTile();
		}
	}
}

void AAG_PatrollingAICharacter::MoveToNextPatrolTile()
{
	if (PatrolTileCoords.Num() > 0)
	{
		if (PatrolIndex < PatrolTileCoords.Num())
		{
			PatrolIndex++;
		}
		else
		{
			PatrolIndex = 0;
		}
		CurrentPatrolTileCoord = PatrolTileCoords[PatrolIndex];

		if (AG_TileInDirection::TileAtForward == TileMap->GetTileInDirection(CurrentPatrolTileCoord, this))
		{
			MoveForward();
		}
		else if (AG_TileInDirection::TileAtBackward == TileMap->GetTileInDirection(CurrentPatrolTileCoord, this))
		{
			MoveBackward();
		}
		else if (AG_TileInDirection::TileAtRight == TileMap->GetTileInDirection(CurrentPatrolTileCoord, this))
		{
			MoveRight();
		}
		else if (AG_TileInDirection::TileAtLeft == TileMap->GetTileInDirection(CurrentPatrolTileCoord, this))
		{
			MoveLeft();
		}
		else if (AG_TileInDirection::TileAtInvalidDirection == TileMap->GetTileInDirection(CurrentPatrolTileCoord, this))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Orange, "InValid Patrol Direction");
		}
	}
}
