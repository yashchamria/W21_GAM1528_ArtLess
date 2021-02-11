#include "AG_TileMap.h"
#include "AG_Tile.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AAG_TileMap::AAG_TileMap()
{
	PrimaryActorTick.bCanEverTick = true;

	bLockLocation = true;
	
	Tags.Add("AG_TileMap");
}


void AAG_TileMap::BeginPlay()
{
	Super::BeginPlay();

}

void AAG_TileMap::ClearTiles()
{
	for (int i = 0; i < Tiles.Num(); i++)
	{
		if (Tiles.IsValidIndex(i))
		{
			Tiles[i]->WipeRegister();
			Tiles[i]->Destroy();
		}
	}

	Tiles.Empty();
}

void AAG_TileMap::GenerateTiles()
{
	ClearTiles();

	for (uint32 i = 0; i < Width; i++)
	{
		for (uint32 j = 0; j < Length; j++)
		{
			FVector Location = GetActorLocation() + FVector(i * TileSize.X, j * TileSize.Y, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters TileParams;
			AAG_Tile* SpawnedTile = GetWorld()->SpawnActor<AAG_Tile>(Location, Rotation, TileParams);

			FAttachmentTransformRules TileTransformRules(EAttachmentRule::KeepWorld, true);
			SpawnedTile->AttachToActor(this, TileTransformRules);

			SpawnedTile->SetTileCoordinates(FIntPoint(i, j));

			FString Name = *FString::Printf(TEXT("Tile(%i,%i)"), i, j);
			SpawnedTile->SetActorLabel(Name);
			SpawnedTile->Tags.Add(*Name);
			SpawnedTile->TileSize = TileSize;
			SpawnedTile->Position = GetTilePosition(FIntPoint(i, j));
			
			SpawnedTile->TileTriggerBox->SetRelativeLocation(SpawnedTile->Position + FVector(0.0f, 0.0f, 65.0f));
			SpawnedTile->TileTriggerBox->SetBoxExtent(FVector(TileSize.X/2, TileSize.Y/2, 65.0f));
			SpawnedTile->TileTriggerBox->ComponentTags.Add(*Name);
			
			Tiles.Add(SpawnedTile);
		}
	}
}
void AAG_TileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


FIntPoint AAG_TileMap::GetTileCoord(FVector WorldPosition)
{
	FIntPoint TileCoord;

	TileCoord.X = UE4::SSE4::FloorToFloat(WorldPosition.X / TileSize.X);
	TileCoord.Y = UE4::SSE4::FloorToFloat(WorldPosition.Y / TileSize.Y);

	return TileCoord;
}

FIntPoint AAG_TileMap::GetNextTileCoord(FVector CharacterLocation, FVector DirectionVector, uint32 TileLeap)
{
	FIntPoint TileCoord = GetTileCoord(CharacterLocation);

	FVector2D DirectionRounding = RoundToInt(FVector2D(DirectionVector.X, DirectionVector.Y));
	FIntPoint Direction = FIntPoint(DirectionRounding.X, DirectionRounding.Y);

	GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Orange, FString::Printf(TEXT("Forward Vector: %s"), *Direction.ToString()));

	if (Direction.X > 0) { TileCoord.X += TileLeap; }
	if (Direction.X < 0) { TileCoord.X -= TileLeap; }
	if (Direction.Y > 0) { TileCoord.Y += TileLeap; }
	if (Direction.Y < 0) { TileCoord.Y -= TileLeap; }

	return TileCoord;
}

FVector AAG_TileMap::GetTilePosition(FIntPoint TileCoord)
{
	return FVector((TileCoord.X * TileSize.X) + TileSize.X / 2, (TileCoord.Y * TileSize.Y) + TileSize.Y / 2, GetActorLocation().Z);
}

bool AAG_TileMap::IsTileCoordVaild(FIntPoint TileCoord)
{
	if(TileCoord.X >= 0 && (uint32)TileCoord.X < Width && TileCoord.Y >= 0 && (uint32)TileCoord.Y < Length)
	{
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("TileCoord:%s Is Not Valid"), *TileCoord.ToString()));
		return false;
	}
}

bool AAG_TileMap::GetTileProperty(FIntPoint TileCoord, AG_TileProperty TileProperty)
{
	if(IsTileCoordVaild(TileCoord))
	{
		uint32 index = GetArrayIndexFromCoord(TileCoord);

		if (TileProperty == AG_TileProperty::IsStartTile)			{ return Tiles[index]->IsStartTile; }
		else if (TileProperty == AG_TileProperty::IsWalkable)		{ return Tiles[index]->IsWalkable; }
		else if (TileProperty == AG_TileProperty::IsTransportable)	{ return Tiles[index]->IsTransportable; }
		else if (TileProperty == AG_TileProperty::CanKill)			{ return Tiles[index]->CanKill; }
		else if (TileProperty == AG_TileProperty::HasPickup)		{ return Tiles[index]->HasPickup; }
		else if (TileProperty == AG_TileProperty::HasTriggerEvent)	{ return Tiles[index]->HasTriggerEvent; }
		else if (TileProperty == AG_TileProperty::NullTile)			{ return Tiles[index]->NullTile; }
		else if (TileProperty == AG_TileProperty::IsCrackable)		{ return Tiles[index]->IsCrackable; }
		else if (TileProperty == AG_TileProperty::IsCracked)		{ return Tiles[index]->IsCracked; }
		else if (TileProperty == AG_TileProperty::CanSlide)			{ return Tiles[index]->CanSlide; }
		else if (TileProperty == AG_TileProperty::IsWinTile)		{ return Tiles[index]->IsWinTile; }
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("Property for TileCoord:%s Is Not Valid"), *TileCoord.ToString()));
	}
	return false;
}

uint32 AAG_TileMap::GetArrayIndexFromCoord(FIntPoint TileCoord)
{
	return TileCoord.X * Length + TileCoord.Y;
}

void AAG_TileMap::Register(AActor* Actor, FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if(Tiles.Num() > 0)
	{
		Tiles[TileIndex]->Register(Actor);
	}
}


///WIP CODE------>
void AAG_TileMap::UnRegister(AActor* Actor, FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.Num() > 0)
	{
		Tiles[TileIndex]->UnRegister(Actor);
	}
}

bool AAG_TileMap::IsRegistered(AActor* Actor, FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.Num() > 0)
	{
		//for(int i = 0 ; i < Tiles[TileIndex]->RegisteredActors.Num(); i++)
		if (Tiles[TileIndex]->RegisteredActors.Find(Actor))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return false;
}

AActor* AAG_TileMap::GetAllRegisteredActors(FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.Num() > 0)
	{
		return Tiles[TileIndex]->RegisteredActors[0];
	}

	return nullptr;
}

//void Restore // Restore previous tileMap
//void DestroySingleTile
// set the tile to null.