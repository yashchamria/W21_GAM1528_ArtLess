#include "AG_ColdNitesGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DefaultValueHelper.h"

UAG_ColdNitesGameInstance::UAG_ColdNitesGameInstance()
{
	LevelBaseString = "AG_ColdNites_Level_";
}

void UAG_ColdNitesGameInstance::OpenNextLevel()
{
	FString NextLevelToLoad = LevelBaseString;
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	int LevelNum;
	FDefaultValueHelper::ParseInt(CurrentLevelName.RightChop(LevelBaseString.Len()), LevelNum);

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
		UE_LOG(LogTemp, Warning, TEXT("UNLOCK PREVIOUS LEVELS!"));
	}

	UE_LOG(LogTemp, Warning, TEXT("LVLS COMPLETED : %d"), CompletedLevels.Num());
}

void UAG_ColdNitesGameInstance::NotifyLevelCompleted(FString LevelName)
{
	int LevelNum;
	FDefaultValueHelper::ParseInt(LevelName.RightChop(LevelBaseString.Len()), LevelNum);

	CompletedLevels.AddUnique(LevelNum);

	//for (int completedLevel : CompletedLevels)
	//{
	//	if (completedLevel != LevelNum)
	//	{
	//		CompletedLevels.Push(LevelNum);
	//	}
	//}

	UE_LOG(LogTemp, Warning, TEXT("LVL COMPLETED : %d"), LevelNum);
	UE_LOG(LogTemp, Warning, TEXT("TOTAL LVLS COMPLETED : %d"), CompletedLevels.Num());
}

bool UAG_ColdNitesGameInstance::IsLevelUnlocked(int Level)
{
	if (Level == 1) //return true as the 1st level will always be unlocked
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
