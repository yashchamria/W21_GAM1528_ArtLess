// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AG_TestChar.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_TestChar : public ACharacter
{
	GENERATED_BODY()

public:
	AAG_TestChar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller");
	class AAG_PlayerController* MainPlayerController;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EscKeyDown();
};
