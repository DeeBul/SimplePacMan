#ifndef stage_h
#define stage_h

#include "Rect.h"
#include "AppComponent.h"

class stage : public AppComponent, public Rect {
	Rect* stageBorder1;
	Rect* stageBorder2;
	Rect* stageColumn1;
	Rect* stageColumn2;
	Rect* stageColumn3;
	Rect* stageColumn4;
	Rect* stageColumn5;

public:
	stage();
	void draw() const;
	~stage();
};

#endif /* stage_h */
