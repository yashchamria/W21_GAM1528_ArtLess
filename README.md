# W21_GAM1528_ArtLess

Dev Readme --->
/---------------------------------------------------------------Yash(5th Feb 2021)----------------------------------------------------------/ 

TileMap Class ->  It is responsible for spawning tile actors in grid base fashion. Grid size can be changed on the fly. 
		  For Example, the 10x10 grid can be changed to 20x20 in the Editor detail panel itself.
		  Note - TileMap is supposed to placed at origin. All other tranforms are locked.

Helper Functions in TileMap Class -> TileMap class is saving all the spawned tile pointer in a array.
				     As a result, the player or other actors can ask the tilemap for their current tile position, tile coord, neighbouring tile info, tile types, etc.
				     For example, the player can call a function such as GetNextTiles or GetTileType.

Tile Class -> Tile class is a actor, on which the level is build on. One can change the tile properties and apperance for any tile in the editor itself. 
	      TileMap will be responsible for spawning the tile. 
	      Note - Don't put tiles directly in levels.
		  Note - Don't delete Tiles directly from Outliner. It will cause memory leaks since TileMap is holding the reference for all the tiles.

Helper functions can be called as follow :
{
	TArray<AActor*> TileMapActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATileMap::StaticClass(), TileMapActor);
	
	if (TileMapActor.Num() > 0)
		TileMap = Cast<ATileMap>(TileMapActor[0]);

	FIntPoint Currentcoord = TileMap->GetTileCoord(GetActorLocation());
	FIntPoint Nextcoord = TileMap->GetNextTileCoord(GetActorLocation(), GetActorForwardVector());
	FVector TileWorldLocation = TileMap->GetTilePosition(Currentcoord);

	bool IsCurrentTileWalkable = TileMap->GetTileProperty(Currentcoord, AG_TileProperty::IsWalkable);
	bool IsNextTileWalkable = TileMap->GetTileProperty(Nextcoord, AG_TileProperty::IsWalkable);
	
	GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("IsNextTileWalkable: %d"), IsNextTileWalkable));
	GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("IsCurrentTileTileWalkable: %d"), IsCurrentTileWalkable));
	GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("Next Coord: %s"), *Nextcoord.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("Current Coord: %s"), *Currentcoord.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("Tile World Location: %s"), *TileWorldLocation.ToString()));
}

/--------------------------------------------------------------- Yash----------------------------------------------------------/

/******************************************************************************************************************************/

/----------------------------------------------------------------Vrund---------------------------------------------------------/



/----------------------------------------------------------------Vrund---------------------------------------------------------/