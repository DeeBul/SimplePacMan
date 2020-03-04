#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "pacChar.h"
#include "ghostChar.h"


class App: public GlutApp {
	pacChar* pacman;
	ghostChar* blinky;														// Blinky = Red Ghost
	ghostChar* pinky;														// Pinky = Pink Ghost (Duh)
	//ghostChar* inky;															// Inky = Cyan Ghost
	//ghostChar* clyde;														// Clyde = Orange Ghost
public:
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
	void sound();
	float speed;
	float size;
    
	void blinkyPlace();
	void pinkyPlace();
    void keyDown(unsigned char key, float x, float y);
	void keyUp(unsigned char key, float x, float y);
    
    ~App();
    
    friend void timer(int);
    
};

#endif
