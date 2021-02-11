#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AG_PlayerCharacter.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAG_PlayerCharacter();
	
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	//*****PickUp Start******
	void Pickup();
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
		class USphereComponent* PickupSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
		class USceneComponent* ItemHolder;

	class UInventoryComponent* InventoryComponent;

	void NextInventoryItem();
	void PreviousInventoryItem();
	//*****PickUp End******
	
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

};
