#include "AG_EventManager.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "AG_ColdNites/Camera/AG_CameraManager.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"

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

	//Event Inits
	LevelWonEventInit();
	LevelLoseEventInit();
}

void AAG_EventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerCurrentTileCoord = TileMap->GetTileCoord(PlayerCharacter->GetActorLocation());

	CameraSwitchEventUpdate();
	LevelWonEventUpdate(DeltaTime);
	LevelLoseEventUpdate(DeltaTime);
}

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

