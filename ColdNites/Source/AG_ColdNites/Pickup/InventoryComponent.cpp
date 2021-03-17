#include "InventoryComponent.h"
#include "AG_ColdNites/Pickup/AG_PickupActor.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::AddToInventory(AAG_PickupActor* pickup)
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
	AAG_PickupActor* InventoryItemToEquip = nullptr;

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
	AAG_PickupActor* InventoryItemToEquip = nullptr;
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

AAG_PickupActor* UInventoryComponent::GetCurrentInventory() const
{
	return CurrentInventoryItem;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::EquipNewInventoryItem(AAG_PickupActor* NewItem)
{
	if (CurrentInventoryItem)
	{
		CurrentInventoryItem->Disable();
		CurrentInventoryItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	if (NewItem)
	{
		NewItem->Enable();

		AAG_PlayableCharacter* OwningActor = Cast<AAG_PlayableCharacter>(GetOwner());
		NewItem->AttachToComponent(OwningActor->ItemHolder, FAttachmentTransformRules::SnapToTargetIncludingScale, "AttachPoint");
	}
	CurrentInventoryItem = NewItem;
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::ResetCurrentInventory()
{
	CurrentInventoryItem = nullptr;
}

