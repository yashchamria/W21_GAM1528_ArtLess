/******************************************************************************************************************
Team - ArtLess Games - Section 010
Name - Yash Chamria
 Module:  TileMap
 Description - TileMap is resoponsible for spawning the tiles in the world which makes the level possible.
			   It is possible to spawn any number of tiles on the fly through the editor. For example change 10x10 tile to 100x100 from editor itself.

			   Also we can set any properties for the tile through the editor. For instance making walkable, unwalkable, start, win, or other stuff.
			   Aesthetic changes can also be done in the inspector.

			   Tiles also keep track(register) of the actors standing on it which will be used for all the event throught the game.
			   Such as AI can ask the TileMap about the Player Location for Player Detection and visa versa.
			   Overall the main focus of the TileMap is to provide functionality and also make the level designers job easily.
******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_Tile.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_Tile : public AActor
{
	GENERATED_BODY()

public:
	AAG_Tile();

	//Tile Info
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileInfo")
		FVector Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileInfo")
		FIntPoint TileCoordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileInfo")
		FVector2D TileSize = FVector2D(250.0f, 250.0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileInfo")
		TArray<class AActor*> RegisteredActors;

	//Tile Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileComponents")
		class USceneComponent* TileRootTransformation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileComponents")
		class UStaticMeshComponent* TileMesh;

	//Tile Properties
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "AG_TileProperty")
		void AutoConfigurePropertyToggle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty")
		bool NullTile = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsStartTile = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsWalkable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsTransportable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsWinTile = false;

	//Tile Aesthetics
	UFUNCTION(CallInEditor, Category = "AG_TileAesthetic")
		void RotateMesh();


	void SetTileCoordinates(FIntPoint coord) { TileCoordinate.X = coord.X; TileCoordinate.Y = coord.Y; }

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Register(AActor* Actor);
	void UnRegister(AActor* Actor);
	bool IsRegistered(AActor* Actor);
	void WipeRegister();
};