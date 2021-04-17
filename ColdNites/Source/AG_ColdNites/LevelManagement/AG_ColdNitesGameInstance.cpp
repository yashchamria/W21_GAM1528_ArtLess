#include "AG_ColdNitesGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DefaultValueHelper.h"
#include "AG_ColdNites/LevelManagement/AG_ColdNitesSaveGame.h"

UAG_ColdNitesGameInstance::UAG_ColdNitesGameInstance()
{
	LevelBaseString = "AG_ColdNites_Level_";
	SaveSlotName = "SaveSlot_One";
	UserIndex = 0;
}

void UAG_ColdNitesGameInstance::Init()
{
	Super::Init();
	
	if (LevelMaximumStarPossible.Num() > 0)
	{
		for (int NumStars : LevelMaximumStarPossible)
		{
			TotalMaximumStars += NumStars;
		}
	}

	LoadGame();
}

uint16 UAG_ColdNitesGameInstance::GetLevelMinimunTurnRequired()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	int CurrentLevelNum;
	FDefaultValueHelper::ParseInt(CurrentLevelName.RightChop(LevelBaseString.Len()), CurrentLevelNum);
	
	return LevelMinimunRequiredTurns[CurrentLevelNum - 1];
}

void UAG_ColdNitesGameInstance::OpenNextLevel()
{
	FString NextLevelToLoad = LevelBaseString;
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	int CurrentLevelNum;
	FDefaultValueHelper::ParseInt(CurrentLevelName.RightChop(LevelBaseString.Len()), CurrentLevelNum); //this will get Level num of the level that you just completed

	int NextLevelNum = CurrentLevelNum + 1; 
	NextLevelToLoad.AppendInt(NextLevelNum);

	UGameplayStatics::OpenLevel(this, FName(NextLevelToLoad));
}

void UAG_ColdNitesGameInstance::OpenSameLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void UAG_ColdNitesGameInstance::OpenSelectedLevel(int Level)
{
	FString LevelToLoad = LevelBaseString;

	if (IsLevelUnlocked(Level))
	{
		LevelToLoad.AppendInt(Level);
		UGameplayStatics::OpenLevel(this, FName(LevelToLoad));
	}
}

int UAG_ColdNitesGameInstance::GetTotalMaximumStars()
{
	return TotalMaximumStars;
}

int UAG_ColdNitesGameInstance::GetTotalCollectedStars()
{
	return CollectedTotalStars.Num();
}

void UAG_ColdNitesGameInstance::AddStar(AG_StarType Star)
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	CollectedTotalStars.AddUnique(CurrentLevelName, Star);
}

void UAG_ColdNitesGameInstance::NotifyLevelCompleted(FString LevelName)
{
	int LevelNum;
	FDefaultValueHelper::ParseInt(LevelName.RightChop(LevelBaseString.Len()), LevelNum);

	CompletedLevels.AddUnique(LevelNum);

	SaveGame();
}

void UAG_ColdNitesGameInstance::SaveGame()
{
	UAG_ColdNitesSaveGame* SaveGameInstance = Cast<UAG_ColdNitesSaveGame>(UGameplayStatics::CreateSaveGameObject(UAG_ColdNitesSaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		SaveGameInstance->CompletedLevels = CompletedLevels;
		SaveGameInstance->CollectedTotalStars = CollectedTotalStars;
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
		CollectedTotalStars = LoadedGameInstance->CollectedTotalStars;
		UE_LOG(LogTemp, Warning, TEXT("GameLoaded!"));
	}
}

bool UAG_ColdNitesGameInstance::IsLevelUnlocked(int Level)
{
	if (Level == 1) //return true as the 1st level is always unlocked
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