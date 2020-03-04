#include "stage.h"
#include<iostream>

using namespace std;

stage::stage() {
	float x = 0.1;
	stageBorder1 = new Rect(-0.93, -0.28 - x, 1.86, -1.16, 0.0, 0.0, 0.0);				// Black background
	stageBorder2 = new Rect(-0.95, -0.3 - x, 1.9, -1.2, 1.0, 1.0, 1.0);					// White border
	stageColumn1 = new Rect(-0.8, -0.2 - x, 0.4, -0.35, 1.0, 0.0, 0.0);					// Bottom left
	stageColumn2 = new Rect(-0.26, 0.5 - x, 0.6, -0.3, 0.0, 1.0, 0.0);					// Top middle
	stageColumn3 = new Rect(-0.26, 0.35 - x, 0.6, 0.55, 0.0, 1.0, 0.0);
	stageColumn4 = new Rect(0.5, -0.2 - x, 0.3, -1.0, 0.0, 0.0, 1.0);
	stageColumn5 = new Rect(-0.8, 0.8 - x, 0.4, 0.5, 1.0, 0.5, 0.0);
}

void stage::draw() const {
	stageColumn1->draw();
	stageColumn2->draw();
	stageColumn3->draw();
	stageColumn4->draw();
	stageColumn5->draw();
	stageBorder1->draw();
	stageBorder2->draw();
	
}

stage::~stage() {
	delete stageBorder1;
	delete stageBorder2;
	delete stageColumn1;
	delete stageColumn2;
	delete stageColumn3;
	delete stageColumn4;
}

