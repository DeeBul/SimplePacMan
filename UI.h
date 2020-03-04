#ifndef UI_h
#define UI_h

#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif


class UI : public Rect {
protected:
	GLuint texture_id;

public:
	UI(const char*, float, float, float, float);
	int lives;
	const char* file;
	void draw(float z) const;
	void setImg(int);
};

#endif