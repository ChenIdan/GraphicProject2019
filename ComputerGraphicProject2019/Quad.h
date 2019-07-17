#pragma once

#include "Quad.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
class Quad
{
private: 
	GLfloat vertex1[3];

	GLfloat vertex2[3];

	GLfloat vertex3[3];

	GLfloat vertex4[3];

	GLfloat normal[3];

	GLfloat color[3];



public:
	Quad(GLfloat vertex1[3], GLfloat vertex2[3], GLfloat vertex3[3], GLfloat vertex4[3], GLfloat normal, GLfloat color[3]);
	void draw(Quad qd);
	~Quad();
};

