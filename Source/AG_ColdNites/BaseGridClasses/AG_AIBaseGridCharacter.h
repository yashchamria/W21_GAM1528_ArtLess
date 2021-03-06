/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  AI (For Both AIBase and Player)

 Description - This AIBaseGridCharacter handles all the Generic AI functions such as Player Detection, Catching the player, etc.
			   So any inheriting AI classes don't have to do repetitive code.

******************************************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridCharacter.h"
#include "AG_AIBaseGridCharacter.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_AIBaseGridCharacter : public AAG_BaseGridCharacter
{
	GENERATED_BODY()

public:
	AAG_AIBaseGridCharacter();
	class AAG_PlayableCharacter* PlayerCharacter;
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();

	bool bIsPlayerInRange = false;
	bool IsActorInRange(FName ActorTag, FVector InDirection, uint32 TileRange);
	void DetectPlayer(uint32 TileRange = 1);
	void CatchPlayer();

	bool bIsAITurn = false;
};
