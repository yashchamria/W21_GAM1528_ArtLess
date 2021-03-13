#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

UCLASS()
class AG_COLDNITES_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupActor();

	UPROPERTY(EditAnywhere, Category = "AG_PickupComponents")
		class USphereComponent* PickupSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_PickupComponents")
		class UStaticMeshComponent* ActorTopMesh;

	UFUNCTION()
		virtual void Disable();

	UFUNCTION()
		virtual void Enable();

protected:
	virtual void BeginPlay() override;
	float RunningTime;
	float MoveOnZ = 20.0f;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Movement)
		float Speed = 5.0f;

};
