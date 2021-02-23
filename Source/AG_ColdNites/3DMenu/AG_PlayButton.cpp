// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_PlayButton.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAG_PlayButton::AAG_PlayButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = ButtonMesh;
	ButtonMesh->SetSimulatePhysics(false);

	ButtonMesh->OnClicked.AddDynamic(this, &AAG_PlayButton::OnPlayClicked);
}

// Called when the game starts or when spawned
void AAG_PlayButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAG_PlayButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}