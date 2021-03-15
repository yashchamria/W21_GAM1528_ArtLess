/******************************************************************************************************************

Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  BaseCharacter (For Both AIBase and Playable Characters)

 Description - All the character movement in the game are (TileMap)Grid-Base. Also all the actors are responsible for registering and uinregister themselves to the TileMap.
			   This BaseGridCharacter supports all the movement, actions, animation and registration to the TileMap.
			   So any inheriting Player or AI don't have to worry about Grid-Base Math or registration system.
			   
******************************************************************************************************************/


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AG_BaseGridCharacter.generated.h"


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
class AG_COLDNITES_API	AAG_BaseGridCharacter : public ACharacter
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
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileComponents")
	//	class USceneComponent* BaseRootTransformation;
	
	class AAG_TileMap* TileMap;

	class AAG_ColdNitesGameModeBase* GameMode;
	
	void MoveTile(FVector DirectionVector, uint32 TileLeap = 1);
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();

	void Rotate(float Rotation);
	
	void KnockOut(FVector FallDirection);
	void OnKnockOut(FRotator KnockOutAngle);
	
	FRotator KnockedOutAngle = FRotator::ZeroRotator;

	bool bWalk = false;
	bool bRotate = false;
	bool bKnockOut = false;
	bool bDestroy = false;

	bool bShouldRegister = true;
	bool bShouldDestroy = true;

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

	UFUNCTION()
	void AutoRepositionToTileCenter(FIntPoint TileCoord);

	virtual void ResetOnTurnEnd();
	
private:
	float ErrorRange = 0.0f;
	float KnockOutDelay = 0.0f;
	float DestroyDelay = 0.0f;
	bool bAlreadyRotated = false;

//Temp Hack to display desired mesh without skeletal animation
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_Components")
		class UStaticMeshComponent* AG_TempMesh;

	//Audio Stuff ---> No Proper Implementation Yet
	//UPROPERTY(VisibleAnywhere, Category = "AG_Walk")
	//	class USoundBase* WalkSound;
	
	//void WalkSoundEffect();
};
