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

Known Bugs for Alpha02 -->

Individual Tile is not aware of its TileType(i.e. Fourway, Threeway, corner or straight), it just checks if the next tile is walkable or not. 
Results in walking over a visual gap between two walkable tiles even in the cases it should not possible.

Multiple consequence presses in the beginning 3D main menu screen might result in 3D Props losing their desired position.

Current Limitations -->

No Animation is available for any characters.
Player cannot knock out AI yet.

