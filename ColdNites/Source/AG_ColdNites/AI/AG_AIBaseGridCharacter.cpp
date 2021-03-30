#include "AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"
#include "AG_ColdNites/AI/AG_AITurnManager.h"

AAG_AIBaseGridCharacter::AAG_AIBaseGridCharacter()
{
	Tags.Add("AG_AICharacter");
}

void AAG_AIBaseGridCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_AIBaseGridCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Getting Player
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player) { PlayerCharacter = Cast<AAG_PlayableCharacter>(Player); }

	//Getting PlayerController
	APlayerController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (CurrentController) { PlayerController = Cast<AAG_PlayerController>(CurrentController); }

	//Getting AIManager
	TArray<AActor*> AIActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_AITurnManager::StaticClass(), AIActor);
	if (AIActor.Num() > 0)
	{
		AITurnManager = Cast<AAG_AITurnManager>(AIActor[0]);
	}

	AITurnManager->RegisterToAIManager(this);
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

bool AAG_AIBaseGridCharacter::bIsPlayerInRange(uint32 TileRange)
{
	for (uint32 i = 1; i <= TileRange; i++)
	{
		if (IsActorInRange("AG_PlayableCharacter", GetActorForwardVector(), i))
		{
			return true;
		}
	}
	return false;
}

void AAG_AIBaseGridCharacter::KnockOutPlayer(FVector ForwardDirection)
{
	if (PlayerCharacter->bIsReached)
	{
		MoveForward();

		AAG_AIBaseGridCharacter* AICharacter = Cast<AAG_AIBaseGridCharacter>(GetInstigator());
		
		if (AICharacter->bIsReached)
		{
			PlayerCharacter->KnockOut(ForwardDirection);
			PlayerController->EnableGamePlayInput(false);

			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Player Caught !!!");
		}
	}
}

void AAG_AIBaseGridCharacter::ResetOnTurnEnd()
{
	Super::ResetOnTurnEnd();

	bIsMyTurn = true;
}