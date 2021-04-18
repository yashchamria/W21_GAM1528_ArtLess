/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  AI
 
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
	class AAG_PlayerController* PlayerController;
	class AAG_AITurnManager* AITurnManager;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();

	bool IsPlayerInRange();
	bool bIsPlayerInRange(uint32 TileRange = 1);
	bool IsActorInRange(FName ActorTag, FVector InDirection, uint32 TileRange = 1);
	void KnockOutPlayer(FVector ForwardDirection);

//Patrol AI variables
public:
	uint8 PatrolIndex = 0;
	
	FIntPoint CurrentPatrolTileCoord;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_PatrolProperty")
		bool CanPatrol = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_PatrolProperty", meta = (EditCondition = "CanPatrol"))
		TArray<FIntPoint> PatrolTileCoords;

};