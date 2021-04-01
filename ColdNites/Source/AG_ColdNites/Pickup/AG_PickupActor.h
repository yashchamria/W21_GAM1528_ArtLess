/******************************************************************************************************************
Team - ArtLess Games - Section 010
Name - Xiyang Chen
 Module:  Inventory System
 Description - The PickupActor inherits from the BaseGridActor.
			   This class will be the base class for all the future pickups in the game.
			   Also, added a floating effect.
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

	void FloatingEffect(float delta);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Property")
		bool bCanFloat = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Property")
		int ActorHeight = 10.0f;
	
	void Disable();
	void Enable();

private:
	bool bCollected = false;
	
	bool bTriggerCollection = false;
	float CollectDelay = 2.65;
	
	//Floating Variables
	float RunningTime = 0.0f;
	float MoveOnZ = 16.0f;
	float Speed = 5.0f;
};