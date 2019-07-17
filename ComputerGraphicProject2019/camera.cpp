#include "camera.h"
#include <cmath>
#include "Vectors.h"
#include "Matrices.h"
#define Dt 1

#define D_theta 4

#define max_angle 360

camera::camera(float posX, float posY, float posZ, float thetaX, float thetaY, float maxX, float maxY, float maxZ, float  minX, float minY, float minZ):
	posX(posX), posY(posY), posZ(posZ), thetaX(thetaX),thetaY(thetaY),maxX(maxX), minX(minX),maxY(maxY), minY(minY), maxZ(maxZ), minZ(minZ)
{}
float camera::get_posX() {return  posX; }
float camera::get_posY() { return posY; }
float camera::get_posZ() { return posZ; }
void   camera::moveRight() {
	if (posX < maxX)
		{

		//get the translation matrix in the current camera coordinate system
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-thetaX, 1, 0, 0);
		glRotatef(-thetaY, 0, 1, 0);
		glTranslatef(Dt, 0, 0);
		glRotatef(thetaY, 0, 1, 0);
		glRotatef(thetaX, 1, 0, 0);
		

		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 0, 1);


		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);
		//move posX
		if (translation_Vec.x>0) {
			if (posX < maxX) {
				posX += translation_Vec.x;
			}

		}

		else {
			if (posX > minX) {
				posX += translation_Vec.x;
			}
		}


		//move posY

		if (translation_Vec.y>0) {
			if (posY < maxY) {
				posY += translation_Vec.y;
			}

		}

		else {
			if (posY > minY) {
				posY += translation_Vec.y;
			}
		}

		//move posZ

		if (translation_Vec.z>0) {
			if (posZ < maxX) {
				posZ += translation_Vec.z;
			}

		}

		else {
			if (posZ > minY) {
				posZ += translation_Vec.z;
			}
		}
	}
}
void  camera::moveLeft() { 
	if (posX > minX)
		{

		//get the translation matrix in the current camera coordinate system
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-thetaX, 1, 0, 0);
		glRotatef(-thetaY, 0, 1, 0);
		glTranslatef(-Dt, 0, 0);
		glRotatef(thetaY, 0, 1, 0);
		glRotatef(thetaX, 1, 0, 0);
		

		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 0, 1);
		glPopMatrix();

		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);
		//move posX
		if (translation_Vec.x>0) {
			if (posX < maxX) {
				posX += translation_Vec.x;
			}

		}

		else {
			if (posX > minX) {
				posX += translation_Vec.x;
			}
		}


		//move posY

		if (translation_Vec.y>0) {
			if (posY < maxY) {
				posY += translation_Vec.y;
			}

		}

		else {
			if (posY > minY) {
				posY += translation_Vec.y;
			}
		}

		//move posZ

		if (translation_Vec.z>0) {
			if (posZ < maxX) {
				posZ += translation_Vec.z;
			}

		}

		else {
			if (posZ > minY) {
				posZ += translation_Vec.z;
			}
		}
	}
}
void   camera::moveUp() {
	if (posY < maxY) {
		//get the translation matrix in the current camera coordinate system
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-thetaX, 1, 0, 0);
		glRotatef(-thetaY, 0, 1, 0);
		glTranslatef(0, Dt, 0);
		glRotatef(thetaY, 0, 1, 0);
		glRotatef(thetaX, 1, 0, 0);
		
		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 0, 1);
		glPopMatrix();


		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);
		//move posX
		if (translation_Vec.x>0) {
			if (posX < maxX) {
				posX += translation_Vec.x;
			}

		}

		else {
			if (posX > minX) {
				posX += translation_Vec.x;
			}
		}


		//move posY

		if (translation_Vec.y>0) {
			if (posY < maxY) {
				posY += translation_Vec.y;
			}

		}

		else {
			if (posY > minY) {
				posY += translation_Vec.y;
			}
		}

		//move posZ

		if (translation_Vec.z>0) {
			if (posZ < maxX) {
				posZ += translation_Vec.z;
			}

		}

		else {
			if (posZ > minY) {
				posZ += translation_Vec.z;
			}
		}
	}
}
			
void   camera::moveDown() { 
	if (posY > minY) {		//get the translation matrix in the current camera coordinate system
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-thetaX, 1, 0, 0);
		glRotatef(-thetaY, 0, 1, 0);
		glTranslatef(0, -Dt, 0);
		glRotatef(thetaY, 0, 1, 0);
		glRotatef(thetaX, 1, 0, 0);
		

		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 0, 1);
		glPopMatrix();

		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);
		//move posX
		if (translation_Vec.x>0) {
			if (posX < maxX) {
				posX += translation_Vec.x;
			}

		}

		else {
			if (posX > minX) {
				posX += translation_Vec.x;
			}
		}


		//move posY

		if (translation_Vec.y>0) {
			if (posY < maxY) {
				posY += translation_Vec.y;
			}

		}

		else {
			if (posY > minY) {
				posY += translation_Vec.y;
			}
		}

		//move posZ

		if (translation_Vec.z>0) {
			if (posZ < maxX) {
				posZ += translation_Vec.z;
			}

		}

		else {
			if (posZ > minY) {
				posZ += translation_Vec.z;
			}
		}
	}
} 

void   camera::moveForward() {
	if (posZ < maxZ) 
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-thetaX, 1, 0, 0);
		glRotatef(-thetaY, 0, 1, 0);
		glTranslatef(0, 0, Dt);
		glRotatef(thetaY, 0, 1, 0);
		glRotatef(thetaX, 1, 0, 0);
		

		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 0, 1);

		glPopMatrix();

		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);
		//move posX
		if (translation_Vec.x>0) {
			if (posX < maxX) {
				posX += translation_Vec.x;
			}

		}

		else {
			if (posX > minX) {
				posX += translation_Vec.x;
			}
		}


		//move posY

		if (translation_Vec.y>0) {
			if (posY < maxY) {
				posY += translation_Vec.y;
			}

		}

		else {
			if (posY > minY) {
				posY += translation_Vec.y;
			}
		}

		//move posZ

		if (translation_Vec.z>0) {
			if (posZ < maxX) {
				posZ += translation_Vec.z;
			}

		}

		else {
			if (posZ > minY) {
				posZ += translation_Vec.z;
			}
		}
	}
}

void   camera::moveBackward() { 
	if (posZ > minZ)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-thetaX, 1, 0, 0);
		glRotatef(-thetaY, 0, 1, 0);
		glTranslatef(0, 0, -Dt);
		glRotatef(thetaY, 0, 1, 0);
		glRotatef(thetaX, 1, 0, 0);
		

		//get the translation vector in the current camera coordinate system
		float matrixf[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
		Matrix4 modelview_mat = Matrix4(matrixf);
		Vector4 zero_vec = Vector4(0, 0, 0, 1);
		glPopMatrix();

		//translate camera position
		Vector4 translation_Vec = modelview_mat.operator*(zero_vec);

		//move posX
		if (translation_Vec.x>0) {
			if (posX < maxX) {
				posX += translation_Vec.x;
			}
			
		}

		else {
			if (posX > minX) {
				posX += translation_Vec.x;
			}
		}
		

		//move posY
		
		if (translation_Vec.y>0) {
			if (posY < maxY) {
				posY += translation_Vec.y;
			}

		}

		else {
			if (posY > minY) {
				posY += translation_Vec.y;
			}
		}
		
		//move posZ

		if (translation_Vec.z>0) {
			if (posZ < maxX) {
				posZ+= translation_Vec.z;
			}

		}

		else {
			if (posZ > minY) {
				posZ += translation_Vec.z;
			}
		}
	} 
}


void camera::rotateX_left() { if (thetaX > 0) { thetaX -= D_theta; } }
void camera::rotateX_right() { if (thetaX < max_angle) { thetaX += D_theta; } }

void camera::rotateY_up() { if (thetaY > 0) { thetaY -= D_theta; } }
void camera::rotateY_down() { if (thetaY < max_angle) { thetaY += D_theta; } }



