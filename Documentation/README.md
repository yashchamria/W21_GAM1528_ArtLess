# W21_GAM1528_ArtLess

**Review in Notepad for better formatting

Team --> ArtLess Games

Game --> Cold Nites

Description --> Cold Nites is a Grid-style turn-based game. The player must strategically navigate through the level to survive the cold night, protecting the boy from all the mischievous elements of the city. 
	        And, there are always multiple ways to solve the puzzles along the way.

Team Members --> Xiyang Chen   | Project Manager/Programmer
	     --> Jonathan Sime | Programmer
	     --> Vrund Soni    | Programmer
	     --> Yash Chamria  | Programmer

Alpha 01 Modules --> 

01. TileMap 	      | Yash
02. TurnBase System   | Jonathan
03. BaseGrid Classes  | Yash
04. PlayerCharacter   | Jonathan
05. Inventory System  | Xiyang
06. Menu System       | Vrund

Alpha 02 Modules --> 

07. AI System	      | Yash
08. Event Manager     | Yash
09. Camera Manager    | Yash
10. Level Management  | Vrund
11. Scoring System    | Vrund


Setup Instructions -->
The correct level should load itself. The game will start with 3D Main Menu. Leading to Level Selection Screen.
In case, to manually load the levels, all the levels are located in Content/Maps/GameLevels/...


Player Controls -->

Movements(Only Possible if the next tile is valid to walk on) -->
Forward  -> W,  Up-Arrow,     Mouse-Clicking on Forward Tile
Left     -> A,  Left-Arrow,   Mouse-Clicking on Left Tile
Backward -> S,  Down-Arrow,   Mouse-Clicking on Backward Tile
Right    -> D,  Right-Arrow,  Mouse-Clicking on Right Tile

Transport(Only Possible if the player is on sewers) -->
Transport -> E

Inventory(Only if you have collected pickups) -->
Scroll Up Throw the Inventory(collected pickups)   -> PageUp
Scroll Down Throw the Inventory(collected pickups) -> PageDown

Pause(Menu Screen) -> Esc/Q
Resume -> Esc/Q
NOTE: The Esc key is disabled to stop PlayInEditor. To Exit the game use the 3D Exit Button in the 3D MainMenu.

Scoring System | Star Types

There are three possible StarType for a level in the game.

Level Completion Star --> Get it by completing the level.
Collectible Star      --> Get it by collecting in-level Star prop.
Turn Star 	      --> Get it by completing the level in the minimum number of Turns.

Note - Not every level has 3 stars.

AI System | AI Types

There are three types of AI in the game.

Still AI - Still AI only stays in one place and will only react if the player is right in the front tile.
Rotating AI - Rotating AI rotates 180 degree after every player turn, it will also attack if the player is right in front of it.
Patrolling AI - Patrolling AI will patrol on set Tile Coordinates, it will also only attack if the player comes to the forward tile.

Note - All the AI can be knocked out if the player approaches the AI from the blind spot(any direction but not the front).

Known Bugs for Alpha02 -->

Individual Tile is not aware of its TileType(i.e. Fourway, Threeway, corner or straight), it just checks if the next tile is walkable or not. 
Results in walking over a visual gap between two walkable tiles even in the cases it should not possible.

Multiple consequence presses in the beginning 3D main menu screen might result in 3D Props losing their desired position.

Current Limitations -->

No Animation is available for any characters.

The Current Unreal Engine 4.26 does not support UPROPERTY Macro for TMultiMap Yet -
https://answers.unrealengine.com/questions/588193/tmultimap-not-allowed-as-a-uproperty.html
As a result, CollectedTotalStars will not work for the new Instance of the Game and will be reset on every new launch.
Though CollectedTotalStars will work fine with the same running Instance of the Game.

