#include "AG_InventoryComponent.h"
#include "AG_ColdNites/Pickup/AG_PickupActor.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"


UAG_InventoryComponent::UAG_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> USB1(TEXT("Pickup Sound '/Game/Audio/UnCategorize/PickUp'"));
	PickUpSound = CreateDefaultSubobject<USoundBase>(TEXT("Pickup Sound"));
	if (USB1.Succeeded()) { PickUpSound = USB1.Object; }

	static ConstructorHelpers::FObjectFinder<USoundBase> USB2(TEXT("Inventory Sound '/Game/Audio/UnCategorize/Inventory_Switch'"));
	InventorySound = CreateDefaultSubobject<USoundBase>(TEXT("Inventory Sound"));
	if (USB2.Succeeded()) { InventorySound = USB2.Object; }
}

void UAG_InventoryComponent::AddToInventory(AAG_PickupActor* pickup)
{
	Inventory.AddUnique(pickup);
	pickup->Disable();
}

int UAG_InventoryComponent::GetInventoryCount()
{
	return Inventory.Num();
}

void UAG_InventoryComponent::NextInventoryItem()
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

void UAG_InventoryComponent::PreviousInventoryItem()
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

AAG_PickupActor* UAG_InventoryComponent::GetCurrentInventory() const
{
	return CurrentInventoryItem;
}

void UAG_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAG_InventoryComponent::EquipNewInventoryItem(AAG_PickupActor* NewItem)
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

void UAG_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAG_InventoryComponent::ResetCurrentInventory()
{
	CurrentInventoryItem = nullptr;
}
