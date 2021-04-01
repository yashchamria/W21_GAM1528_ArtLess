#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AG_ColdNitesSaveGame.generated.h"

UCLASS()
class AG_COLDNITES_API UAG_ColdNitesSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UAG_ColdNitesSaveGame();

    UPROPERTY(VisibleAnywhere, Category = "AG_SaveGame")
        TArray<int> CompletedLevels;

    UPROPERTY(VisibleAnywhere, Category = "AG_SaveGame")
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = "AG_SaveGame")
        uint32 UserIndex;
};
