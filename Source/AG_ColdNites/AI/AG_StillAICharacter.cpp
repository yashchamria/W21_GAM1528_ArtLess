#include "AG_StillAICharacter.h"

#include "AG_ColdNites/GameMode/AG_ColdNitesGameModeBase.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"

AAG_StillAICharacter::AAG_StillAICharacter()
{
}

void AAG_StillAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_StillAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsActorInRange("PlayableCharacter", GetActorForwardVector(), 1))
	{
		if (GameMode->GetTurnState() == TurnState::IsAITurn)
		{
			MoveForward();
			PlayerCharacter->KnockOut();
		}
	}
}
