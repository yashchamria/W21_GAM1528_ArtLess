#include "AG_ColdNitesGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DefaultValueHelper.h"
#include "AG_ColdNites/SaveAndLoad/AG_ColdNitesSaveGame.h"

UAG_ColdNitesGameInstance::UAG_ColdNitesGameInstance()
{
	LevelBaseString = "AG_ColdNites_Level_";
	SaveSlotName = "SaveSlot_One";
	UserIndex = 0;
}

void UAG_ColdNitesGameInstance::Init()
{
	Super::Init();

	LoadGame();
}

void UAG_ColdNitesGameInstance::OpenNextLevel()
{
	FString NextLevelToLoad = LevelBaseString;
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	int LevelNum;
	FDefaultValueHelper::ParseInt(CurrentLevelName.RightChop(LevelBaseString.Len()), LevelNum); //this will get Level num of the level that you just completed

	LevelNum++; // increment to set number to next level number
	NextLevelToLoad.AppendInt(LevelNum);

	UE_LOG(LogTemp, Warning, TEXT("LVL-NAME : %s"), *NextLevelToLoad);
	UGameplayStatics::OpenLevel(this, FName(NextLevelToLoad));
}

void UAG_ColdNitesGameInstance::OpenSameLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	
	UE_LOG(LogTemp, Warning, TEXT("LVL-NAME: %s"), *CurrentLevelName);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void UAG_ColdNitesGameInstance::OpenSelectedLevel(int Level)
{
	FString LevelToLoad = LevelBaseString;

	if ( IsLevelUnlocked(Level) )
	{
		LevelToLoad.AppendInt(Level);
		UGameplayStatics::OpenLevel(this, FName(LevelToLoad));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TRYING TO OPEN LEVEL: %d"), Level);
		UE_LOG(LogTemp, Warning, TEXT("UNLOCK PREVIOUS LEVELS!"));

	}

	UE_LOG(LogTemp, Warning, TEXT("LVLS COMPLETED : %d"), CompletedLevels.Num());
}


void UAG_ColdNitesGameInstance::NotifyLevelCompleted(FString LevelName)
{
	int LevelNum;
	FDefaultValueHelper::ParseInt(LevelName.RightChop(LevelBaseString.Len()), LevelNum);

	CompletedLevels.AddUnique(LevelNum);

	UE_LOG(LogTemp, Warning, TEXT("LVL COMPLETED : %d"), LevelNum);
	UE_LOG(LogTemp, Warning, TEXT("TOTAL LVLS COMPLETED : %d"), CompletedLevels.Num());

	SaveGame();
}

void UAG_ColdNitesGameInstance::SaveGame()
{
	UAG_ColdNitesSaveGame* SaveGameInstance = Cast<UAG_ColdNitesSaveGame>(UGameplayStatics::CreateSaveGameObject(UAG_ColdNitesSaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		SaveGameInstance->CompletedLevels = CompletedLevels;
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex))
		{
			UE_LOG(LogTemp, Warning, TEXT("GameSaved!"));
		}
	}
}

void UAG_ColdNitesGameInstance::LoadGame()
{
	UAG_ColdNitesSaveGame* LoadedGameInstance = Cast<UAG_ColdNitesSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

	if (LoadedGameInstance)
	{
		CompletedLevels = LoadedGameInstance->CompletedLevels;
		UE_LOG(LogTemp, Warning, TEXT("GameLoaded!"));
	}
}

bool UAG_ColdNitesGameInstance::IsLevelUnlocked(int Level)
{
	if (Level == 1) //return true as the 1st level needs to be always unlocked
	{
		return true;
	}

	for (int completedLevel : CompletedLevels)
	{
		if (completedLevel == (Level - 1))
		{
			return true;
		}
	}

	return false;
}