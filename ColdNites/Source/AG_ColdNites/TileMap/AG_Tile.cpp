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
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Art/TileMap/Tile/Mesh/TileMesh.TileMesh'"));
	if (MeshAsset.Succeeded()) { TileMesh->SetStaticMesh(MeshAsset.Object); }

	Tags.Add("AG_Tile");
}

void AAG_Tile::AutoConfigurePropertyToggle()
{
	if (NullTile == true)
	{
		IsStartTile = false;
		IsWalkable = false;
		IsTransportable = false;
		IsWinTile = false;
	}

	if (IsStartTile == true)
	{
		NullTile = false;
		IsWalkable = true;
		IsWinTile = false;
	}

	if (IsWalkable == true)
	{
		NullTile = false;
	}

	if (IsTransportable == true)
	{
		NullTile = false;
		IsWalkable = true;
	}

	if (IsWinTile == true)
	{
		NullTile = false;
		IsStartTile = false;
		IsWalkable = true;
	}
}

void AAG_Tile::RotateMesh()
{
	FRotator NewRotation = TileMesh->GetRelativeRotation() + FRotator(0.0f, 90.0f, 0.0f);
	TileMesh->SetRelativeRotation(NewRotation);
}

void AAG_Tile::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAG_Tile::Register(AActor* Actor)
{
	uint32 ActorIndex = RegisteredActors.Find(Actor);

	if (ActorIndex == INDEX_NONE)
	{
		RegisteredActors.Add(Actor);
	}
}

void AAG_Tile::UnRegister(AActor* Actor)
{
	uint32 ActorIndex = RegisteredActors.Find(Actor);

	if (RegisteredActors.IsValidIndex(ActorIndex))
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
	if (RegisteredActors.Num() > 0)
	{
		RegisteredActors.Empty();
	}
}