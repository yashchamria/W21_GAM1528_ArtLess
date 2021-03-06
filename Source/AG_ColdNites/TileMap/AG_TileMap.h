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
#include "AG_TileMap.generated.h"

UENUM()
enum class AG_TileProperty : uint8
{
	IsStartTile			 UMETA(DisplayName = "IsStartTile"),
	IsWalkable			 UMETA(DisplayName = "IsWalkable"),
	IsTransportable		 UMETA(DisplayName = "IsTransportable"),
	CanKill				 UMETA(DisplayName = "CanKill"),
	HasPickup			 UMETA(DisplayName = "HasPickup"),
	HasTriggerEvent		 UMETA(DisplayName = "HasTriggerEvent"),
	NullTile			 UMETA(DisplayName = "NullTile"),
	IsCrackable			 UMETA(DisplayName = "IsCrackable"),
	IsCracked			 UMETA(DisplayName = "IsCracked"),
	CanSlide			 UMETA(DisplayName = "CanSlide"),
	IsWinTile			 UMETA(DisplayName = "IsWinTile"),
};

UCLASS()
class AG_COLDNITES_API AAG_TileMap : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_TileMap();

	UPROPERTY(EditAnywhere, Category = "AG_TileMapProperty")
		uint32 Width;
	
	UPROPERTY(EditAnywhere, Category = "AG_TileMapProperty")
		uint32 Length;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_TileMapProperty")
		TArray<class AAG_Tile*> Tiles;
	
	UFUNCTION(CallInEditor, Category = "AG_TileMapProperty")
		void ClearTiles();

	UFUNCTION(CallInEditor, Category = "AG_TileMapProperty")
		void GenerateTiles();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_TileMapProperty")
		FVector2D TileSize = FVector2D(250.0f, 250.0);

	FIntPoint GetTileCoord(FVector WorldPosition);
	
	FIntPoint GetNextTileCoord(FVector CharacterLocation, FVector DirectionVector, uint32 TileLeap = 1);

	FVector GetTileWorldPosition(FIntPoint TileCoord);

	bool IsTileCoordVaild(FIntPoint TileCoord);
	bool IsTileNeighbouring(FIntPoint CheckCoord, FVector WorldPosition, FVector ForwardDirection, FVector RightDirection, uint32 TileLeap = 1);

	bool GetTileProperty(FIntPoint TileCoord, AG_TileProperty TileProperty);

	uint32 GetArrayIndexFromCoord(FIntPoint TileCoord);

	void Register(AActor* Actor, FIntPoint TileCoord);
	void UnRegister(AActor* Actor, FIntPoint TileCoord);
	bool IsRegistered(AActor* Actor, FIntPoint TileCoord);
	bool IsRegistered(FName ActorTag, FIntPoint TileCoord);
	AActor* GetAllRegisteredActors(FIntPoint TileCoord);
	
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
