/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  AI (For Both AIBase and Player)

 Description - StillAI is the most basic AI in the game. It only moves when the player is in front of the AI.

******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"
#include "AG_StillAICharacter.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_StillAICharacter : public AAG_AIBaseGridCharacter
{
	GENERATED_BODY()

public:
	AAG_StillAICharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
