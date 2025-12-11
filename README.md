# Go With The Flow
This is a videogame made as the final project for Advanced Programming. It is an ocean-themed endless runner game where you try to avoid the obstacles and pick up the right collectibles to reach your highest score while the game gets progressively faster.

You can see a more in-depth explanation of how to play here https://drive.google.com/file/d/1IR714lVISHfurcod3_ptlw_ofTAogHTf/view?usp=sharing .

---
## Game Features
The general game mecanics include randomly generated items in three horizontal lanes in the user's screen. The player can control the character (a stingray), by clicking the keyboard's up and down arrows to switch to an adjacent lane. The character´s horizontal position is static, while the random items advance towards it horizontally. If the character touches an item, depending on its type, different events will happen. More specifically, the game includes the following features...
- **Scoring System:** The player can pickup seastars and earn a point for each of them. As the score increases, the game speed will increase as well. increasing the difficulty. If the score goes below zero (which could happen with anti-powerup's), the game is over. 
- **Power-up:** The player can pickup a seashell which will double the amount of points earned during 10 seconds.
- **Anti-power-up:** If the player crashes against a sea urchin, it will lose 3 points from its score. If the player has an active powerup and hits an anti-power-up, it will also lose the double points effect. 
- **Obstacles:** The most common item. If a player crashes against an obstacle, they will lose the game.
- **Sound effects:** When the player touches an item, a different sound effect will be played for each of the four mentioned items.
Every time a game is over, the Game Over Screen will be displayed with the game's final score and the highest registered score.

---
## How to use
This game is made in c++ with cocos2dx. To use the code in this repository, you will need to install Cocos, create a project, and import the two folders in the repository to replace the default homonymous folders. You can then run the code and the game screen will pop-up.
