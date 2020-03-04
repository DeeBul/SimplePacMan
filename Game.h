#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "pacChar.h"
#include "ghostChar.h"
#include "Timer.h"
#include "TextBox.h"
#include <vector>
#include <sstream>

class Game: public AppComponent, public Timer{
	//**************************************VARIABLE DECLARATIONS*********************************************************
	// MAIN GAME STUFF
	float size = 0.1;																		// Size of pacman and ghosts
	float speed = 0.0005;																	// How fast pacman moves
	float ghostSpeed = speed * 1.15;														// How fast ghosts move (always slightly faster)
	bool ghostMove = true;
	int lives = 3;
	float buffer = 0.01;																	// How much distance is checked for when ghosts hit their positions
	float pathBuff = 6 * buffer;															// Proximity for Pacman within paths to be centered

	// PACMAN POSITIONS
	float spawnX = 0.0;																		// Where Pacman spawns x-coordinate
	float spawnY = -0.38;																	// Where Pacman spawns y-coordinate	

	// GHOST POSITIONS
	float bX = 0.88;																		// Blinky's X-coordinate spawnpoint
	float bY = -0.38;																		// Blinky's Y-coordinate spawnpoint
	float pX = -0.98;																		// Pinky's X-coordinate spawnpoint
	float pY = 0.68;																		// Pinky's Y-coordinate spawnpoint
	float iX = -0.38;																		// Inky's Y-coordinate spawnpoint
	float iY = 0.68;																		// Inky's's Y-coordinate spawnpoint
	float cX = 0.37;																		// Clyde's Y-coordinate spawnpoint
	float cY = 0.33;																		// Clyde's Y-coordinate spawnpoint
	float cY2 = 0.13;																		// Clyde's 2nd Y-coordinate for movement	

	float distance = 0.1;																	// Border thickness
	bool gameOver = false;
	bool gameRunning = true;

	// MOVEMENT BOOLEANS
	bool moving = false;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	//****************//
	bool upCmd = true;
	bool downCmd = true;
	bool leftCmd = true;
	bool rightCmd = true;

	//bool soundPlaying = false;
	bool hit = false;	
	float sB1x = -1.3;
	float sB2x = -1.32;
	float sB1y = 1.0;
	float sB2y = 1.02;
	float bgSpeed = speed / 15;
	//********************************************************************************************************************
	
	//**********************************************DRAWING SECTION*******************************************************
	std::vector<AppComponent*> components;
	void addComponent(AppComponent* component) {
		components.push_back(component);
	}

	// PACMAN
	pacChar* pacman;
	pacChar* pacHit;
//    sound* waka;
//    sound* dead;

	// GHOSTS
	bool ghostsMoving = true;
	bool pinkyL, pinkyR, pinkyU, pinkyD = (false, false, false, false);
	int blinkyPos = 4;
	int pinkyPos = 4;
	int inkyPos = 4;
	int clydePos = 6;
	ghostChar* blinky;																	// Blinky = Red Ghost
	ghostChar* pinky;																	// Pinky = Pink Ghost (Duh)
	ghostChar* inky;																	// Inky = Cyan Ghost
	ghostChar* clyde;																	// He's the orange one
	
	// PACMAN'S LIVES
	TexRect* life1;
	TexRect* life2;
	TexRect* life3;
	
	// UI SCREENS
	TexRect* lost;
	TexRect* respawn;
	TexRect* spacebar;
	bool spawn = true;

	// STAGE BUILDING
	Rect* stageBorder1;
	Rect* stageBorder2;
	Rect* sB1;
	Rect* sB2;
	Rect* yellowColumn;
	Rect* pinkColumn;
	Rect* redColumn;
	Rect* blueColumn;
	Rect* orangeColumn;
	//********************************************************************************************************************
public:
    Game();	
    void draw() const;
    void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
    void action();

    ~Game();
};

#endif 
