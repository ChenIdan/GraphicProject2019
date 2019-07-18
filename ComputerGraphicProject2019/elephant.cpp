#include "elephant.h"
#include "Matrices.h"
#include "Vectors.h"

#define SIZE_SCALE_FACTOR 0.05 //elephant size

#define VERTEX_NORMAL_ANGEL 45

//elephant movment rate params
#define Dx 1
#define Dz 1




//rotation speed
#define Dtheta 1

elephant::elephant(GLfloat _locX,GLfloat _height,GLfloat _locZ, GLfloat _theta)
{

	locX = _locX;
	locZ = _locZ;

	height = _height;
	
	theta = _theta;

	char objfname[] = "_elephant.obj";


	obj_model = glmReadOBJ(objfname); //load object model file

	//set normals and textures
	glmFacetNormals(obj_model);
	glmVertexNormals(obj_model, VERTEX_NORMAL_ANGEL);
	glmSpheremapTexture(obj_model);

	//setting up elephant size
	glmScale(obj_model, SIZE_SCALE_FACTOR);




}

void elephant::Draw() {

	//draw elephant at the requierd location
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	glTranslatef(locX, 0, locZ);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(theta, 0, 1, 0);

	if (is_moving) {
		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 1, 1);



		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);
		//move posX

		locX += translation_Vec.x;
		height += translation_Vec.y;
		locZ += translation_Vec.z;
	}

	glPopMatrix();
	glRotatef(theta, 0, 1, 0);
	
	
	glmDraw(obj_model, GLM_SMOOTH | GLM_MATERIAL);

	glPopMatrix();

	
	

	
}

void elephant::moveLeft() {
	locX =+ -Dx;

}

void elephant::moveRight() {
	locX = +Dx;

}


void elephant::moveBackward() {
	locZ = -Dz;

}

void elephant::moveForward() {
	locZ = -Dz;

}


