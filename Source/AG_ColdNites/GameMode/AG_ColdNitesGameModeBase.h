// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AG_ColdNitesGameModeBase.generated.h"

/**
 * 
 */

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
