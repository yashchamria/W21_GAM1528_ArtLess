// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AG_COLDNITES_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddToInventory(class APickupActor* pickup);

	int GetInventoryCount();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual void NextInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual void PreviousInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		class APickupActor* GetCurrentInventory() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class APickupActor* CurrentInventoryItem;

	void EquipNewInventoryItem(APickupActor* NewItem);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray< class APickupActor* > Inventory;

	void ResetCurrentInventory();
		
};
