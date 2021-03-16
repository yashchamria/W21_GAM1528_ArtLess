/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Jonathan Sime

 Module:  Player Character

 Description -

*******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Xiyang Chen

 Module:  Player Character

 Description - A Spherecomponent is used for overlapping detection of PickupActors.
			   After pickup, the PickupActor will be stored in the inventory.
			   The inventory can equip the PickupActor using PageUp and PageDown Keys. 

******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridCharacter.h"
#include "AG_PlayableCharacter.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_PlayableCharacter : public AAG_BaseGridCharacter
{
	GENERATED_BODY()

public:
	AAG_PlayableCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();

///---------------------------------------Inventory Setup----------------------------------------------------------///
public:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_Pickup")
		class USphereComponent* PickupSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_Pickup")
		class USceneComponent* ItemHolder;

	UPROPERTY(VisibleAnywhere, Category = "AG_PickUp")
		class USoundBase* PickUpSound;
	
	class UInventoryComponent* InventoryComponent;

	void NextInventoryItem();
	void PreviousInventoryItem();
};
