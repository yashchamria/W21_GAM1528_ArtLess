#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_EventManager.generated.h"

enum AG_TurnState : unsigned;

UCLASS()
class AG_COLDNITES_API AAG_EventManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_EventManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	class AAG_TileMap* TileMap;
	class AAG_ColdNitesGameModeBase* GameMode;
	class UAG_ColdNitesGameInstance* GameInstance;
	class AAG_PlayableCharacter* PlayerCharacter;
	class AAG_PlayerController* PlayerController;
	class AAG_CameraManager* CameraManager;
	TArray<class AAG_AIBaseGridCharacter*> AICharacters;

	FIntPoint PlayerCurrentTileCoord;

//Miscellaneous Events
	void SetPlayerIntialTile();
	void SetDecorMeshProperty();
	
//Turn Events
	void SetFirstTurn(AG_TurnState NewTurnState);
	void SwitchTurnStateUpdate();
	void ChangeTurnState(AG_TurnState NewTurnState);
	bool CheckIsAITurnOver();
	void SetPlayerTurnEvent();
	void SetAITurnEvent();
	void SetIdleTurnEvent();
	
//CameraSwitchEvent
public:
	FName GetSwitchCameraTag();
	
private:
	FName CurrentCameraTag;
	void CameraSwitchEventUpdate();

//Scoring Event
public:
	void UpdateStarCount(uint8 StarIncrement = 1);
	void UpdateTurnCount(uint8 TurnIncrement = 1);

//Win Event
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<UUserWidget> WinWidgetTemplate;

	bool bHasPlayerWon = false;
	
private:	
	void LevelWonEventInit();
	void LevelWonEventUpdate(float DeltaTime);

	class UUserWidget* WinWidget;

//Lose Event
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<UUserWidget> LoseWidgetTemplate;
	
private:	
	void LevelLoseEventInit();
	void LevelLoseEventUpdate(float DeltaTime);

	class UUserWidget* LoseWidget;
	bool bPlayerKnockedOut = false;
};
