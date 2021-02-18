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
		FVector2D TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_TileInfo")
		TArray<class AActor*> RegisteredActors;

	//Tile Properties
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "AG_TileProperty")
		void AutoConfigurePropertyToggle();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty")
		bool NullTile = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsStartTile = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsWalkable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsTransportable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool CanKill = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool HasPickup = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool HasTriggerEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsCrackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsCracked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool CanSlide = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileProperty", meta = (EditCondition = "!NullTile"))
		bool IsWinTile = false;
	
	//Tile Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_TileComponents")
		class UStaticMeshComponent* TileMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_TileComponents")
		class UBoxComponent* TileTriggerBox;

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
