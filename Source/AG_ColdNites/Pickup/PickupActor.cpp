#include "PickupActor.h"
#include "Components/SphereComponent.h"
#include <Components/SkeletalMeshComponent.h>
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
	PickupSphere->SetSphereRadius(100.f);

	SetRootComponent(PickupSphere);

	ActorTopMesh = CreateDefaultSubobject<UStaticMeshComponent>("Sphere Mesh");
	ActorTopMesh->SetupAttachment(GetRootComponent());
	ActorTopMesh->SetCollisionProfileName("NoCollision");
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
}

