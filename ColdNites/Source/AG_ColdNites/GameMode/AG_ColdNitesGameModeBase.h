/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Jonathan Sime

 Module:  Game Mode Base

 Description - GameModeBase handles TurnStates.
			   FinishTurn() is called by the last object to update during it's turn to continue the turns.
			   AllowPlayerMove() allows the player to move once their turn starts.

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
