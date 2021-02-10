// Copyright Epic Games, Inc. All Rights Reserved.


#include "AG_ColdNitesGameModeBase.h"
#include "AG_PlayerController.h"
#include "AG_PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"


AAG_ColdNitesGameModeBase::AAG_ColdNitesGameModeBase()
{
	PlayerControllerClass = AAG_PlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_AG_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
