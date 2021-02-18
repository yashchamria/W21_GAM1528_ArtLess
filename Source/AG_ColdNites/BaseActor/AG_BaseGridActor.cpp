#include "AG_BaseGridActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "Kismet/GameplayStatics.h"

AAG_BaseGridActor::AAG_BaseGridActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(50, 50, 50));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAG_BaseGridActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Getting the Spawned TileMap Actor from the World
	TArray<AActor*> TileMapActor;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);
	
	if (TileMapActor.Num() > 0)
	{
		TileMap = Cast<AAG_TileMap>(TileMapActor[0]);
		TargetTileWorldLocation = TileMap->GetTileWorldPosition(TileMap->GetTileCoord(GetActorLocation()));

		CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
		TileMap->Register(this, CurrentTileCoord);
	}
	
	AutoRepositionToTileCenter();
}

void AAG_BaseGridActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_BaseGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAG_BaseGridActor::AutoRepositionToTileCenter()
{
	if (TileMap && TileMap->GetTileProperty(CurrentTileCoord, AG_TileProperty::IsWalkable))
	{
		FVector NewLocation = TileMap->GetTileWorldPosition(CurrentTileCoord);
		NewLocation.Z = 75.406784;
		SetActorLocation(NewLocation);

		TileMap->Register(this, CurrentTileCoord);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 200.0f, FColor::Red, FString::Printf(TEXT("--> Actor placed on Unwalkable tile <--")));
	}
}

void AAG_BaseGridActor::Delete()
{
	TileMap->UnRegister(this, CurrentTileCoord);
	Destroy();
}
