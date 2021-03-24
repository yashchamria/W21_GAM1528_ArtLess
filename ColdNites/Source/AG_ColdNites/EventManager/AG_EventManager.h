#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_EventManager.generated.h"

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
	class AAG_PlayableCharacter* PlayerCharacter;
	class AAG_PlayerController* PlayerController;
	class AAG_CameraManager* CameraManager;
	
	FIntPoint PlayerCurrentTileCoord;

//CameraSwitchEvent
public:
	FName GetSwitchCameraTag();
	
private:
	FName CurrentCameraTag;
	void CameraSwitchEventUpdate();

//Win Event
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<UUserWidget> WinWidgetTemplate;
	
private:	
	void LevelWonEventInit();
	void LevelWonEventUpdate(float DeltaTime);

	class UUserWidget* WinWidget;
	bool bWon = false;

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
