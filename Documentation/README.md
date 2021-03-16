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

1. TileMap 	     | Yash
2. TurnBase System   | Jonathan
3. BaseGrid Classes  | Yash
4. PlayerCharacter   | Jonathan
5. Inventory System  | Xiyang
6. User Interface    | Vrund

**Other feature that might be present in submission but not ready for Alpha01 -> AI/Enemy, Camera Manager, Audio System, Pickup & BaseGrid Actor, Level Manager, Event System



Setup Instructions -->
The correct level should load itself. The game will start with 3D Main Menu. Leading to one Alpha01 gameplay prototype level.
In case, to manually load the levels, all the Alpha01 levels are located in Content/Maps/ALPHA01/...



Player Controls -->

Character Movements(Only Possible if the next tile is valid to walk on) -->
Forward  -> W,  Up-Arrow,     Mouse-Clicking on Forward Tile
Left     -> A,  Left-Arrow,   Mouse-Clicking on Left Tile
Backward -> S,  Down-Arrow,   Mouse-Clicking on Backward Tile
Right    -> D,  Right-Arrow,  Mouse-Clicking on Right Tile

Character Inventory(Only if you have collected pickups) -->
Scroll Up Throw the Inventory(collected pickups) -> PageUp
Scroll Down Throw the Inventory(collected pickups) -> PageDown

User Interface -->
Pause(Menu Screen) -> Q
Resume -> Q



Known Bugs for Alpha01 -->

Individual Tile is not aware of its TileType(i.e. Fourway, Threeway, corner or straight), it just checks if the next tile is walkable or not. 
Results in walking over a visual gap between two walkable tiles even in the cases it should not possible.

Multiple consequence presses in the beginning 3D main menu screen might result in 3D Props losing their desired position.



Current(Alpha01) Limitations -->

No Animation is available for any characters.
Player cannot knock out AI just yet.
No indication for win(win system is not in place yet).
No indication for losing but player indeed gets knocked out and cannot move anymore.
AI is still work in progress.
Pickup is currently proof of working, more game specific features will be added later on.

