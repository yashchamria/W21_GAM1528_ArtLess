#include "AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"

AAG_AIBaseGridCharacter::AAG_AIBaseGridCharacter()
{
	Tags.Add("AG_BaseAI");
}

void AAG_AIBaseGridCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_AIBaseGridCharacter::BeginPlay()
{
	Super::BeginPlay();

	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player) { PlayerCharacter = Cast<AAG_PlayableCharacter>(Player); }
}

void AAG_AIBaseGridCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode->GetTurnState() == TurnState::IsAITurn)
	{
		bIsAITurn = true;
	}
	else
	{
		bIsAITurn = false;
		ResetOnTurnEnd();
	}
}

//void AAG_AIBaseGridCharacter::InTick(float DeltaTime)
//{
//
//	
//}

void AAG_AIBaseGridCharacter::MoveRight()
{
	Super::MoveRight();
}

void AAG_AIBaseGridCharacter::MoveLeft()
{
	Super::MoveLeft();
}

void AAG_AIBaseGridCharacter::MoveForward()
{
	Super::MoveForward();
}

void AAG_AIBaseGridCharacter::MoveBackward()
{
	Super::MoveBackward();
}

bool AAG_AIBaseGridCharacter::IsActorInRange(FName ActorTag, FVector InDirection, uint32 TileRange)
{
	FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
	FIntPoint NextTileCoord = TileMap->GetNextTileCoord(GetActorLocation(), InDirection, TileRange);
	
	if (TileMap->IsRegistered(ActorTag, NextTileCoord))
	{
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "Actor In Range !!!");
		return true;
	}
	
	return false;
}

void AAG_AIBaseGridCharacter::DetectPlayer(uint32 TileRange)
{
	for (uint32 i = 1; i <= TileRange; i++)
	{
		if(IsActorInRange("AG_PlayableCharacter", GetActorForwardVector(), i))
		{
			bIsPlayerInRange = true;
			break;
		}
		bIsPlayerInRange = false;
	}
}

void AAG_AIBaseGridCharacter::CatchPlayer()
{
	if (bIsPlayerInRange)
	{
		MoveForward();
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "Player Caught !!!");
	}

}
