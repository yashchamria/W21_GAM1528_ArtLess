/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Vrund Soni

 Module:

 Description -

******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_BaseGridActor.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_BaseGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_BaseGridActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_Components")
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_Components")
		class UStaticMeshComponent* Mesh;

	class AAG_TileMap* TileMap;
	
	FIntPoint CurrentTileCoord;
	FVector TargetTileWorldLocation;

	bool bAutoRepositionToTileCenter = true;
protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	void AutoRepositionToTileCenter();

	virtual void Delete();
};
