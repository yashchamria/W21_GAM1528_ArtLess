/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Vrund Soni

 Module: 3D Game Menu Module

 Description - Empty GameMode for the GameMenu Level.
*******************************************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AG_ColdNitesUIGameMode.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_ColdNitesUIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAG_ColdNitesUIGameMode();
	
	virtual void BeginPlay() override;
};
