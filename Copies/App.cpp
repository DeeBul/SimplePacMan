#include <iostream>
#include "App.h"
#include <cstdlib>
#include <Windows.h>
#include <MMSystem.h>

App* singleton;
AnimatedRect* movement;
bool moving = false;
bool moveUp = false;
bool moveDown = false;
bool moveLeft = false;
bool moveRight = false;
bool soundPlaying = false;

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

	ghostPos[2][0] = singleton->inky->getX();
	ghostPos[2][1] = singleton->inky->getY();

	ghostPos[3][0] = singleton->clyde->getX();
	ghostPos[3][1] = singleton->clyde->getY();
	//--------------------------------------------

	float bounds = singleton->size * 0.75;
	float moveSpeed = singleton->speed;
	if (moving) {
		if (soundPlaying == true) {
			PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		if (moveUp) {
			singleton->pacman->setY(singleton->pacman->getY() + moveSpeed);
			
		}
		else if (moveDown) {
			singleton->pacman->setY(singleton->pacman->getY() - moveSpeed);
			
		}
		else if (moveLeft) {
			singleton->pacman->setX(singleton->pacman->getX() - moveSpeed);
			//PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else if (moveRight) {
			singleton->pacman->setX(singleton->pacman->getX() + moveSpeed);
			//PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else {
			moving = false;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (abs(singleton->pacman->getX() - (ghostPos[i][0])) <= bounds && abs(singleton->pacman->getY() - (ghostPos[i][1])) <= bounds) {
			std::cout << "You're dead" << std::endl;
			//PlaySound(TEXT(""), NULL, SND_APPLICATION);
		}
	}
    glutTimerFunc(16, timer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
	size = 0.2;
	pacman = new AnimatedRect("pacman.png", 4, 5, 20, true, true, 0.0,  0.0, size, size);
	blinky = new AnimatedRect("Blinky-Down.png", 1, 2, 100, true, true, -0.8, 0.6, size, size);
	pinky = new AnimatedRect("Pinky-Down.png", 1, 2, 100, true, true, -0.4, 0.6, size, size);
	inky = new AnimatedRect("Inky-Down.png", 1, 2, 100, true, true, 0.2, 0.6, size, size);
	clyde = new AnimatedRect("Clyde-Down.png", 1, 2, 100, true, true, 0.6, 0.6, size, size);
	speed = 0.01;
	
    singleton = this;    
    timer(1);
}

void App::draw() {
	pacman->draw(0.5);
	blinky->draw(0.6);
	pinky->draw(0.7);
	inky->draw(0.8);
	clyde->draw(0.9);
}

void App::keyDown(unsigned char key, float x, float y){
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
		soundPlaying = true;
    }
	if (key == 'a') {
		pacman->left();
		moving = true;
		moveLeft = true;
		moveUp = false;
		moveRight = false;
		moveDown = false;
		std::cout << "Moving left" << std::endl;
		soundPlaying = true;
	}
	if (key == 'd') {
		pacman->right();
		moving = true;
		moveRight = true;
		moveUp = false;
		moveLeft = false;
		moveDown = false;
		std::cout << "Moving right" << std::endl;
		soundPlaying = true;
	}
	if (key == 's') {
		pacman->down();
		moving = true;
		moveDown = true;
		moveUp = false;
		moveLeft = false;
		moveRight = false;
		std::cout << "Moving down" << std::endl;
		soundPlaying = true;
	}
	if (key == ']') {
		singleton->speed += 0.005;
	}
	if (key == '[') {
		singleton->speed -= 0.005;
	}
}

void App::keyUp(unsigned char key, float x, float y) {
	if (key == 'w') {
		//moving = false;
		//moveUp = false;
		//soundPlaying = false;
	}
	if (key == 'a') {
		//moving = false;
		//moveLeft = false;
		//soundPlaying = false;
	}
	if (key == 'd') {
		//moving = false;
		//moveRight = false;
		//soundPlaying = false;
	}
	if (key == 's') {
		//moving = false;
		//moveDown = false;
		//soundPlaying = false;
	}
}

App::~App(){
    delete pacman;
    std::cout << "Exiting..." << std::endl;
}

