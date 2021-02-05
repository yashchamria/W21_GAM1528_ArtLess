// Fill out your copyright notice in the Description page of Project Settings.


#include "AG_Tile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AAG_Tile::AAG_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bLockLocation = true;
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("AG Tile Mesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Assets/Mesh/TileMap/Tiles/AG_TestTile.AG_TestTile'"));
	if (Mesh.Succeeded()) { TileMesh->SetStaticMesh(Mesh.Object); }
	RootComponent = TileMesh;

	TileTriggerBox = CreateDefaultSubobject<UBoxComponent>("AG Tile Trigger Box");
		
	Tags.Add("AG_Tile");
}

void AAG_Tile::AutoConfigurePropertyToggle()
{	
	if(NullTile == true)
	{
		IsStartTile 	   = false;
		IsWalkable		   = false;
		IsTransportable	   = false;
		CanKill			   = false;
		HasPickup		   = false;
		HasTriggerEvent	   = false;
		IsCrackable		   = false;
		IsCracked		   = false;
		CanSlide		   = false;
		IsWinTile		   = false;
	}

	if(IsStartTile == true)
	{
		NullTile = false;
		IsWalkable = true;
		CanKill = false;
		IsWinTile = false;
		IsCracked = false;
	}

	if(IsWalkable == true)
	{
		NullTile = false;
		IsCracked = false;
	}

	if(IsTransportable == true)
	{
		NullTile = false;
		IsWalkable = true;
		CanKill = false;
		IsCracked = false;
	}

	if(CanKill == true)
	{
		NullTile = false;
		IsStartTile = false;
		IsWalkable = true;
		IsWinTile = false;
	}
	if(HasPickup == true)
	{
		NullTile = false;
		IsWalkable = true;
		CanKill = false;
		IsCracked = false;
	}

	if(HasTriggerEvent == true)
	{
		NullTile = false;
		IsWalkable = true;
	}

	if(IsCrackable == true)
	{
		NullTile = false;
		IsWalkable = true;
		IsCracked = false;
	}

	if(IsCracked == true)
	{
		NullTile = false;
		IsWalkable = true;
		IsStartTile = false;
		IsWinTile = false;
	}

	if(CanSlide == true)
	{
		NullTile = false;
		IsWalkable = true;
		CanKill = false;
		IsCracked = false;
		IsWinTile = false;
	}

	if(IsWinTile == true)
	{
		NullTile = false;
		IsStartTile = false;
		IsWalkable = true;
		IsCracked = false;
		CanKill = false;
	}
}

void AAG_Tile::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

