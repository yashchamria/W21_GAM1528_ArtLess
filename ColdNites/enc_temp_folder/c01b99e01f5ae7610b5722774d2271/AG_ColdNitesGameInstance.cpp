#include "AG_ColdNitesGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DefaultValueHelper.h"

void UAG_ColdNitesGameInstance::OpenNextLevel()
{
	FString NextLevelToLoad = "AG_ColdNites_Level0";
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	int NextLevelNum;
	FDefaultValueHelper::ParseInt(CurrentLevelName.RightChop(NextLevelToLoad.Len() - 1), NextLevelNum);

	NextLevelNum++;
	NextLevelToLoad.AppendInt(NextLevelNum);

	if (!NextLevelToLoad.IsEmpty())
	{
		int a = 0;
		a++;

		UE_LOG(LogTemp, Warning, TEXT("NEXT LVL NUM : %d"), NextLevelNum);

		UGameplayStatics::OpenLevel(this, FName(NextLevelToLoad));
	}
}

void UAG_ColdNitesGameInstance::OpenSameLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	
	UE_LOG(LogTemp, Warning, TEXT("LVL-NAME: %s"), *CurrentLevelName);
	
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
