/*
	Code for Pacman game done by Mark McCullough, Darshan Bulsara, and Baudelio Perez
	With assistance from code distributed by Angelo Kyrilov
	All sprites made by Baudelio Perez
	Sounds downloaded from https://www.classicgaming.cc/classics/pac-man/sounds
	Spring 2019, UC Merced
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
//#include <Windows.h>
//#include <MMSystem.h>
#include "Game.h"
#include <vectors>

Game::Game(){
	// PACMAN STUFF																						(@MM)
	pacman = new pacChar("Pac-Man.png", 4, 5, 20, true, true, spawnX, spawnY, size, size);
	pacHit = new pacChar("pacmanDeath.png", 4, 5, 80, false, false, 0.0, 0.0, size, size);
//    waka = new sound("pacman_chomp.wav");
//    dead = new sound("pacman_death.wav");

	// GHOST STUFF																						(@MM & BP)
	blinky = new ghostChar("Sprites/Blinky/Blinky-Down.png", 1, 2, 100, true, true, bX, bY, size, size);
	pinky = new ghostChar("Sprites/Pinky/Pinky-Down.png", 1, 2, 100, true, true, pX, pY, size, size);
	inky = new ghostChar("Sprites/Inky/Inky-Down.png", 1, 2, 100, true, true, iX, iY, size, size);
	clyde = new ghostChar("Sprites/Clyde/Clyde-Down.png", 1, 2, 100, true, true, cX, cY, size, size);

	// UI STUFF																							(@MM)
    life1 = new TexRect("Sprites/pacmanLife.png", 0.9, 0.9, 0.1, 0.1);
	life2 = new TexRect("Sprites/pacmanLife.png", 1.05, 0.9, 0.1, 0.1);
	life3 = new TexRect("Sprites/pacmanLife.png", 1.2, 0.9, 0.1, 0.1);
	lost = new TexRect("Sprites/Text/GameOver.png", -0.25, 0.05, 0.5, 0.1);					// Gameover Screen
	respawn = new TexRect("Sprites/Text/Respawn.png", -0.21, 0.05, 0.5, 0.1);
	spacebar = new TexRect("Sprites/Text/Press_Space.png", -0.26, -0.1, 0.6, 0.1);
	// STAGE STUFF (x, y, w, h)																			(@DB & MM) 
	sB1 = new Rect(sB1x, sB1y, 2.6, 1.8, 0.0, 0.0, 0.0);
	sB2 = new Rect(sB2x, sB2y, 2.64, 1.84, 1.0, 1.0, 1.0);
	stageBorder1 = new Rect(-1.0, 0.7, 2.0, 1.2, 0.0, 0.0, 0.0);							// Black background
	stageBorder2 = new Rect(-1.02, 0.72, 2.04, 1.24, 1.0, 1.0, 1.0);						// White border
	yellowColumn = new Rect(-0.85, -0.01, 0.45, 0.35, 0.8, 1.0, 0.0);						// Bottom left (yellow)
	orangeColumn = new Rect(-0.85, 0.56, 0.45, 0.40, 1.0, 0.5, 0.0);						// Top left (orange)
	blueColumn = new Rect(0.5, 0.56, 0.35, 0.91, 0.0, 0.0, 1.0);							// Right (blue)	
	pinkColumn = new Rect(-0.25, 0.56, 0.58, 0.20, 1.0, 0.7, 0.7);							// Top middle (pink)
	redColumn = new Rect(-0.25, 0.19, 0.58, 0.55, 1.0, 0.0, 0.0);							// Bottom middle (red)

    setRate(1);
    start();
}

void Game::action() {
	float mx = pacman->getX();
	float my = pacman->getY();

	//**************************************PLAYER MOVEMENT*************************************		(@MM)
	if (moving) {
		if (moveUp && upCmd) {
			if (pacman->getX() >= bX - pathBuff && pacman->getX() <= bX + pathBuff) {
				pacman->setX(bX);
			}
			else if (pacman->getX() >= iX - pathBuff && pacman->getX() <= iX + pathBuff) {
				pacman->setX(iX);
			}
			else if (pacman->getX() >= pX - pathBuff && pacman->getX() <= pX + pathBuff) {
				pacman->setX(pX);
			}
			else if (pacman->getX() >= cX - pathBuff && pacman->getX() <= cX + pathBuff) {
				pacman->setX(cX);
			}
			pacman->setY(my + speed);
			sB1->setY(sB1->getY() - bgSpeed);
			sB2->setY(sB2->getY() - bgSpeed);
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (moveDown && downCmd) {
			if (pacman->getX() >= bX - pathBuff && pacman->getX() <= bX + pathBuff) {
				pacman->setX(bX);
			}
			else if (pacman->getX() >= iX - pathBuff && pacman->getX() <= iX + pathBuff) {
				pacman->setX(iX);
			}
			else if (pacman->getX() >= pX - pathBuff && pacman->getX() <= pX + pathBuff) {
				pacman->setX(pX);
			}
			else if (pacman->getX() >= cX - pathBuff && pacman->getX() <= cX + pathBuff) {
				pacman->setX(cX);
			}
			pacman->setY(my - speed);
			sB1->setY(sB1->getY() + bgSpeed);
			sB2->setY(sB2->getY() + bgSpeed);
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (moveLeft && leftCmd) {
			if (pacman->getY() >= bY - pathBuff && pacman->getY() <= bY + pathBuff) {
				pacman->setY(bY);
			}
			else if (pacman->getY() >= pY - pathBuff && pacman->getY() <= pY + pathBuff) {
				pacman->setY(pY);
			}
			else if (pacman->getY() >= iY - pathBuff && pacman->getY() <= iY + pathBuff) {
				pacman->setY(iY);
			}
			else if (pacman->getY() >= cY - pathBuff && pacman->getY() <= cY + pathBuff) {
				pacman->setY(cY);
			}
			else if (pacman->getY() >= cY2 - pathBuff && pacman->getY() <= cY2 + pathBuff) {
				pacman->setY(cY2);
			}
			pacman->setX(mx - speed);
			sB1->setX(sB1->getX() + bgSpeed);
			sB2->setX(sB2->getX() + bgSpeed);
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (moveRight && rightCmd) {
			if (pacman->getY() >= bY - pathBuff && pacman->getY() <= bY + pathBuff) {
				pacman->setY(bY);
			}
			else if (pacman->getY() >= pY - pathBuff && pacman->getY() <= pY + pathBuff) {
				pacman->setY(pY);
			}
			else if (pacman->getY() >= iY - pathBuff && pacman->getY() <= iY + pathBuff) {
				pacman->setY(iY);
			}
			else if (pacman->getY() >= cY - pathBuff && pacman->getY() <= cY + pathBuff) {
				pacman->setY(cY);
			}
			else if (pacman->getY() >= cY2 - pathBuff && pacman->getY() <= cY2 + pathBuff) {
				pacman->setY(cY2);
			}
			pacman->setX(mx + speed);
			sB1->setX(sB1->getX() - (bgSpeed));
			sB2->setX(sB2->getX() - (bgSpeed));
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PLAYER COLLISION DETECTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// BLOCK DOWNWARD MOVEMENTS
		if (abs((pacman->getY() - pacman->getH()) - (stageBorder2->getY() - stageBorder2->getH())) <= 4 * buffer ||

			abs((pacman->getY() - pacman->getH()) - (pinkColumn->getY())) <= 4 * buffer &&
			pacman->getX() <= (pinkColumn->getX() + pinkColumn->getW()) &&
			pacman->getX() >= (pinkColumn->getX() - pacman->getW()) ||

			pacman->getX() <= (pinkColumn->getX() + pinkColumn->getW()) &&
			pacman->getX() + pacman->getW() >= pinkColumn->getX() &&
			pacman->getY() <= pinkColumn->getY() - pinkColumn->getH() &&
			pacman->getY() - pacman->getH() >= redColumn->getY() ||

			pacman->getX() <= (yellowColumn->getX() + yellowColumn->getW()) &&
			pacman->getX() >= (yellowColumn->getX() - pacman->getW()) ||

			pacman->getX() <= (blueColumn->getX() + blueColumn->getW()) &&
			pacman->getX() >= (blueColumn->getX() - pacman->getW())) 
		{
			downCmd = false;
			if (moveDown) {
				pacman->pause();
				moving = false;
			}
		}
		else {
			downCmd = true;
			pacman->resume();
		}
		// BLOCK UPWARD MOVEMENTS
		if (abs(pacman->getY() - stageBorder2->getY()) <= 5 * buffer ||

			abs(pacman->getY() - redColumn->getY() <= 4 * buffer) && 
			pacman->getX() <= (redColumn->getX() + redColumn->getW()) &&
			pacman->getX() >= (redColumn->getX() - pacman->getW()) ||

			pacman->getX() <= (pinkColumn->getX() + pinkColumn->getW()) &&
			pacman->getX() + pacman->getW() >= pinkColumn->getX() &&
			pacman->getY() <= pinkColumn->getY() - pinkColumn->getH() &&
			pacman->getY() - pacman->getH() >= redColumn->getY() ||

			pacman->getX() <= (yellowColumn->getX() + yellowColumn->getW()) &&
			pacman->getX() >= (yellowColumn->getX() - pacman->getW()) ||

			pacman->getX() <= (blueColumn->getX() + blueColumn->getW()) &&
			pacman->getX() >= (blueColumn->getX() - pacman->getW()))
		{
			upCmd = false;
			if (moveUp) {
				pacman->pause();
				moving = false;
			}
		}
		else {
			upCmd = true;
			pacman->resume();
		}
		// BLOCK LEFT MOVEMENTS
		if (abs(pacman->getX() - stageBorder2->getX()) <= 4 * buffer ||
			
			pacman->getY() >= (blueColumn->getY() - blueColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (blueColumn->getY()) &&
			pacman->getX() >= blueColumn->getX() + blueColumn->getW() ||

			pacman->getY() >= (pinkColumn->getY() - pinkColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (pinkColumn->getY()) &&
			pacman->getX() >= pinkColumn->getX() + pinkColumn->getW() &&
			pacman->getX() <= blueColumn->getX() ||

			pacman->getY() >= (redColumn->getY() - redColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (redColumn->getY()) &&
			pacman->getX() >= redColumn->getX() + redColumn->getW() &&
			pacman->getX() <= blueColumn->getX() ||

			pacman->getY() >= (yellowColumn->getY() - yellowColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (yellowColumn->getY()) &&
			pacman->getX() >= yellowColumn->getX() + yellowColumn->getW() &&
			pacman->getX() + pacman->getW() <= pinkColumn->getX() ||

			pacman->getY() >= (orangeColumn->getY() - orangeColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (orangeColumn->getY()) &&
			pacman->getX() >= orangeColumn->getX() + orangeColumn->getW() - 3 * buffer &&
			pacman->getX() + pacman->getW() <= pinkColumn->getX())
		{
			leftCmd = false;
			if (moveLeft) {
				pacman->pause();
				moving = false;
			}
		}
		else {
			leftCmd = true;
			pacman->resume();
		}
		// BLOCK RIGHT MOVEMENTS
		if (abs((pacman->getX() + pacman->getW()) - (stageBorder2->getX() + stageBorder2->getW())) <= 4 * buffer ||

			pacman->getY() >= (blueColumn->getY() - blueColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (blueColumn->getY()) &&
			pacman->getX() + pacman->getW() <= blueColumn->getX()  &&
			pacman->getX() >= pinkColumn->getX() + pinkColumn->getW() ||

			pacman->getY() >= (pinkColumn->getY() - pinkColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (pinkColumn->getY()) &&
			pacman->getX() + pacman->getW() <= pinkColumn->getX() &&
			pacman->getX() >= orangeColumn->getX() + orangeColumn->getW()||

			pacman->getY() >= (redColumn->getY() - redColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (redColumn->getY()) &&
			pacman->getX() + pacman->getW() <= redColumn->getX() &&
			pacman->getX() >= yellowColumn->getX() + yellowColumn->getW()||

			pacman->getY() >= (yellowColumn->getY() - yellowColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (yellowColumn->getY()) &&
			pacman->getX() + pacman->getW() <= yellowColumn->getX() ||

			pacman->getY() >= (orangeColumn->getY() - orangeColumn->getH()) &&
			(pacman->getY() - pacman->getH()) <= (orangeColumn->getY()) &&
			pacman->getX() + pacman->getW() <= orangeColumn->getX())
		{
			rightCmd = false;
			if (moveRight) {
				pacman->pause();
				moving = false;
			}
		}
		else {
			rightCmd = true;
			pacman->resume();
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}	
	//******************************************************************************************


	




	

	//***************************************GHOST MOVEMENT*************************************		(@BP & MM)
	if (ghostMove) {
		// PINKY
		if (gameRunning) {
			// Move pinky up
			if ((pinky->getX() >= pX - buffer && pinky->getX() <= pX + buffer) &&
				(pinky->getY() >= bY - buffer && pinky->getY() <= bY + buffer)) {
				pinky->up();
				if (pinkyPos == 2) {
					pinky->setY(bY);
				}
				pinkyPos = 1;
			}
			// Move pinky down
			if ((pinky->getX() >= pX - buffer && pinky->getX() <= pX + buffer) &&
				(pinky->getY() >= pY - buffer && pinky->getY() <= pY + buffer)) {
				pinky->down();
				if (pinkyPos == 1) {
					pinky->setY(pY);
				}
				pinkyPos = 2;
			}
			if (pinkyPos == 1) {
				pinky->setY(pinky->getY() + (ghostSpeed));
			}
			if (pinkyPos == 2) {
				pinky->setY(pinky->getY() - (ghostSpeed));
			}
		}
		// BLINKY
		if (gameRunning) {
			if ((blinky->getX() >= bX - buffer && blinky->getX() <= bX + buffer) &&
				(blinky->getY() >= bY - buffer && blinky->getY() <= bY + buffer)) {
				blinky->up();
				if (blinkyPos == 2) {
					blinky->setY(bY);
				}
				blinkyPos = 1;
				std::cout << "Moving up" << std::endl;
			}
			// Move blinky down
			if ((blinky->getX() >= bX - buffer && blinky->getX() <= bX + buffer) &&
				(blinky->getY() >= pY - buffer && blinky->getY() <= pY + buffer)) {
				blinky->down();
				if (blinkyPos == 1) {
					blinky->setY(pY);
				}
				blinkyPos = 2;
				std::cout << "Moving down" << std::endl;
			}
			if (blinkyPos == 1) {
				blinky->setY(blinky->getY() + (ghostSpeed));
			}
			if (blinkyPos == 2) {
				blinky->setY(blinky->getY() - (ghostSpeed));
			}
		}
		// INKY
		if (gameRunning) {
			// Move inky down
			if ((inky->getX() >= iX - buffer && inky->getX() <= iX + buffer) &&
				(inky->getY() >= iY - buffer && inky->getY() <= iY + buffer)) {
				inky->up();
				if (inkyPos == 4) {
					inky->setX(iX);
				}
				inkyPos = 1;
				std::cout << "Moving up" << std::endl;
			}
			// Move inky right
			if ((inky->getX() >= iX - buffer && inky->getX() <= iX + buffer) &&
				(inky->getY() >= bY - buffer && inky->getY() <= bY + buffer)) {
				inky->down();
				if (inkyPos == 1) {
					inky->setY(bY);
				}
				inkyPos = 2;
				std::cout << "Moving down" << std::endl;
			}
			// Move inky up
			if ((inky->getX() >= cX - buffer && inky->getX() <= cX + buffer) &&
				(inky->getY() >= bY - buffer && inky->getY() <= bY + buffer)) {
				inky->down();
				if (inkyPos == 2) {
					inky->setX(cX);
				}
				inkyPos = 3;
				std::cout << "Moving down" << std::endl;
			}
			// Move inky left
			if ((inky->getX() >= cX - buffer && inky->getX() <= cX + buffer) &&
				(inky->getY() >= iY - buffer && inky->getY() <= iY + buffer)) {
				inky->down();
				if (inkyPos == 3) {
					inky->setY(iY);
				}
				inkyPos = 4;
				std::cout << "Moving down" << std::endl;
			}
			if (inkyPos == 1) {
				inky->setY(inky->getY() - (ghostSpeed));
			}
			if (inkyPos == 2) {
				inky->setX(inky->getX() + (ghostSpeed));
			}
			if (inkyPos == 3) {
				inky->setY(inky->getY() + (ghostSpeed));
			}
			if (inkyPos == 4) {
				inky->setX(inky->getX() - (ghostSpeed));
			}
		}
		// CLYDE
		if (gameRunning) {
			// Move clyde left
			if ((clyde->getX() >= cX - buffer && clyde->getX() <= cX + buffer) &&
				(clyde->getY() >= cY - buffer && clyde->getY() <= cY + buffer)) {
				clyde->up();
				if (clydePos == 6) {
					clyde->setY(cY);
				}
				clydePos = 1;
			}
			// Move clyde down
			if ((clyde->getX() >= iX - buffer && clyde->getX() <= iX + buffer) &&
				(clyde->getY() >= cY - buffer && clyde->getY() <= cY + buffer)) {
				clyde->down();
				if (clydePos == 1) {
					clyde->setX(iX);
				}
				clydePos = 2;
			}
			// Move clyde left (2nd time)
			if ((clyde->getX() >= iX - buffer && clyde->getX() <= iX + buffer) &&
				(clyde->getY() >= cY2 - buffer && clyde->getY() <= cY2 + buffer)) {
				clyde->down();
				if (clydePos == 2) {
					clyde->setY(cY2);
				}
				clydePos = 3;
			}
			// Move clyde up
			if ((clyde->getX() >= pX - buffer && clyde->getX() <= pX + buffer) &&
				(clyde->getY() >= cY2 - buffer && clyde->getY() <= cY2 + buffer)) {
				clyde->down();
				if (clydePos == 3) {
					clyde->setX(pX);
				}
				clydePos = 4;
			}
			// Move clyde right
			if ((clyde->getX() >= pX - buffer && clyde->getX() <= pX + buffer) &&
				(clyde->getY() >= pY - buffer && clyde->getY() <= pY + buffer)) {
				clyde->down();
				if (clydePos == 4) {
					clyde->setY(pY);
				}
				clydePos = 5;
			}
			// Move clyde down (2nd time)
			if ((clyde->getX() >= cX - buffer && clyde->getX() <= cX + buffer) &&
				(clyde->getY() >= pY - buffer && clyde->getY() <= pY + buffer)) {
				clyde->down();
				if (clydePos == 5) {
					clyde->setX(cX);
				}
				clydePos = 6;
			}
			if (clydePos == 1) {
				clyde->setX(clyde->getX() - (ghostSpeed));
			}
			if (clydePos == 2) {
				clyde->setY(clyde->getY() - (ghostSpeed));
			}
			if (clydePos == 3) {
				clyde->setX(clyde->getX() - (ghostSpeed));
			}
			if (clydePos == 4) {
				clyde->setY(clyde->getY() + (ghostSpeed));
			}
			if (clydePos == 5) {
				clyde->setX(clyde->getX() + (ghostSpeed));
			}
			if (clydePos == 6) {
				clyde->setY(clyde->getY() - (ghostSpeed));
			}
		}
	}
	
	//******************************************************************************************

	//-------------------------------GHOST COLLISION DETECTION----------------------------------		(@MM)
	if (!hit && gameRunning) {
		float ghostPos[4][2];																// Holds the positions of the ghosts
		float bounds = size * 0.75;															// Creates hitbox bounds based on current size of Pacman & ghosts
		ghostPos[0][0] = blinky->getX();
		ghostPos[0][1] = blinky->getY();

		ghostPos[1][0] = pinky->getX();
		ghostPos[1][1] = pinky->getY();

		ghostPos[2][0] = inky->getX();
		ghostPos[2][1] = inky->getY();

		ghostPos[3][0] = clyde->getX();
		ghostPos[3][1] = clyde->getY();

		for (int i = 0; i < 4; i++) {
			if (abs(pacman->getX() - (ghostPos[i][0])) <= bounds && abs(pacman->getY() - (ghostPos[i][1])) <= bounds) {
				hit = true;
				gameRunning = false;
			}
		}
	}
	if (hit && !gameRunning) {
		moving = false;
		spawn = false;
		pacHit->setX(pacman->getX());
		pacHit->setY(pacman->getY());
		pacman->disappear();
		//waka->stop();
		pacHit->reappear();
		pacHit->playOnce();
		//dead->playOnce();
		if (lives >= 0) {
			lives -= 1;
			gameRunning = true;
			if (lives >= 0) {
				std::cout << "Lives remaining: " << lives << std::endl;
			}
		}
	}
	//------------------------------------------------------------------------------------------
	if (lives < 0) {
		gameOver = true;
	}
}

void Game::draw() const {
	if (!gameOver) {
		// DRAW STAGE (@DB)
		yellowColumn->draw();
		pinkColumn->draw();
		redColumn->draw();
		blueColumn->draw();
		orangeColumn->draw();
		stageBorder1->draw();
		stageBorder2->draw();
		sB1->draw();
		sB2->draw();

		// DRAW PACMAN AND GHOSTS (@MM)
		pacman->draw(0.5);
		pacHit->draw(0.5);
		blinky->draw(0.6);
		pinky->draw(0.7);
		inky->draw(0.8);
		clyde->draw(0.9);

		if (!spawn) {
			respawn->draw(1.0);
			spacebar->draw(1.0);
		}
		// DRAW LIVES (@MM)
		if (lives == 3) {
			life1->draw(1.0);
		}
		if (lives >= 2) {
			life2->draw(1.0);
		}
		if (lives >= 1) {
			life3->draw(1.0);
		}
	}

	// DRAW GAME OVER SCREEN (@MM)
	else {
		lost->draw(1.0);
		pacHit->draw(0.5);
	}
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == 'p'){
		ghostMove = false;
    }
    else if (key == 'r'){
		ghostMove = true;
    }
	if (!hit && !gameOver) {
		if (key == 'w' && upCmd) {
			std::cout << "Moving up" << std::endl;
			pacman->up();
			moving = true;
			moveUp = true;
			moveLeft = false;
			moveRight = false;
			moveDown = false;
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (key == 'a' && leftCmd) {
			std::cout << "Moving left" << std::endl;
			pacman->left();
			moving = true;
			moveLeft = true;
			moveUp = false;
			moveRight = false;
			moveDown = false;
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (key == 'd' && rightCmd) {
			std::cout << "Moving right" << std::endl;
			pacman->right();
			moving = true;
			moveRight = true;
			moveUp = false;
			moveLeft = false;
			moveDown = false;
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (key == 's' && downCmd) {
			std::cout << "Moving down" << std::endl;
			pacman->down();
			moving = true;
			moveDown = true;
			moveUp = false;
			moveLeft = false;
			moveRight = false;
//            if (!soundPlaying) {
//                soundPlaying = true;
//                waka->play();
//            }
		}
		if (key == ']') {
			if (speed <= 0.01 - 0.0001) {
				speed += 0.0001;
			}
		}
		if (key == '[') {
			if (speed >= 0.0001) {
				speed -= 0.0001;
			}
		}
		if (key == ' ') {
			moving = false;
//            soundPlaying = false;
//            waka->stop();
		}
		if (key == 'k') {
			hit = true;
			gameRunning = false;
			std::cout << "Hit!" << std::endl;
		}
	}	
	else if (hit && !gameOver) {
		if (key == ' ') {
			moving = false;
			//soundPlaying = false;
			hit = false;
			gameRunning = true;
			upCmd = true;
			leftCmd = true;
			rightCmd = true;
			downCmd = true;
			spawn = true;
			pacman->setX(spawnX);
			pacman->setY(spawnY);
			blinky->setX(bX);
			blinky->setY(bY);
			inky->setX(iX);
			inky->setY(iY);
			pinky->setX(pX);
			pinky->setY(pY);
			clyde->setX(cX);
			clyde->setY(cY);
			pacHit->disappear();
			pacman->reappear();
			sB1->setX(sB1x);
			sB1->setY(sB1y);
			sB2->setX(sB2x);
			sB2->setY(sB2y);
		}
	}
}

void Game::handleKeyUp(unsigned char key, float x, float y) {
	
}

Game::~Game(){
    stop();
	delete pacman;
	delete pacHit;
	delete pinky;
	delete blinky;
	delete inky;
	delete clyde;
	delete yellowColumn;
	delete pinkColumn;
	delete redColumn;
	delete blueColumn;
	delete orangeColumn;
	delete stageBorder1;
	delete stageBorder2;
	delete lost;
	delete life1;
	delete life2;
	delete life3;
}
