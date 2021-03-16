/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - 

 Module: Work In Progress
 
 Description - The PickupActor inherits from the BaseGridActor.
			   This class will be the base class for all the future pickups in the game.
			   This class will later be modified as an essential part of the game mechanism.
******************************************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridActor.h"
#include "AG_PickupActor.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_PickupActor : public AAG_BaseGridActor
{
	GENERATED_BODY()

public:
	AAG_PickupActor();

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool bTriggerCollection = false;
	bool bCollected = false;
	float CollectDelay = 1.65;
};
