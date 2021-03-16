/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Xiyang Chen

 Module:  Inventory

 Description -	The PickupActor will be stored in the inventory
				
				The inventory can equip the PickupActor using PageUp and PageDown Keys
******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AG_COLDNITES_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void AddToInventory(class APickupActor* pickup);

	int GetInventoryCount();

	UFUNCTION(BlueprintCallable, Category = "AG_Inventory")
		virtual void NextInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "AG_Inventory")
		virtual void PreviousInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "AG_Inventory")
		class APickupActor* GetCurrentInventory() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_Inventory")
		class APickupActor* CurrentInventoryItem;

	void EquipNewInventoryItem(APickupActor* NewItem);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray< class APickupActor* > Inventory;

	void ResetCurrentInventory();
		
};
