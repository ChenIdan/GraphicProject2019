#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
class camera
{

private:


public:
	float posX; // camera position

	float posY; 
	float posZ;

	float thetaX; // camera angle with x axis

	float thetaY; //camera angle with y axis



	float maxX;
	float minX;

	float maxY;
	float minY;

	float maxZ;
	float minZ;

	

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void moveBackward();
	void moveForward();


	void rotateX_left();
	void rotateX_right();
	void rotateY_up();
	void rotateY_down();

	float get_posX();
	float get_posY();
	float get_posZ();


	static void multiplyMatrix(GLfloat* mat1[], GLfloat * mat2[], GLfloat* res[], int N);


	camera(float posX,float posY,float posZ, float thetaX,float thetaY, float maxX, float maxY, float maxZ, float  minX, float minY, float minZ);
};

