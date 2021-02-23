// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseGridClasses/AG_BaseGridCharacter.h"
#include "AG_TempAI.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_TempAI : public AAG_BaseGridCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_Components")
		class UStaticMeshComponent* AG_Mesh;
	
	float TurnTimer;
	
public:
	// Sets default values for this pawn's properties
	AAG_TempAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
