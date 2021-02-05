// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
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
		FVector2D TileSize = FVector2D(250.0f, 250.0f);

	FIntPoint GetTileCoord(FVector WorldPosition);
	
	FIntPoint GetNextTileCoord(FVector CharacterLocation, FVector DirectionVector, uint32 TileLeap = 1);

	FVector GetTilePosition(FIntPoint TileCoord);

	bool IsTileCoordVaild(FIntPoint TileCoord);

	bool GetTileProperty(FIntPoint TileCoord, AG_TileProperty TileProperty);

	uint32 GetArrayIndexFromCoord(FIntPoint TileCoord);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
