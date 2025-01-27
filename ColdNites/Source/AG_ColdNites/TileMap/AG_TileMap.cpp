#include "AG_TileMap.h"
#include "AG_Tile.h"
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
			SpawnedTile->Position = GetTileWorldPosition(FIntPoint(i, j));

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

	if (IsTileCoordVaild(TileCoord)) { return TileCoord; }
	else { return FIntPoint(-1, -1); } // Returns (-1,-1) if the coord are not valid.
}

FIntPoint AAG_TileMap::GetNextTileCoord(FVector CharacterLocation, FVector DirectionVector, uint32 TileLeap)
{
	FIntPoint TileCoord = GetTileCoord(CharacterLocation);

	FVector2D DirectionRounding = RoundToInt(FVector2D(DirectionVector.X, DirectionVector.Y));
	FIntPoint Direction = FIntPoint(DirectionRounding.X, DirectionRounding.Y);

	//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Orange, FString::Printf(TEXT("Forward Vector: %s"), *Direction.ToString()));

	if (Direction.X > 0) { TileCoord.X += TileLeap; }
	if (Direction.X < 0) { TileCoord.X -= TileLeap; }
	if (Direction.Y > 0) { TileCoord.Y += TileLeap; }
	if (Direction.Y < 0) { TileCoord.Y -= TileLeap; }

	if (IsTileCoordVaild(TileCoord)) { return TileCoord; }
	else { return FIntPoint(-1, -1); } // Returns (-1,-1) if the coord are not valid.
}

FVector AAG_TileMap::GetTileWorldPosition(FIntPoint TileCoord)
{
	return FVector((TileCoord.X * TileSize.X) + TileSize.X / 2, (TileCoord.Y * TileSize.Y) + TileSize.Y / 2, GetActorLocation().Z);
}

bool AAG_TileMap::IsTileCoordVaild(FIntPoint TileCoord)
{
	if (TileCoord.X >= 0 && (uint32)TileCoord.X < Width && TileCoord.Y >= 0 && (uint32)TileCoord.Y < Length)
	{
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("TileCoord:%s Is Not Valid"), *TileCoord.ToString()));
		return false;
	}
}

bool AAG_TileMap::IsTileNeighbouring(FIntPoint CheckCoord, FVector WorldPosition, FVector ForwardDirection, FVector RightDirection, uint32 TileLeap)
{
	FIntPoint CurrentTileCoord = GetTileCoord(WorldPosition);

	FIntPoint ForwardTileCoord = GetNextTileCoord(WorldPosition, ForwardDirection, TileLeap);
	FIntPoint BackwardTileCoord = GetNextTileCoord(WorldPosition, -ForwardDirection, TileLeap);
	FIntPoint RightTileCoord = GetNextTileCoord(WorldPosition, RightDirection, TileLeap);
	FIntPoint LeftTileCoord = GetNextTileCoord(WorldPosition, -RightDirection, TileLeap);

	if (CheckCoord == ForwardTileCoord || CheckCoord == BackwardTileCoord || CheckCoord == RightTileCoord || CheckCoord == LeftTileCoord)
	{
		return true;
	}
	return false;
}

bool AAG_TileMap::GetTileProperty(FIntPoint TileCoord, AG_TileProperty TileProperty)
{
	if (IsTileCoordVaild(TileCoord))
	{
		uint32 index = GetArrayIndexFromCoord(TileCoord);

		if (TileProperty == AG_TileProperty::IsStartTile) { return Tiles[index]->IsStartTile; }
		else if (TileProperty == AG_TileProperty::IsWalkable) { return Tiles[index]->IsWalkable; }
		else if (TileProperty == AG_TileProperty::IsTransportable) { return Tiles[index]->IsTransportable; }
		else if (TileProperty == AG_TileProperty::NullTile) { return Tiles[index]->NullTile; }
		else if (TileProperty == AG_TileProperty::IsWinTile) { return Tiles[index]->IsWinTile; }
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
	if (IsTileCoordVaild(TileCoord))
	{
		const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

		if (Tiles.Num() > 0)
		{
			Tiles[TileIndex]->Register(Actor);
		}
	}
}


void AAG_TileMap::UnRegister(AActor* Actor, FIntPoint TileCoord)
{
	if (IsTileCoordVaild(TileCoord))
	{
		const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

		if (Tiles.IsValidIndex(TileIndex))
		{
			Tiles[TileIndex]->UnRegister(Actor);
		}
	}
}

bool AAG_TileMap::IsRegistered(AActor* Actor, FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		if (Tiles[TileIndex]->RegisteredActors.Find(Actor))
		{
			return true;
		}
	}

	return false;
}

bool AAG_TileMap::IsRegistered(FName ActorTag, FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		for (AActor* RegisteredActor : Tiles[TileIndex]->RegisteredActors)
		{
			if (RegisteredActor)
			{
				if (RegisteredActor->ActorHasTag(ActorTag))
				{
					return true;
				}
			}
		}
	}
	return false;
}

AActor* AAG_TileMap::GetAllRegisteredActors(FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		return Tiles[TileIndex]->RegisteredActors[0];
	}
	return nullptr;
}

void AAG_TileMap::GetAllRegisteredActorArray(FIntPoint TileCoord, TArray<AActor*>& RegisteredActors)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		uint8 RegisterActorNum = GetNumberOfRegisteredActors(TileCoord);

		RegisteredActors.Reserve(RegisterActorNum);
		
		for(int i = 0; i < RegisterActorNum; i++)
		{
			RegisteredActors.Insert(Tiles[TileIndex]->RegisteredActors[i], i);
		}
	}	
}

void AAG_TileMap::GetAllRegisteredActorArrayOfTag(FIntPoint TileCoord, FName ActorTag, TArray<AActor*>& RegisteredActors)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		uint8 RegisterActorNum = GetNumberOfRegisteredActors(TileCoord);

		for(AActor* RegisteredAI : Tiles[TileIndex]->RegisteredActors)
		{
			if(RegisteredAI->ActorHasTag(ActorTag))
			{
				RegisteredActors.Add(RegisteredAI);
			}
		}
	}
}

uint8 AAG_TileMap::GetNumberOfRegisteredActors(FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		return Tiles[TileIndex]->RegisteredActors.Num();
	}

	return 0;
}

AG_TileInDirection AAG_TileMap::GetTileInDirection(FIntPoint NextTileCoord, AActor* Actor, uint32 TileLeap)
{
	if (GetNextTileCoord(Actor->GetActorLocation(), Actor->GetActorForwardVector(), TileLeap) == NextTileCoord)
	{
		return AG_TileInDirection::TileAtForward;
	}

	if (GetNextTileCoord(Actor->GetActorLocation(), -Actor->GetActorForwardVector(), TileLeap) == NextTileCoord)
	{
		return AG_TileInDirection::TileAtBackward;
	}

	if (GetNextTileCoord(Actor->GetActorLocation(), Actor->GetActorRightVector(), TileLeap) == NextTileCoord)
	{
		return AG_TileInDirection::TileAtRight;
	}

	if (GetNextTileCoord(Actor->GetActorLocation(), -Actor->GetActorRightVector(), TileLeap) == NextTileCoord)
	{
		return AG_TileInDirection::TileAtLeft;
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Invalid Tile Direction");
	return AG_TileInDirection::TileAtInvalidDirection;
}

FName AAG_TileMap::GetTileCameraTag(FIntPoint TileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(TileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		return Tiles[TileIndex]->CameraActorTag;
	}
	return "None";
}

FIntPoint AAG_TileMap::GetStartTileCoord()
{
	for(AAG_Tile* Tile : Tiles)
	{
		if(Tile->IsStartTile)
		{
			return Tile->TileCoordinate;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "No StartTile Found!");
	return (-1, -1);
}

FIntPoint AAG_TileMap::GetSewerPairCoord(FIntPoint CurrentTileCoord)
{
	const uint32 TileIndex = GetArrayIndexFromCoord(CurrentTileCoord);

	if (Tiles.IsValidIndex(TileIndex))
	{
		FName CurrentSewerID = Tiles[TileIndex]->SewerID;

		for (AAG_Tile* Tile : Tiles)
		{
			if(Tile->SewerID == CurrentSewerID)
			{
				if(!(Tile->TileCoordinate == CurrentTileCoord))
				{
					return Tile->TileCoordinate;
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Sewer Pair Missing");
	return (-1, -1);
}

//Future Possibility

//void Restore // Restore previous tileMap

//void DestroySingleTile // set the tile to null.

//Adding/removing more row or column without reseting the tiles

//Saving or loading tiles or edited tiles array