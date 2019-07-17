#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

class checkboard
{

private:
	int displayListId;

public:
	int width;
	int depth;
	
	
	void create();
	float centerx();
	float centerz();
	void draw();
	checkboard(int my_width, int my_depth);
	
};

