#include "AG_ColdNitesGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DefaultValueHelper.h"

void UAG_ColdNitesGameInstance::OpenNextLevel()
{
	FString NextLevelToLoad = "AG_ColdNites_Level_";
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);

	int NextLevelNum;
	FDefaultValueHelper::ParseInt(CurrentLevelName.RightChop(NextLevelToLoad.Len()), NextLevelNum);

	NextLevelNum++;
	NextLevelToLoad.AppendInt(NextLevelNum);

	UE_LOG(LogTemp, Warning, TEXT("LVL-NAME : %s"), *NextLevelToLoad);
	UGameplayStatics::OpenLevel(this, FName(NextLevelToLoad));
}

void UAG_ColdNitesGameInstance::OpenSameLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	
	UE_LOG(LogTemp, Warning, TEXT("LVL-NAME: %s"), *CurrentLevelName);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
