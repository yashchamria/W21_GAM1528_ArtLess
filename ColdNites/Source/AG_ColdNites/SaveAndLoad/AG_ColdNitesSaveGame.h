/*************************************************************************************************************************************
    Team - ArtLess Games - Section 010
    
    Name - Vrund Soni
    
    Module - Level Management System
    
    Description - The 'UAG_ColdNitesSaveGame' class is a part level management system module. This class is responsible for
                  saving the counts of completed levels given by the Game Instance in an array of int called 'completedLevels'.
**************************************************************************************************************************************/
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
        TMultiMap<FString, AG_StarType> CollectedLevelStars;

    UPROPERTY(VisibleAnywhere, Category = "AG_SaveGame")
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = "AG_SaveGame")
        uint32 UserIndex;
};
