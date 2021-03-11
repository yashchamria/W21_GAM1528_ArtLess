#include "AG_Tile.h"
#include "Components/StaticMeshComponent.h"

AAG_Tile::AAG_Tile()
{
	PrimaryActorTick.bCanEverTick = true;

	bLockLocation = true;

	TileRootTransformation = CreateDefaultSubobject<USceneComponent>("AG Scene Component");
	RootComponent = TileRootTransformation;
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("AG Tile Mesh");
	TileMesh->SetRelativeLocation(GetActorLocation() + FVector(TileSize.X / 2, TileSize.Y / 2, 0.0f));
	TileMesh->SetupAttachment(TileRootTransformation);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Art/TileMap/Tiles/AG_TileFourway.AG_TileFourway'"));
	if (MeshAsset.Succeeded()) { NewTileMesh = MeshAsset.Object; }
	RegenerateMesh();
	
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

void AAG_Tile::RotateMesh()
{
	FRotator NewRotation = TileMesh->GetRelativeRotation() + FRotator(0.0f, 90.0f, 0.0f);
	TileMesh->SetRelativeRotation(NewRotation);
}

void AAG_Tile::RegenerateMesh()
{
	if (NewTileMesh) { TileMesh->SetStaticMesh(NewTileMesh); }
	else { TileMesh->SetStaticMesh(nullptr); }
}

void AAG_Tile::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


///WIP CODE------>
void AAG_Tile::Register(AActor* Actor)
{
	uint32 ActorIndex = RegisteredActors.Find(Actor);

	if(ActorIndex == INDEX_NONE)
	{
		RegisteredActors.Add(Actor);
	}
}

void AAG_Tile::UnRegister(AActor* Actor)
{
	uint32 ActorIndex = RegisteredActors.Find(Actor);

	if(RegisteredActors.IsValidIndex(ActorIndex))
	{
		RegisteredActors.RemoveAt(ActorIndex);
	}
}

bool AAG_Tile::IsRegistered(AActor* Actor)
{
	uint32 ActorIndex = RegisteredActors.Find(Actor);

	if (RegisteredActors.IsValidIndex(ActorIndex))
	{
		return true;
	}
	return false;
}

void AAG_Tile::WipeRegister()
{
	if(RegisteredActors.Num() > 0)
	{
		RegisteredActors.Empty();
	}
}

