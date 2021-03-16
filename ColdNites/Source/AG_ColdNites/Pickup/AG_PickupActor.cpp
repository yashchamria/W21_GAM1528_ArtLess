/******************************************************************************************************************
 
---->	Working Prototype of the class inheriting from BaseGridActor. Will be expanded more in future iteration of the game.
---->	Doesn't relies on OnHit or Overlap. Event are handled based on the BaseGridActor provided functions and it's close integration with the TileMap.

******************************************************************************************************************/

#include "AG_PickupActor.h"

AAG_PickupActor::AAG_PickupActor()
{
}

void AAG_PickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_PickupActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_PickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCollected)
	{
		CollectDelay -= DeltaTime;

		if (CheckPlayerOnTheTile() && !bTriggerCollection)
		{
			bTriggerCollection = true;
			CollectDelay = 1.65f;
		}
		
		if (CollectDelay < 0.0f && bTriggerCollection)
		{
			bCollected = true;

			//Do Something
			DeleteGridActor();
		}
	}
}
