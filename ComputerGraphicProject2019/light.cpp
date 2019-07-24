#include "light.h"

#define SPOTLIGHT_EXP 10
#define SPOTLIGHT_HEIGHT 10

#define angleX_max 45
#define angleX_min -45

#define angleZ_max 45
#define angleZ_min -45

#define D_THETA 3
#define Dt 2
#define INIT_ANGLEX 0
#define INIT_ANGLEZ 0

GLfloat _ambient[4] = { 1,1, 1, 1.0 };

GLfloat _diffuse[4] = { 1,1, 1, 1.0 };

GLfloat _specular[4] = { 1,1, 1, 1.0 };

light::light(float posX, float posZ, float cutoff_angle, float const_atennuation, float linear_attenuation, float quadratic_attenuation, int maxX, int maxZ, int minZ, int minX) :
	posX(posX), posZ(posZ), cutoff_angle(cutoff_angle), angleX(0) , angleZ(0), const_atennuation(const_atennuation), linear_attenuation(linear_attenuation), 
	quadratic_attenuation(quadratic_attenuation),
	spot_exp(SPOTLIGHT_EXP),posY(SPOTLIGHT_HEIGHT), maxX(maxX), maxZ(maxZ), minZ(minZ), minX(minX)
{
	set_specular(_specular);
	set_ambient(_ambient);
	set_diffuse(_diffuse);
}


void light::set_pos(float x, float z) {
	posX = x;
	posZ = z;
}

void light::set_const_atennuation(float c) {
	const_atennuation = c;

}

void light::set_linear_atennuation(float c) {
	linear_attenuation = c;
}

void light::set_quadratic_attenuation(float c) {
	quadratic_attenuation = c;
}

void light::set_cuttof_angle(float theta) {
	cutoff_angle = theta;
}

void light::set_ambient(float *_ambient) {
	ambient[0] = _ambient[0];
	ambient[1] = _ambient[1];
	ambient[2] = _ambient[2];
	ambient[3] = _ambient[3];
}

void light::set_specular(float *_specular) {
	specular[0] = _specular[0];
	specular[1] = _specular[1];
	specular[2]=_specular[2];
	specular[3] = _specular[3];
}

void light::set_diffuse(float *_diffuse) {
	diffuse[0] = _diffuse[0];
	diffuse[1] = _diffuse[1];
	diffuse[2] = _diffuse[2];
	diffuse[3] = _diffuse[3];
}

void light::increase_angleX() {
	if (angleX < angleX_max){
		angleX +=  D_THETA;
	}
}

void light::increase_angleZ() {
	if (angleZ < angleZ_max) {
		angleZ +=  D_THETA;
	}
}


void light::decrease_angleX() {
	if (angleX > angleX_min) {
		angleX -= D_THETA;
	}
}

void light::decrease_angleZ() {
	if (angleZ > angleZ_min) {
		angleZ -= D_THETA;
	}
}

float light::get_height() {
	return posY;
}

float* light::get_specular() {
	return specular;
}

float* light::get_ambient() {
	return ambient;
}

float* light::get_diffuse() {
	return diffuse;
}

float light::get_cutoff_angle() {
	return cutoff_angle;
}

float light::get_spot_exp() {
	return spot_exp;
}

void light::moveRight() {
	if (posX < maxX-3) {
		posX+= Dt;

	}
}

void light::moveLeft() {
	if (posX > minX+3) {
		posX -= Dt;

	}
}

void light::moveForward() {
	if (posZ < maxZ-3) {
		posZ += Dt;

	}
}

void light::moveInward() {

	if (posZ > minZ+3) {
		posZ -= Dt;

	}
	
}
