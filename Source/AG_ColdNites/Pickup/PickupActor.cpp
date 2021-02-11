// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/SphereComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include <Components/PrimitiveComponent.h>
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

