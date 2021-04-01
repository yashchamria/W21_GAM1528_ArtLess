// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_StreetLightObstacle.h"
#include "../TileMap/AG_TileMap.h"
#include "../TileMap/AG_Tile.h"
#include "../Player/AG_PlayerController.h"

void AAG_StreetLightObstacle::SetWalkable()
{
	TileMap->Tiles[Coord]->IsWalkable = true;
}

void AAG_StreetLightObstacle::DisableWalable()
{
	TileMap->Tiles[Coord]->IsWalkable = false;
}

void AAG_StreetLightObstacle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_StreetLightObstacle::CheckTurnCounter()
{
	uint32 turn = PlayerController->GetPlayerTurnCount();
	if (turn % 2 == 0)
	{
		DisableWalable();
	}
	else
	{
		SetWalkable();
	}
}

void AAG_StreetLightObstacle::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(GetActorLocation() + 10.0f);

	Coord = TileMap->GetArrayIndexFromCoord(this->CurrentTileCoord);
	//TileMap->Tiles[Coord]->Register(this);
	CheckTurnCounter();
}

void AAG_StreetLightObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckTurnCounter();
}