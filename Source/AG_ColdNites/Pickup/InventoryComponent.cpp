// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "PickupActor.h"
#include "../AG_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInventoryComponent::AddToInventory(APickupActor* pickup)
{
	Inventory.AddUnique(pickup);
	pickup->Disable();
}

int UInventoryComponent::GetInventoryCount()
{
	return Inventory.Num();
}

void UInventoryComponent::NextInventoryItem()
{
	if (Inventory.Num() == 0)
	{
		return;
	}
	APickupActor* InventoryItemToEquip = nullptr;

	int32 Index = 0;
	if (CurrentInventoryItem)
	{
		Inventory.Find(CurrentInventoryItem, Index);
		Index += 1;
	}
	if (Index < Inventory.Num())
	{
		InventoryItemToEquip = Inventory[Index];
	}
	EquipNewInventoryItem(InventoryItemToEquip);
}

void UInventoryComponent::PreviousInventoryItem()
{
	if (Inventory.Num() == 0)
	{
		return;
	}
	APickupActor* InventoryItemToEquip = nullptr;
	int32 Index = Inventory.Num() - 1;
	if (CurrentInventoryItem != nullptr)
	{
		Inventory.Find(CurrentInventoryItem, Index);
		Index -= 1;
	}

	if (Index > -1)
	{
		InventoryItemToEquip = Inventory[Index];
	}
	EquipNewInventoryItem(InventoryItemToEquip);
}

APickupActor* UInventoryComponent::GetCurrentInventory() const
{
	return CurrentInventoryItem;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UInventoryComponent::EquipNewInventoryItem(APickupActor* NewItem)
{
	if (CurrentInventoryItem)
	{
		CurrentInventoryItem->Disable();
		CurrentInventoryItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	if (NewItem)
	{
		NewItem->Enable();

		AAG_PlayerCharacter* OwningActor = Cast<AAG_PlayerCharacter>(GetOwner());
		NewItem->AttachToComponent(OwningActor->ItemHolder,
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			"AttachPoint");
	}
	CurrentInventoryItem = NewItem;
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::ResetCurrentInventory()
{
	CurrentInventoryItem = nullptr;
}

