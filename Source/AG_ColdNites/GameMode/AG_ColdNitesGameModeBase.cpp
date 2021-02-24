#include "AG_ColdNitesGameModeBase.h"
#include "../Player/AG_PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AAG_ColdNitesGameModeBase::AAG_ColdNitesGameModeBase()
{
	PlayerControllerClass = AAG_PlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_AG_PlayableCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	TurnState = TurnState::IsNewTurn;
}

void AAG_ColdNitesGameModeBase::BeginPlay()
{
	PlayerController = Cast<AAG_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	FinishTurn();
}

void AAG_ColdNitesGameModeBase::FinishTurn()
{
	TurnState++;

	switch(TurnState)
	{		
	case TurnState::IsNewTurn:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("New Turn"));
		NewTurn();
		break;
		
	case TurnState::IsPlayerTurn:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Player Turn"));
		AllowPlayerMove();
		break;
		
	case TurnState::IsAITurn:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AI Turn"));
		break;
		
	case TurnState::IsEndTurn:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("End Turn"));
		EndTurn();
		break;

	default:
		break;
	}
}

void AAG_ColdNitesGameModeBase::NewTurn()
{
	// Actors or Objects needed to be updated before turn starts
	// The last Actor or Object updated should call FinishTurn()


	
	FinishTurn();
}

void AAG_ColdNitesGameModeBase::EndTurn()
{
	// Actors or Objects needed to be updated once turn has ended
	// The last Actor or Object updated should call FinishTurn()


	TurnState = TurnState::IsPendingNewTurn;
	FinishTurn();
}

void AAG_ColdNitesGameModeBase::AllowPlayerMove()
{
	PlayerController->SetCanMove(true);
}
