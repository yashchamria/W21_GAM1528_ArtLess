#include "PickupActor.h"
#include "Components/SphereComponent.h"
#include <Components/PrimitiveComponent.h>
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

APickupActor::APickupActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	PickupSphere->SetSimulatePhysics(false);
	PickupSphere->SetCollisionProfileName("OverlapAllDynamic");
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetSphereRadius(20.f);

	SetRootComponent(PickupSphere);

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Sphere Mesh");
	ActorMesh->SetupAttachment(GetRootComponent());
	ActorMesh->SetCollisionProfileName("NoCollision");	
}

void APickupActor::Disable()
{
	SetActorHiddenInGame(true);
	PickupSphere->SetActive(false);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickupActor::Enable()
{
	SetActorHiddenInGame(false);
	PickupSphere->SetActive(true);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APickupActor::BeginPlay()
{
	Super::BeginPlay();
}

void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * MoveOnZ;

	//Increment RunningTime
	RunningTime += DeltaTime * Speed;
	SetActorLocation(NewLocation);
}

