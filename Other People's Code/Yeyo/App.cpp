#include <iostream>
#include <ctime>
#include "App.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <Windows.h>
#include <MMSystem.h>

using namespace std;

App* singleton;
bool moving = false;
bool moveUp = false;
bool moveDown = false;
bool moveLeft = false;
bool moveRight = false;
bool soundPlaying = false;

bool ghostShift = true;
//bool ghostUp = false;
//bool ghostDown = false;
//bool ghostLeft = false;
//bool ghostRight = false;

int blinkyPos, pinkyPos;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer
	//--------------------------------------------

	float ghostPos[4][2];
	ghostPos[0][0] = singleton->blinky->getX();
	ghostPos[0][1] = singleton->blinky->getY();

	ghostPos[1][0] = singleton->pinky->getX();
	ghostPos[1][1] = singleton->pinky->getY();

	//ghostPos[2][0] = singleton->inky->getX();
	//ghostPos[2][1] = singleton->inky->getY();

	//ghostPos[3][0] = singleton->clyde->getX();
	//ghostPos[3][1] = singleton->clyde->getY();
	//--------------------------------------------

	float bounds = singleton->size * 0.75;
	float moveSpeed = singleton->speed;

	if (moving) {
		soundPlaying = true;
		if (moveUp) {
			singleton->pacman->setY(singleton->pacman->getY() + moveSpeed);
			soundPlaying = true;
		}
		else if (moveDown) {
			singleton->pacman->setY(singleton->pacman->getY() - moveSpeed);
			soundPlaying = true;
		}
		else if (moveLeft) {
			singleton->pacman->setX(singleton->pacman->getX() - moveSpeed);
			soundPlaying = true;
		}
		else if (moveRight) {
			singleton->pacman->setX(singleton->pacman->getX() + moveSpeed);
			soundPlaying = true;
		}
		else {
			moving = false;
			ghostShift = true;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (abs(singleton->pacman->getX() - (ghostPos[i][0])) <= bounds && abs(singleton->pacman->getY() - (ghostPos[i][1])) <= bounds) {
			std::cout << "You're dead" << std::endl;
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------

	if (ghostShift) {
		singleton->pinkyPlace();
		singleton->blinkyPlace();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------

    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title) : GlutApp(argc, argv, width, height, title) {
	size = 0.2;
	pacman = new pacChar("pacman.png", 4, 5, 20, true, true, true, 0.0,  0.0, size, size);
	blinky = new ghostChar("Blinky-Down.png", 1, 2, 100, true, true, true, -0.8, 0.6, size, size);
	pinky = new ghostChar("Pinky-Down.png", 1, 2, 100, true, true, true, -0.4, 0.6, size, size);
	//inky = new ghostChar("Inky-Down.png", 1, 2, 100, true, true, true, 0.2, 0.6, size, size);
	//clyde = new ghostChar("Clyde-Down.png", 1, 2, 100, true, true, true, 0.6, 0.6, size, size);
	speed = 0.01;
	
    singleton = this;    
    timer(1);
}

void App::draw() {
	pacman->draw(0.5);
	blinky->draw(0.6);
	pinky->draw(0.7);
	//inky->draw(0.8);
	//clyde->draw(0.9);
}

void App::sound() {
	if (soundPlaying) {
		if (moving) {
			PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
	else if (!soundPlaying) {
		PlaySound(NULL, 0, 0);
	}
}


void App::blinkyPlace() {

	if (blinkyPos == 1) {
		blinky->setY(blinky->getY() + (speed));
	}
	if (blinkyPos == 2) {
		blinky->setY(blinky->getY() - (speed));
	}
	if (blinkyPos == 3 || blinkyPos == 0) {
		blinky->setX(blinky->getX() - (speed));
	}
	if (blinkyPos == 4) {
		blinky->setX(blinky->getX() + (speed));
	}
	//Change to up
	if ((blinky->getX() > 0.89 && blinky->getX() < 0.91) && (blinky->getY() > -0.91 && blinky->getY() < -0.89)) {
		blinky->up();
		blinkyPos = 1;
	}
	//Change to down
	if ((blinky->getX() > -0.91 && blinky->getX() < -0.89) && (blinky->getY() > 0.89 && blinky->getY() < 0.91)) {
		blinky->down();
		blinkyPos = 2;
	}
	if ((blinky->getX() > -0.91 && blinky->getX() < -0.89) && (blinky->getY() > 0.59 && blinky->getY() < 0.61)) {
		blinky->down();
		blinkyPos = 2;
	}
	//Change to left
	if ((blinky->getX() > 0.99 && blinky->getX() < 1.01) && (blinky->getY() > 0.89 && blinky->getY() < 0.91)) {
		blinky->left();
		blinkyPos = 3;
	}
	//Change to right
	if ((blinky->getX() > -0.91 && blinky->getX() < -0.89) && (blinky->getY() > -0.91 && blinky->getY() < -0.89)) {
		blinky->right();
		blinkyPos = 4;
	}
	else {
		ghostShift = true;
	}
}

void App::pinkyPlace() {

	if (pinkyPos == 1) {
		pinky->setY(pinky->getY() + (speed));
	}
	if (pinkyPos == 2) {
		pinky->setY(pinky->getY() - (speed));
	}
	if (pinkyPos == 3) {
		pinky->setX(pinky->getX() - (speed));
	}
	if (pinkyPos == 4 || pinkyPos == 0) {
		pinky->setX(pinky->getX() + (speed));
		pinkyPos = 4;
	}
	//Change to up
	if ((pinky->getX() > -0.41 && pinky->getX() < -0.39) && (pinky->getY() > 0.199 && pinky->getY() < 0.21)) {
		pinky->up();
		pinkyPos = 1;
	}
	//Change to down
	if ((pinky->getX() < 0.41 && pinky->getX() > 0.39) && (pinky->getY() < 0.61 && pinky->getY() > 0.59)) {
		pinky->down();
		pinkyPos = 2;
	}
	//Change to left
	if ((pinky->getX() < 0.41 && pinky->getX() > 0.39) && (pinky->getY() > 0.199 && pinky->getY() < 0.21)) {
		pinky->left();
		pinkyPos = 3;
	}
	//Change to right
	if ((pinky->getX() > -0.41 && pinky->getX() < -0.39) && (pinky->getY() < 0.61 && pinky->getY() > 0.59)) {
		pinky->right();
		pinkyPos = 4;
	}

	else {
		ghostShift = true;
	}
}

void App::keyDown(unsigned char key, float x, float y){

	ghostShift = true;

    if (key == 27){
        exit(0);
    }
    if (key == 'w'){
		pacman->up();
		moving = true;
		moveUp = true;
		moveLeft = false;
		moveRight = false;
		moveDown = false;
		std::cout << "Moving up" << std::endl;
		if (!soundPlaying) {
			soundPlaying = true;
			PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
    }
	if (key == 'a') {
		pacman->left();
		moving = true;
		moveUp = false;
		moveLeft = true;
		moveRight = false;
		moveDown = false;
		std::cout << "Moving left" << std::endl;
		if (!soundPlaying) {
			soundPlaying = true;
			PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
	if (key == 'd') {
		pacman->right();
		moving = true;
		moveUp = false;
		moveLeft = false;
		moveRight = true;
		moveDown = false;
		std::cout << "Moving right" << std::endl;
		if (!soundPlaying) {
			soundPlaying = true;
			PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
	if (key == 's') {
		pacman->down();
		moving = true;
		moveUp = false;
		moveLeft = false;
		moveRight = false;
		moveDown = true;
		std::cout << "Moving down" << std::endl;
		if (!soundPlaying) {
			soundPlaying = true;
			PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
	if (key == ']') {
		singleton->speed += 0.005;
	}
	if (key == '[') {
		singleton->speed -= 0.005;
	}
	if (key == ' ') {
		moving = false;
		soundPlaying = false;
		PlaySound(NULL, 0, 0);
	}
}

void App::keyUp(unsigned char key, float x, float y) {

	if (key == 'w') {
		//moving = false;
		moveUp = false;
		soundPlaying = false;
		
	}
	if (key == 'a') {
		//moving = false;
		moveLeft = false;
		soundPlaying = false;
	}
	if (key == 'd') {
		//moving = false;
		moveRight = false;
		soundPlaying = false;
	}
	if (key == 's') {
		//moving = false;
		moveDown = false;
		soundPlaying = false;
	}
}

App::~App(){
    delete pacman;
    std::cout << "Exiting..." << std::endl;
}

