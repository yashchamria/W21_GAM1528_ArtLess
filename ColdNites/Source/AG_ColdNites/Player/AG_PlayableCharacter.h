/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Jonathan Sime

 Module:  Player Character

 Description - PlayableCharacter inherits from BaseGridCharacter.
			   Move methods call the parent's move methods for movement code.
			   Move methods are called by the PlayerController.

*******************************************************************************************************************/

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
	class UAG_InventoryComponent* InventoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_Pickup")
		class USceneComponent* ItemHolder;

	void NextInventoryItem();
	void PreviousInventoryItem();

///---------------------------------------Audio Setup----------------------------------------------------------///
	//UPROPERTY(VisibleAnywhere, Category = "AG_PickUp")
	//	class USoundBase* PickUpSound;
};
