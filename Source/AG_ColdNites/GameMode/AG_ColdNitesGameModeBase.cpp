// Copyright Epic Games, Inc. All Rights Reserved.


#include "AG_ColdNitesGameModeBase.h"
#include "../Player/AG_PlayerController.h"
#include "UObject/ConstructorHelpers.h"

AAG_ColdNitesGameModeBase::AAG_ColdNitesGameModeBase()
{
	PlayerControllerClass = AAG_PlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_AG_PlayableCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
