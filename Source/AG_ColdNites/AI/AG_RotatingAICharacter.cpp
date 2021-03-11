#include "AG_RotatingAICharacter.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"

AAG_RotatingAICharacter::AAG_RotatingAICharacter()
{
	Tags.Add("AG_RotatingAI");
}

void AAG_RotatingAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_RotatingAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAITurn)
	{
		if (IsActorInRange("AG_PlayableCharacter", GetActorForwardVector(), 1))
		{
			MoveForward();
			PlayerCharacter->KnockOut(GetActorForwardVector());
		}
		else
		{
			Rotate(180.0f);
		}
	}
}

