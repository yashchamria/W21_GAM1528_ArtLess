W21_GAM1528_ArtLess

/---------------------------------------------------------------Yash(5th Feb 2021)----------------------------------------------------------/

TileMap -> It is responsible for spawning tile actors in grid base fashion. Grid size can be changed on the fly. For Example, the 10x10 grid can be changed to 20x20 in the Editor detail panel itself. Note - TileMap is supposed to placed at origin. All other tranforms are locked.

Helper Functions in TileMap -> TileMap class is storing all the spawned tile pointer in a array. As a result, the player or other actors can ask the tilemap for their current tile position, tile coord, neighbouring tile info, tile types, etc. For example, the player can call a function such as GetNextTiles or GetTileType.

Tile -> Tile class is a actor, on which the level is build on. One can change the tile properties and apperance for any tile in the editor itself. TileMap will be responsible for spawning the tile. Note - Don't put tiles directly in levels. Note - Don't delete Tiles directly from Outliner. It will cause memory leaks since TileMap is holding the reference for all the tiles.

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


/----------------------------------------------------------------Vrund(5th Feb 2021)---------------------------------------------------------/

Main Menu -> Added a working Main menu and pause menu.
	     The pause menu makes use of character class the player controller class. 
    	     Key binding for the pause menu is 'Q' key for now.

/--------------------------------------------------------------- Yash(16th Feb 2021)----------------------------------------------------------/

BaseGridCharacter -> Added a BaseGridCharacter inheriting from ACharacter. This character will be now responsible for movement on grid base tilemap. As well as the actor will take care of resgistering itself or any inheriting actor to the tilemap.

Now all the moving characters should inherit from BaseGridCharacter.

PlayableCharacter -> Now the playable character inherits from ABaseGridCharacter. PlayerController -> Also, playercontroller works with WASD, Mouse clicking and Arrow keys.

/----------------------------------------------------------------Vrund(17th Feb 2021)---------------------------------------------------------/

BaseGridActor-> Use BaseGridActor to make any static objects (pickups, collectibles etc) that will go in the level. 
		To destory the actor do not call Destroy, instead call Delete function of BaseGridActor.


/--------------------------------------------------------------- Yash(22th Feb 2021)----------------------------------------------------------/

Tile -> Individual spawned tile now keeps track of all actors/characters standing on it. For this to work all the base class calls Register function on TileMap. And make sure to call unregister once you leave the tile.

Tile -> Now you can rotate the staticmesh or change tilemesh from TileAesthetic Category in the editor.


/--------------------------------------------------------------- Yash(6th March 2021)----------------------------------------------------------/

AIBaseGridCharacter -> Added a BaseAI class inheriting from BaseGridCharacter and will provide basic functionality such as detecting the player, Catching the player, manganing the AITurn(with AITurnManager)etc. All future AI class will inherits from this class.

*(Changed it entire in the future Iteration) AITurnManager -> Basically, this class calls FinishTurn() for all the AI using a Timer. Now we don't need to manually call FinishTurn() so that the player can move again. Also fixes the issue of Turn System not working when no AI is present in the game.

StillAI -> Inherits from AIBaseGridCharacter. Itis the most basic AI in the game. It only moves when the player is in front of him and knocks him over.


/--------------------------------------------------------------- Yash(11th March 2021)----------------------------------------------------------/

AITurnManager -> Rewrote the entire Manager System. Now, it inherits from a basic actor.
		 Now, the AITurn Manager is aware of all the present AI in the world.
		 It will call FinishTurn once all the AI are done with their turn.
		 Still need to deal with some bugs.

RotatingAI -> It rotates 180 in each turn. It only attacks when the player is right in front of the AI when it is looking at him.

PatrollingAI -> Very WIP
