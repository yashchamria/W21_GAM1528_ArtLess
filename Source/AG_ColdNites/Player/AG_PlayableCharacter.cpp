#include "AG_PlayableCharacter.h"

#include "Components/SphereComponent.h"
#include "AG_ColdNites/Pickup/PickupActor.h"
#include "../Pickup/InventoryComponent.h"

AAG_PlayableCharacter::AAG_PlayableCharacter()
{
	PickupSphere = CreateDefaultSubobject<USphereComponent>("Pickup Sphere");
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetSimulatePhysics(false);
	PickupSphere->SetCollisionProfileName("OverlapAll");
	PickupSphere->SetSphereRadius(100.f);
	PickupSphere->SetupAttachment(RootComponent);
	
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AAG_PlayableCharacter::BeginOverlap);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Player Inventory");

	ItemHolder = CreateDefaultSubobject<USceneComponent>("ItemHolder");
	ItemHolder->AttachTo(GetRootComponent());
	ItemHolder->SetRelativeLocation(FVector(0, 0, 150.f));
}

void AAG_PlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_PlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAG_PlayableCharacter::MoveRight()
{
	Super::MoveRight();
}

void AAG_PlayableCharacter::MoveLeft()
{
	Super::MoveLeft();
}

void AAG_PlayableCharacter::MoveForward()
{
	Super::MoveForward();
}

void AAG_PlayableCharacter::MoveBackward()
{
	Super::MoveBackward();
}

void AAG_PlayableCharacter::NextInventoryItem()
{
	InventoryComponent->NextInventoryItem();
}

void AAG_PlayableCharacter::PreviousInventoryItem()
{
	InventoryComponent->PreviousInventoryItem();
}

void AAG_PlayableCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> pickups;

	PickupSphere->GetOverlappingActors(pickups, APickupActor::StaticClass());

	if (pickups.Num() > 0)
	{
		for (int i = 0; i < pickups.Num(); i++)
		{
			InventoryComponent->AddToInventory(Cast<APickupActor>(pickups[i]));
		}
	}
}