#include "AG_BaseGridActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

AAG_BaseGridActor::AAG_BaseGridActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseRootTransformation = CreateDefaultSubobject<USceneComponent>("Scene Component");
	RootComponent = BaseRootTransformation;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	
	if (bAutoRepositionToTileCenter) { AutoRepositionToTileCenter(); }
}

void AAG_BaseGridActor::BeginPlay()
{
	Super::BeginPlay();

	//Getting the Spawned TileMap Actor from the World
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player) { PlayerCharacter = Cast<AAG_PlayableCharacter>(Player); }
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
		NewLocation.Z = 0.0f;
		SetActorLocation(NewLocation);

		TileMap->Register(this, CurrentTileCoord);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 200.0f, FColor::Red, FString::Printf(TEXT("--> Actor placed on Unwalkable tile <--")));
	}
}

bool AAG_BaseGridActor::CheckActorOnTheTile(FName ActorTag)
{
	if (TileMap->IsRegistered(ActorTag, CurrentTileCoord))
	{
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "Actor On Pickup Tile !!!");
		return true;
	}
	return false;
}

bool AAG_BaseGridActor::CheckPlayerOnTheTile()
{
	if(CheckActorOnTheTile("AG_PlayableCharacter"))
	{
		return true;
	}
	return false;
}

void AAG_BaseGridActor::UnRegisterToTileMap()
{
	TileMap->UnRegister(this, CurrentTileCoord);
}

void AAG_BaseGridActor::Delete()
{
	TileMap->UnRegister(this, CurrentTileCoord);
	Destroy();
}
