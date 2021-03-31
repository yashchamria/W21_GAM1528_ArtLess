/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Vrund Soni

 Module: Base Classes
 
 Description - Created the body and implemented AutoReposition feature. Also, actor registers to the TileMap.
 
*******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

Module : Base Classes

Description - Removed the collision component. All the collision/overlaps for the BaseActor will be now handled by the TileMap Registeration System.
			  Added feature such Player or Actor Detection. Added Player variable. Also created some Registerion related helper functions.
			  
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_BaseComponents")
		class USceneComponent* BaseRootTransformation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_BaseComponents")
		class UStaticMeshComponent* BaseMesh;

	class AAG_TileMap* TileMap;
	class AAG_PlayableCharacter* PlayerCharacter;
	class AAG_PlayerController* PlayerController;

	FIntPoint CurrentTileCoord;
	FVector TargetTileWorldLocation;

	bool bAutoRepositionToTileCenter = true;
	
protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

	void AutoRepositionToTileCenter();

	bool CheckActorOnTheTile(FName ActorTag);

	bool CheckPlayerOnTheTile();

	void UnRegisterToTileMap();

	virtual void DeleteGridActor();
};