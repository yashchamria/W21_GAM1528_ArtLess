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

class AAG_PlayerController;

enum TurnState : uint32
{
	IsPendingNewTurn    UMETA(DisplayName = "IsPendingNewTurn"),
	IsNewTurn			UMETA(DisplayName = "IsNewTurn"),
	IsPlayerTurn		UMETA(DisplayName = "IsPlayerTurn"),
	IsAITurn			UMETA(DisplayName = "IsAITurn"),
	IsEndTurn			UMETA(DisplayName = "IsEndTurn"),
};


UCLASS()
class AG_COLDNITES_API AAG_ColdNitesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	int TurnState;

	AAG_PlayerController* PlayerController;

public:
	AAG_ColdNitesGameModeBase();

	virtual void BeginPlay() override;
	
	void FinishTurn();

	void NewTurn();
	
	void EndTurn();

	void AllowPlayerMove();
	
	int GetTurnState() { return TurnState; }
};
