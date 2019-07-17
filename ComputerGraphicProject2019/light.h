#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

class light

{
private: 
	float posY;
	GLfloat ambient[4];

	GLfloat specular[4];

	GLfloat diffuse[4];

	float spot_exp;

	void set_ambient(float *ambient);

	void set_specular(float *specular);

	void set_diffuse(float *diffuse);

	float cutoff_angle;

	int maxX;

	int maxZ;
	
	int minZ;
	
	int minX;


public:
	float posX;
	float posZ;

	float angleX;

	float angleZ;

	

	

	float const_atennuation;
	float linear_attenuation;
	float quadratic_attenuation;

	void set_pos(float x, float y);

	void set_cuttof_angle(float theta);

	void set_const_atennuation(float c);
	void set_linear_atennuation(float c);
	void set_quadratic_attenuation(float c);

	void increase_angleX();

	void decrease_angleX();

	void increase_angleZ();

	void decrease_angleZ();

	float get_height();

	float* get_diffuse();

	float* get_ambient();

	float* get_specular();

	float get_cutoff_angle();

	float get_spot_exp();

	void moveForward();

	void moveInward();

	void moveRight();

	void moveLeft();








	light(float posX ,float posZ,  float cutoff_angle, float const_atennuation, float linear_attenuation, float quadratic_attenuation, int maxX, int maxZ, int minZ, int minX);

};

