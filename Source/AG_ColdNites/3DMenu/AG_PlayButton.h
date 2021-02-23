// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_PlayButton.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_PlayButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAG_PlayButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Menu")
		class UStaticMeshComponent* ButtonMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
