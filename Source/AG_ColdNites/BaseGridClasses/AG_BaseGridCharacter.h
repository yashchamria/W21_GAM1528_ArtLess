#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AG_BaseGridCharacter.generated.h"

class AAG_ColdNitesGameModeBase;

UENUM()
enum class AG_AnimationStates : uint8
{
	Idle		 UMETA(DisplayName = "Idle"),
	Walk		 UMETA(DisplayName = "Walk"),
	Rotation	 UMETA(DisplayName = "Rotation"),
	PickUp		 UMETA(DisplayName = "PickUp"),
	Attack		 UMETA(DisplayName = "Attack"),
};

UCLASS()
class AG_COLDNITES_API AAG_BaseGridCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAG_BaseGridCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

///---------------------------------------Character Setup----------------------------------------------------------///
public:
	class AAG_TileMap* TileMap;

	void MoveTile(FVector DirectionVector, uint32 TileLeap = 1);
	
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();

	bool bRotate = false;
	bool bWalk = false;
	
	FVector TargetTileWorldLocation;
	FVector TargetDistance = FVector::ZeroVector;
	FVector TargetDirection = FVector::ZeroVector;
	FRotator TargetRotation = FRotator::ZeroRotator;


	//Animation Stuff ---> No Implementation Yet
	bool bAnimate = true;
	void Animate();
	void SetAnimation(AG_AnimationStates NewState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AG_Animation")
		AG_AnimationStates CurrentAnimationState = AG_AnimationStates::Idle;

	UFUNCTION(CallInEditor, Category = "AG_")
	void AutoRepositionToTileCenter(FIntPoint TileCoord);

	
private:
	float ErrorRange = 0.0f;

protected:
	AAG_ColdNitesGameModeBase* GameMode;
};
