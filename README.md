# Space Race
Do you love arcade games? Or are you old enough to see such games?

You may have heard of [Atari's Space Race game](https://en.wikipedia.org/wiki/Space_Race_(video_game)) or played similar games involving asteroids or enemies. In those games, you aim to reach the top of the screen - if asteroids hit you, you must start from the beginning. In other variations, you can earn scores by shooting the asteroids or enemies, and you lose your life or health if they hit you.

My first game project is a variation of Space Race, where you shoot the enemies to gain points. If you let the enemy go past you, you lose your points. If an enemy hits you, you lose health - and the game is over once your health becomes zero. Simple, right?

You can also play with your friends, as this game supports up to 4 players (1-4)!

# Version
- Alpha version, yet to be compiled as a standalone program.
- Based on Qt6 and C++

# Updates
### 230918
```
<Updates>
- Added state machines to the game logic
- Now accepting multiple keys - smoother multiplayer support
<Bugs>
- The program may crash if the number of players is being set more than once after playing one or more games
- The game needs to be more presentable 
```
# Potential Improvements
1) Return to the starting screen once all the players are killed **[WIP]**
2) Announce the winner if only one player survives (when there are 2+ players)
3) Accept multiple keys at the instant so that the multiplayer mode can be smoother **[Done - 230918]**
4) Add variations to enemies (more/less damage, shoot bullets back, etc)
5) Add other items - health refuel, x2 points, etc
6) Add difficulty
7) Give options to users about resolution
