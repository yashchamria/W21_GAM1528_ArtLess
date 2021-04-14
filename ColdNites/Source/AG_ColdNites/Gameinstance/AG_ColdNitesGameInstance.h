/******************************************************************************************************************************************
	Team: ArtLess Games - Section 010
	
	Name: Vrund Soni
	
	Module: Level Management System
	
	Description: The 'UAG_ColdNitesGameInstance' class is the part of level management system module. This class is responsible for: 
				     - To determine which next level to load when a certain level is completed.
				     - To not allow the player to go to the next level if the current level is not completed.
				     - To save and load the completed levels progress.
				       (The game will save the progress each time when a level is completed).
********************************************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AG_ColdNitesGameInstance.generated.h"

UCLASS()
class AG_COLDNITES_API UAG_ColdNitesGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UAG_ColdNitesGameInstance();

private:
	TArray<int> CompletedLevels;

	FString LevelBaseString;
	FString SaveSlotName;
	
	int UserIndex;

public:
	bool IsLevelUnlocked(int Level);
	
	void NotifyLevelCompleted(FString LevelName);

	void SaveGame();
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "AG_Levels")
	void OpenNextLevel();

	UFUNCTION(BlueprintCallable, Category = "AG_Levels")
	void OpenSameLevel();

	UFUNCTION(BlueprintCallable, Category = "AG_Levels")
	void OpenSelectedLevel(int Level);

protected:
	virtual void Init() override;

//Scoring System
private:
	const uint8 TotalAvailableStars = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Levels")
	TArray<uint16> MinimunRequiredTurnsForLevel;
	
	uint16 NumberOfTurns = 0;

public:
	uint16 TotalTurnPerformed = 0;
	uint8 TotalCollectedStars = 0;
	uint8 StarsCollectedPerLevel = 0;
	void ResetScoringParameters();
};