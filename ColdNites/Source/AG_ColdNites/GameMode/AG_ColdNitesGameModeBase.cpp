#include "AG_ColdNitesGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AAG_ColdNitesGameModeBase::AAG_ColdNitesGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_AG_PlayableCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//To prevent any major GamePlay event before EventManager's BeginPlay is called.
	CurrentTurnState = AG_TurnState::IdleTurn;
}
