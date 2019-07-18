#pragma once

#include "glm.h"


#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif



class elephant
{
private :
	GLMmodel* obj_model; //elepahtn obj file
	GLfloat size;
	GLfloat height;
public:
	bool is_moving = false;
	GLfloat locX, locZ;

	GLfloat theta; //elephant angle

	elephant(GLfloat locX,GLfloat _height, GLfloat locZ, GLfloat theta);

	void moveRight();
	void moveLeft();
	void moveBackward();
	void moveForward();
	void Draw();

	
};

