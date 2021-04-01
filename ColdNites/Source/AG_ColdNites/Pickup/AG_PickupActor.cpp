#include "AG_PickupActor.h"
#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/Pickup/AG_InventoryComponent.h"

AAG_PickupActor::AAG_PickupActor()
{
	CollectDelay = 1.65f;
}

void AAG_PickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_PickupActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + ActorHeight));
}

void AAG_PickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanFloat)
	{
		FloatingEffect(DeltaTime);
	}
	
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
			PlayerCharacter->InventoryComponent->AddToInventory(this);
		}
	}
}

void AAG_PickupActor::FloatingEffect(float delta)
{
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + delta) - FMath::Sin(RunningTime));
	NewLocation.Z += (DeltaHeight * MoveOnZ);

	//Increment RunningTime
	RunningTime += delta * Speed;
	SetActorLocation(NewLocation);
}

void AAG_PickupActor::Disable()
{
	UnRegisterToTileMap();
	SetActorHiddenInGame(true);
}

void AAG_PickupActor::Enable()
{
	SetActorHiddenInGame(false);
}