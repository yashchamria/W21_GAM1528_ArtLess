// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AG_PlayerCharacter.generated.h"


UCLASS()
class AG_COLDNITES_API AAG_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAG_PlayerCharacter();
	
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

};
