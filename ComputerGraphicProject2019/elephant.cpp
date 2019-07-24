#include "elephant.h"
#include "Matrices.h"
#include "Vectors.h"
#include "glm.h"


//elephant body parts obj files directories

char back_left[] = "back_left.obj";
char front_left[] = "front_left.obj";
char back_right[] = "back_right.obj";
char front_right[] = "front_right.obj";
char body_file[] = "body.obj";
char head_file[]="head.obj";
char tail_file[] = "tail.obj";
char trunk_file[] = "trunk.obj";


#define SIZE_SCALE_FACTOR 0.025 //elephant size

#define VERTEX_NORMAL_ANGEL 45

//elephant movment rate params
#define Dx 1
#define Dz 1





//rotation speed
#define Dtheta 1

elephant::elephant(GLfloat _locX,GLfloat _height,GLfloat _locZ, GLfloat _theta, bool* _elephant_pov){

	tail = Object_Model(tail_file,_locX, _height, _locZ, SIZE_SCALE_FACTOR, 0, 0, 0, VERTEX_NORMAL_ANGEL);
	trunk = Object_Model(trunk_file, _locX, _height, _locZ, SIZE_SCALE_FACTOR, 0, 0, 0, VERTEX_NORMAL_ANGEL);
	head = Object_Model(head_file, _locX, _height, _locZ, SIZE_SCALE_FACTOR, 0, 0, 0, VERTEX_NORMAL_ANGEL);
	body = Object_Model(body_file, _locX, _height, _locZ, SIZE_SCALE_FACTOR, 0, 0, 0, VERTEX_NORMAL_ANGEL);
	legs = elephant_legs(_locX, _height, _locZ, SIZE_SCALE_FACTOR, VERTEX_NORMAL_ANGEL);

	locX = _locX;
	locZ = _locZ;

	height = _height;
	
	theta = _theta;
	elephant_pov = _elephant_pov;

}




void elephant::Update() {

	//draw elephant at the requierd location

	Object_Model arr[] = { tail,head, body, trunk };

	int i;

	head.locX = locX;
	head.locY = height; 
	head.locZ = locZ;

	head.thetaY = theta;

	head.thetaX = 0;



	
	head.Update(draw);

	trunk.locX = locX;
	trunk.locY = height;
	trunk.locZ = locZ; 

	trunk.thetaY = head.thetaY;

	trunk.thetaX = head.thetaX;

	trunk.Update(draw);


	body.locX = locX;
	body.locY = height;
	body.locZ = locZ;

	body.thetaY = theta;

	body.Update(draw);

	tail.locX = locX;
	tail.locY = height;
	tail.locZ = locZ;

	tail.thetaY = theta;

	tail.Update(draw);

	legs.locX = locX; 
	legs.locY = height;
	legs.locZ = locZ;
	legs.elephant_angel = theta;
	legs.Update(draw);
	

	printf("elephant angel: %f\n", theta);
	
	

	
}

void elephant::move() {
	

		glPushMatrix();
		glLoadIdentity();
		glRotatef(theta, 0, 1, 0);


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
		glPopMatrix();
	

}




