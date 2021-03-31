#include "AG_EventManager.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/StaticMeshActor.h"

#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "AG_ColdNites/Camera/AG_CameraManager.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridCharacter.h"

AAG_EventManager::AAG_EventManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bLockLocation = true;
}

void AAG_EventManager::BeginPlay()
{
	Super::BeginPlay();

	//Getting TileMap
	TArray<AActor*> TileMapActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);
	if (TileMapActor.Num() > 0) { TileMap = Cast<AAG_TileMap>(TileMapActor[0]); }
	
	//Getting GameMode
	GameMode = Cast<AAG_ColdNitesGameModeBase>(GetWorld()->GetAuthGameMode());
	
	//Getting Camera Manager
	TArray<AActor*> CameraManagerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_CameraManager::StaticClass(), CameraManagerActor);
	if (CameraManagerActor.Num() > 0) { CameraManager = Cast<AAG_CameraManager>(CameraManagerActor[0]); }

	//Getting Player
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player) { PlayerCharacter = Cast<AAG_PlayableCharacter>(Player); }
	
	//Getting PlayerController
	APlayerController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (CurrentController) { PlayerController = Cast<AAG_PlayerController>(CurrentController); }

	//Getting All AI Characters
	TArray<AActor*> AIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_AIBaseGridCharacter::StaticClass(), AIActors);
	if(AIActors.Num() > 0)
	{
		AICharacters.Reserve(AIActors.Num());
		for (AActor* AI : AIActors) { AICharacters.Add(Cast<AAG_AIBaseGridCharacter>(AI)); }
	}

	
	//Event Inits
	
	SetDecorMeshProperty();
	SetPlayerIntialTile();
	SetFirstTurn(AG_TurnState::IsPlayerTurn);
	LevelWonEventInit();
	LevelLoseEventInit();
}

void AAG_EventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerCurrentTileCoord = TileMap->GetTileCoord(PlayerCharacter->GetActorLocation());

	SwitchTurnStateUpdate();
	CameraSwitchEventUpdate();
	LevelWonEventUpdate(DeltaTime);
	LevelLoseEventUpdate(DeltaTime);
}

//Miscellaneous Events

void AAG_EventManager::SetPlayerIntialTile()
{
	if (PlayerCharacter && TileMap)
	{
		FVector PlayerStartLocation = TileMap->GetTileWorldPosition(TileMap->GetStartTileCoord());
		PlayerCharacter->SetActorLocation(PlayerStartLocation);
	}
}

void AAG_EventManager::SetDecorMeshProperty()
{
	//Getting All StaticMeshActor
	TArray<AActor*> AllStaticMeshActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), AllStaticMeshActor);
	if (AllStaticMeshActor.Num() > 0)
	{
		for (AActor* StaticMeshActor : AllStaticMeshActor)
		{
			//Disables collision and Overlaps
			StaticMeshActor->SetActorEnableCollision(false);
			StaticMeshActor->UpdateOverlaps(false);
		}
	}
}


//Switch Turn Event.

void AAG_EventManager::SetFirstTurn(AG_TurnState NewTurnState)
{
	if (GameMode)
	{
		GameMode->SetCurrentTurnState(NewTurnState);
		ChangeTurnState(NewTurnState);
	}
}

void AAG_EventManager::SwitchTurnStateUpdate()
{
	AG_TurnState CurrentTurnState = GameMode->GetCurrentTurnState();

	if(CurrentTurnState == AG_TurnState::IsPlayerTurn)
	{
		if (PlayerCharacter)
		{
			if (PlayerCharacter->bIsReached && !PlayerCharacter->bIsMyTurn)
			{
				ChangeTurnState(AG_TurnState::IsAITurn);
			}
		}
	}

	if (CurrentTurnState == AG_TurnState::IsAITurn)
	{
		if (CheckIsAITurnOver())
		{
			ChangeTurnState(AG_TurnState::IsPlayerTurn);
		}
	}
}

bool AAG_EventManager::CheckIsAITurnOver()
{
	for (AAG_AIBaseGridCharacter* AIActor : AICharacters)
	{
		if (AIActor)
		{
			if(!(AIActor->bIsReached && !AIActor->bIsMyTurn))
			{
				return false;
			}
		}
	}
	return true;
}

void AAG_EventManager::ChangeTurnState(AG_TurnState NewTurnState)
{
	switch(NewTurnState)
	{
	case AG_TurnState::IsPlayerTurn:
			SetPlayerTurnEvent();
			break;

	case AG_TurnState::IsAITurn:
		SetAITurnEvent();
		break;
		
	case AG_TurnState::IdleTurn:
		SetIdleTurnEvent();
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("InValid Turn State"));
		break;
	}
	
	GameMode->SetCurrentTurnState(NewTurnState);
}

void AAG_EventManager::SetPlayerTurnEvent()
{
	PlayerCharacter->bIsMyTurn = true;

	for (AAG_AIBaseGridCharacter* AI : AICharacters)
	{
		AI->bIsMyTurn = false;
		AI->ResetOnTurnEnd();
	}
}

void AAG_EventManager::SetAITurnEvent()
{
	for(AAG_AIBaseGridCharacter* AI : AICharacters)
	{
		AI->bIsMyTurn = true;
	}
	
	PlayerCharacter->bIsMyTurn = false;
	PlayerCharacter->ResetOnTurnEnd();
}

void AAG_EventManager::SetIdleTurnEvent()
{
	PlayerCharacter->bIsMyTurn = false;
	PlayerCharacter->ResetOnTurnEnd();

	for (AAG_AIBaseGridCharacter* AI : AICharacters)
	{
		AI->bIsMyTurn = false;
		AI->ResetOnTurnEnd();
	}
}


//Camera Switch Event.

void AAG_EventManager::CameraSwitchEventUpdate()
{
	if (PlayerCharacter->bIsReached)
	{
		CurrentCameraTag = TileMap->GetTileCameraTag(PlayerCurrentTileCoord);
	}
}

FName AAG_EventManager::GetSwitchCameraTag()
{
	if(TileMap)
	{
		if(TileMap->IsTileCoordVaild(PlayerCurrentTileCoord))
		{
			return CurrentCameraTag;
		}
	}
	
	return "None";
}

//Level Won Event.

void AAG_EventManager::LevelWonEventInit()
{
	if (WinWidgetTemplate)
	{
		WinWidget = CreateWidget<UUserWidget>(PlayerController, WinWidgetTemplate);
		WinWidget->AddToViewport();
		WinWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAG_EventManager::LevelWonEventUpdate(float DeltaTime)
{
	if (TileMap->GetTileProperty(PlayerCurrentTileCoord, AG_TileProperty::IsWinTile))
	{
		bWon = true;

		if(PlayerCharacter->bIsReached)
		{
			if (WinWidgetTemplate)
			{
				WinWidget->SetVisibility(ESlateVisibility::Visible);
				PlayerController->EnableUIInput(false);
			}
		}

		PlayerController->EnableGamePlayInput(false);
	}
}

//Level Lose Event.

void AAG_EventManager::LevelLoseEventInit()
{
	if (LoseWidgetTemplate)
	{
		LoseWidget = CreateWidget<UUserWidget>(PlayerController, LoseWidgetTemplate);
		LoseWidget->AddToViewport();
		LoseWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAG_EventManager::LevelLoseEventUpdate(float DeltaTime)
{
	if (PlayerCharacter->bKnockOut && !bWon)
	{
		if (PlayerCharacter->bIsReached)
		{
			if (LoseWidgetTemplate)
			{
				LoseWidget->SetVisibility(ESlateVisibility::Visible);
				PlayerController->EnableUIInput(false);
			}
		}
	}
}