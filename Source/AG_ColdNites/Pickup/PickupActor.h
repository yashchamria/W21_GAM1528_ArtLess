// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

UCLASS()
class AG_COLDNITES_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	UPROPERTY(EditAnywhere, Category = PickupCollision)
		class USphereComponent* PickupSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		class UStaticMeshComponent* ActorTopMesh;

	UFUNCTION()
		virtual void Disable();

	UFUNCTION()
		virtual void Enable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
