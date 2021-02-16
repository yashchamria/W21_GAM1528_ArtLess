// Fill out your copyright notice in the Description page of Project Settings.

#include "AG_PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "../Pickup/PickupActor.h"
#include "../Pickup/InventoryComponent.h"

// Sets default values
AAG_PlayerCharacter::AAG_PlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("/Game/Assets/M_Cursor_Decal"));
	//if (DecalMaterialAsset.Succeeded())
	{
		//CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	PickupSphere = CreateDefaultSubobject<USphereComponent>("Pickup Sphere");
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetSimulatePhysics(false);
	PickupSphere->SetCollisionProfileName("OverlapAll");
	PickupSphere->SetSphereRadius(100.f);
	PickupSphere->SetupAttachment(RootComponent);

	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AAG_PlayerCharacter::BeginOverlap);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Player Inventory");

	ItemHolder = CreateDefaultSubobject<USceneComponent>("ItemHolder");
	ItemHolder->AttachTo(GetRootComponent());
	ItemHolder->SetRelativeLocation(FVector(0, 0, 150.f));
}


void AAG_PlayerCharacter::Pickup()
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

void AAG_PlayerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Pickup();
}

void AAG_PlayerCharacter::NextInventoryItem()
{
	InventoryComponent->NextInventoryItem();
}

void AAG_PlayerCharacter::PreviousInventoryItem()
{
	InventoryComponent->PreviousInventoryItem();
}

void AAG_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CursorToWorld is Nullptr"));
	}
}

