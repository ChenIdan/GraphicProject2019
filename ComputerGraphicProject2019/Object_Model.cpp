#include "Object_Model.h"
#include <GL/freeglut.h>
#define MAX_TILT 2
#define MIN_TILT -2

#define D_tilt 0.5
Object_Model::Object_Model() {

}

Object_Model::Object_Model(char* my_file, GLfloat my_locX, GLfloat my_locY, GLfloat my_locZ, GLfloat  my_size_scale_factor, 
	GLfloat my_thetaX, GLfloat my_thetaY, GLfloat my_thetaZ, GLfloat vertex_normal_angle)
{

	//initialize object properties
	locX = my_locX;
	locY = my_locY;
	locZ = my_locZ;

	size_scale_factor = my_size_scale_factor;

	thetaX = my_thetaX;
	thetaY = my_thetaY;
	thetaZ = my_thetaZ;
	//read object file
	obj_ptr = glmReadOBJ(my_file);

	//set normals and textures
	glmFacetNormals(obj_ptr);
	glmVertexNormals(obj_ptr, vertex_normal_angle);
	glmSpheremapTexture(obj_ptr);

	//setting up  size
	glmScale(obj_ptr, my_size_scale_factor);

	

}

/*
drawing the object
*/

void Object_Model::Update(bool draw) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//move to object location
	glTranslatef(locX, locY, locZ);

	

	if (tilt_up_and_down) {
		tilt_up_down();
	}

	else if (tilt_left_and_right) {
		tilt_left_right();
	}

	//rotate according to angles
	glRotatef(thetaX + vertical_tilt, 1, 0, 0);
	glRotatef(thetaY + horizontal_tilt, 0, 1, 0);
	glRotatef(thetaZ, 0, 0, 1);

	if (draw) {
		glmDraw(obj_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		
	}

	glPopMatrix();

}



void Object_Model::tilt_up_down() {
	if (tilt_down) {
		if (vertical_tilt < MIN_TILT) {
			tilt_down = !tilt_down;
		}

		else {
			vertical_tilt += -D_tilt;
		}
	}

	else {
		if (vertical_tilt > MAX_TILT) {
			tilt_down = !tilt_down;
		}

		else {
			vertical_tilt += D_tilt;
		}
	}


}

void Object_Model::tilt_left_right() {
	if (tilt_right) {
		if (horizontal_tilt < MIN_TILT) {
			tilt_right = !tilt_right;
		}

		else {
			horizontal_tilt += -D_tilt;
		}
	}

	else {
		if (horizontal_tilt > MAX_TILT) {
			tilt_right = !tilt_right;
		}

		else {
			horizontal_tilt += D_tilt;
		}
	}



}



void Object_Model::end_tilt() {
	tilt_left_and_right = false;
	tilt_up_and_down = false;

	vertical_tilt = 0;
	horizontal_tilt = 0;

	tilt_right = false;
	tilt_down = false;

}

void Object_Model::start_tilt_left_right() {
	vertical_tilt = 0;
	horizontal_tilt = 0;

	tilt_left_and_right = true;
	tilt_up_and_down = false;
	tilt_right = true;

}

void Object_Model::start_tilt_up_down() {
	vertical_tilt = 0;
	horizontal_tilt = 0;

	tilt_left_and_right = false;
	tilt_up_and_down = true;
	tilt_down = true;

}

GLfloat Object_Model::get_horizontal_tilt() {
	return horizontal_tilt;
}

GLfloat Object_Model::get_vertical_tilt() {
	return vertical_tilt;
}
