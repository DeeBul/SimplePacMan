#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"


class App: public GlutApp {
	AnimatedRect* pacman;
	AnimatedRect* blinky;														// Blinky = Red Ghost
	AnimatedRect* pinky;														// Pinky = Pink Ghost (Duh)
	AnimatedRect* inky;															// Inky = Cyan Ghost
	AnimatedRect* clyde;														// Clyde = Orange Ghost
public:
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
	float speed;
	float size;
    
    void keyDown(unsigned char key, float x, float y);
	void keyUp(unsigned char key, float x, float y);
    
    ~App();
    
    friend void timer(int);
    
};

#endif
