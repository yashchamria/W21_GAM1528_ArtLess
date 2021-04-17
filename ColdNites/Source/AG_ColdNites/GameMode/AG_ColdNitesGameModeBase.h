/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Jonathan Sime

 Module:  Turn System Module (Replaced)

 Description - GameModeBase stores the TurnStates.
			   Turn System is handled by the EventManager class in the new system.
*******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AG_ColdNitesGameModeBase.generated.h"

//Turn System.
enum AG_TurnState : uint32
{
	IdleTurn			UMETA(DisplayName = "IdleTurn"),
	IsPlayerTurn		UMETA(DisplayName = "IsPlayerTurn"),
	IsAITurn			UMETA(DisplayName = "IsAITurn"),
};


UCLASS()
class AG_COLDNITES_API AAG_ColdNitesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAG_ColdNitesGameModeBase();

//Turn System.
private:
	AG_TurnState CurrentTurnState;

public:
	void SetCurrentTurnState(AG_TurnState NewTurnState) { CurrentTurnState = NewTurnState; }
	FORCEINLINE AG_TurnState GetCurrentTurnState() { return CurrentTurnState; }
};
