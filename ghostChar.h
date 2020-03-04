#ifndef ghostChar_h
#define ghostChar_h

#include "TexRect.h"
#include "Timer.h"

class ghostChar : public TexRect, protected Timer {

	int rows;
	int cols;

	int curr_row;
	int curr_col;

	bool complete;

	bool loop;

	bool animating;
	bool visible;
	bool ghost;

	void advance();
	bool done();

	bool flipped;
	bool ghostUp;
	bool ghostDown;
	bool ghostLeft;
	bool ghostRight;

public:


	ghostChar(const char*, int, int, int, bool, bool, float, float, float, float);

	void draw(float z);

	void playLoop();

	void playOnce();

	void reset();

	void pause();

	void resume();

	void action();

	void play();

	void flip();

	void up();

	void down();

	void left();

	void right();

};

#endif
#pragma once
