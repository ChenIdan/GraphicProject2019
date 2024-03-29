﻿//Jeff Chastine
#include <Windows.h>
#include "colors.h"
#include <iostream>
#include "camera.h"
#include "checkboard.h"
#include "light.h"
#include "elephant.h"


GLfloat general_light_ambient[] = { 0.1,0.1, 0.6,1 };
GLfloat general_light_diffuse[] = { 0.5,0.5, 0.5,1 };
GLfloat general_light_specular[] = { 0.1,0.1, 0.1,1 };;


#pragma warning(disable:4996)

bool show_window = true;


// This application shows balls bouncing on a checkerboard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <cmath>



#include "imgui_impl_freeglut.h"
#include "imgui_impl_opengl2.h"
#include "Imgui.h"



//gui window
const ImVec2 win_size(30.0, 30.0);
static ImVec4 clear_color = ImVec4(0, 0, 0, 0.00f);

// Colors

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.
class Ball {
	double radius;
	GLfloat* color;
	double maximumHeight;
	double x;
	double y;
	double z;
	int direction;
public:
	Ball(double r, GLfloat* c, double h, double x, double z) :
		radius(r), color(c), maximumHeight(h), direction(-1),
		y(h), x(x), z(z) {
	}
	void update() {
		y += direction * 0.05;
		if (y > maximumHeight) {
			y = maximumHeight; direction = -1;
		}
		else if (y < radius) {
			y = radius; direction = 1;
		}
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glTranslated(x, y, z);
		glutSolidSphere(radius, 30, 30);
		glPopMatrix();
	}
};

// A checkerboard class.  A checkerboard has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).

// Global variables: a camera, a checkerboard and some balls.

checkboard board(64, 64);
float pos[3] = { 0,2,0 };
camera Camera(board.centerx(),2,board.centerz(),0,0, board.width,max(board.width, board.depth),board.depth, 0, 0,0);
elephant my_elephant(20, 0, 20,0, & Camera.elephant_pov);

light spotlight(board.centerx(), board.centerz(), 90, 0.5, 0.1, 0, board.width, board.depth, 0, 0);
char file[] = "Low-Poly-Racing-Car.obj";
//Object_Model Iron_Men(file, 20, 0, 20, 0.025, 0, 0, 0, 45);

Ball balls[] = {
	Ball(1, GREEN, 7, board.centerx(), board.centerz()),
	Ball(1.5, MAGENTA, 6, board.centerx()+2, board.centerz()+2),
	Ball(0.4, WHITE, 5, board.centerx() - 2, board.centerz() - 2)
};


// Application-specific initialization: Set up global lighting parameters
// and create display lists.


void init() {

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//Depth states
	glClearDepth(2.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glEnable(GL_CULL_FACE);

	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);


	// blending
	//glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	

	

	//setting up positional spotlight

	glLightfv(GL_LIGHT0, GL_AMBIENT, spotlight.get_ambient());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotlight.get_diffuse());
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotlight.get_specular());
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlight.get_cutoff_angle());
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, spotlight.const_atennuation);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, spotlight.quadratic_attenuation);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, spotlight.linear_attenuation);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotlight.get_spot_exp());

	//setting up directional light

	glLightfv(GL_LIGHT1, GL_AMBIENT, general_light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, general_light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, general_light_specular);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.25);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.25);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.25);

	//syncs specular reflection with the viewr
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);



	//setting up checkboard material properties

	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);




	board.create();



}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {

	ImGui_ImplFreeGLUT_ReshapeFunc(w, h);


	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, GLfloat(w) / GLfloat(h), 1.0, 150);
	glMatrixMode(GL_MODELVIEW);

}

// function for drawing GUI
void my_display_code() {

	static camera tmp_camera = Camera; //saves current camera if user chooses elephant pov


	//begin ImGui frame. the flag ImGuiWindowFlags_MenuBar is responsinle for the menu bar in the frame
	ImGui::Begin("User Interface",NULL, ImGuiWindowFlags_MenuBar);
	
	

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("GUI style")) {
			if (ImGui::MenuItem("Classic")) {
				ImGui::StyleColorsClassic();
			}
			if (ImGui::MenuItem("Dark")) {
				ImGui::StyleColorsDark();
			}
			if (ImGui::MenuItem("Light")) {
				ImGui::StyleColorsLight();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("quit")) {
			ImGui::EndMenu();
			glutLeaveMainLoop();

		}
		ImGui::EndMenuBar();
	}

	if (ImGui::CollapsingHeader("elephant controlers")) {
		
		
		if (*my_elephant.elephant_pov) {

			
			ImGui::SliderFloat("rotate", &my_elephant.theta, 0,  360);
			
			

		}

		else {
			ImGui::SliderFloat("rotate", &my_elephant.theta, 0, 360);

		}
		if (ImGui::RadioButton("move", my_elephant.is_moving)) {
			my_elephant.is_moving = !my_elephant.is_moving;

		}
		

		

		if (ImGui::CollapsingHeader("tilt elephant_head")) {
			if (ImGui::RadioButton("tilt head up and down", my_elephant.head.tilt_up_and_down)) {
				if (!my_elephant.head.tilt_up_and_down) {
					my_elephant.head.start_tilt_up_down();
					my_elephant.trunk.start_tilt_up_down();
				}

				else {
					my_elephant.head.end_tilt();
					my_elephant.trunk.end_tilt();
				}
				


		    }
			if (ImGui::RadioButton("tilt head right and left", my_elephant.head.tilt_left_and_right)) {
				if (!my_elephant.head.tilt_left_and_right) {
					my_elephant.head.start_tilt_left_right();
					my_elephant.trunk.start_tilt_left_right();
				}
				else {
					my_elephant.head.end_tilt();
					my_elephant.trunk.end_tilt();
				}
				

			}
		}

		if (ImGui::CollapsingHeader("tilt elephant tail")) {
			if (ImGui::RadioButton("tilt tail up and down", my_elephant.tail.tilt_up_and_down)) {
				if (!my_elephant.tail.tilt_up_and_down) {
					my_elephant.tail.start_tilt_up_down();
					
				}

				else {
					my_elephant.tail.end_tilt();
					
				}



			}
			if (ImGui::RadioButton("tilt tail right and left", my_elephant.tail.tilt_left_and_right)) {
				if (!my_elephant.tail.tilt_left_and_right) {
					my_elephant.tail.start_tilt_left_right();
				}
				else {
					my_elephant.tail.end_tilt();
				}


			}
		}


		
		if (ImGui::RadioButton("elephant pov", Camera.elephant_pov)) {
			
			
			Camera.elephant_pov = !Camera.elephant_pov;
			if(Camera.elephant_pov){
				tmp_camera = Camera;

				
				Camera.posX = my_elephant.head.locX;
				Camera.posY = my_elephant.head.locY;
				Camera.posZ = my_elephant.head.locZ;
				
			}

			if (!Camera.elephant_pov) {

				my_elephant.theta = -Camera.thetaY; //get elephant angel in respect to the viewing coordinate system
				my_elephant.theta += 180; // flip elephant angel, becuase of the head direction

				my_elephant.locX = Camera.posX;
				my_elephant.locZ = Camera.posZ;

				Camera = tmp_camera;
				
				
				Camera.elephant_pov = !Camera.elephant_pov;
				
			}

		}


	}


	if (ImGui::CollapsingHeader("Adjust Lighting")) {
		ImGui::ColorEdit3("adjust ambient light", (float *)&general_light_ambient);
		ImGui::ColorEdit3("adjust specular light", (float *)&general_light_specular);


		}

	if (ImGui::CollapsingHeader("help")) {
		

		if (ImGui::TreeNode("Camera Controlers")){
			ImGui::Text("Press -> to move camera right ");
			ImGui::Text("Press <- to move camera left ");
			ImGui::Text("Press up arrow to move camera up ");
			ImGui::Text("Press down to move camera down ");
			ImGui::Text("Press -  to move camera forward ");
			ImGui::Text("Press + to move camera forward ");
			ImGui::Text("Press l to rotate camera to the right ");
			ImGui::Text("Press v to rotate camera to the left ");
			ImGui::Text("Press r to rotate camera up ");
			ImGui::Text("Press q to rotate camera down ");
			ImGui::TreePop();
			ImGui::Separator();
			
		}

		if (ImGui::TreeNode("Light Controlers")) {
			ImGui::Text("Press -> to move camera right ");
			ImGui::Text("Press <- to move camera left ");
			ImGui::Text("Press up arrow to move camera up ");
			ImGui::Text("Press down to move camera down ");
			ImGui::Text("Press -  to move camera forward ");
			ImGui::Text("Press + to move camera forward ");
			ImGui::Text("Press 1 to rotate light to the right in the x direction ");
			ImGui::Text("Press 2 to rotate light to the left  in the x direction ");
			ImGui::Text("Press 3 to rotate light  to the right in the y direction ");
			ImGui::Text("Press 4 to rotate light to the left in the y direction ");
			ImGui::TreePop();
			ImGui::Separator();

		}
		
		

		}

	ImGui::End();
		
		
	}
	

// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void display() {

	// Start the ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplFreeGLUT_NewFrame();

	my_display_code();//rendering gui

	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	

	glMatrixMode(GL_MODELVIEW);

	
	glLoadIdentity();


	printf("Camera angel : %d\n", Camera.thetaX);

	//init camera with elephant locations and values if we are at elephant pov
	if (Camera.elephant_pov) {
		
		
		
		Camera.posY = 3;

		Camera.thetaX = my_elephant.head.get_vertical_tilt();

		printf("%d\n", Camera.thetaX);
		Camera.thetaY = -my_elephant.theta - my_elephant.head.get_horizontal_tilt(); //make elephant rotation direction to be negtive, because 
																				//elephant rotation is negtive in respect to global coordinate system
			
		Camera.thetaY+= 180 ; //flip Camera direction in z axis, because the elephant initial head direction is the vector (0,0,-1)

		//setting up camera direction

		glRotatef(Camera.thetaX, 1, 0, 0);
		glRotatef(Camera.thetaY, 0, 1, 0);


		//setting up viewing coordinates

		glTranslatef(-Camera.posX, -Camera.posY, -Camera.posZ);

		
		if (my_elephant.is_moving) {
			Camera.moveBackward();
		}
		
	}
	
	else {

		
		//setting up camera direction
		glRotatef(Camera.thetaX, 1, 0, 0);
		glRotatef(Camera.thetaY, 0, 1, 0);

		//setting up viewing coordinates

		glTranslatef(-Camera.posX, -Camera.posY, -Camera.posZ);
		if (my_elephant.is_moving) {


			my_elephant.move();

		}
	}

	

	//setting up light position and direction in the viewing coordinates, so the light position and direction wont be affected from moving the camera 

	GLfloat lightPosition[4] = { spotlight.posX, spotlight.get_height(),spotlight.posZ, 1 };

	GLfloat _lightPosition[4] = { board.centerx(), 3,board.centerz(),1};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); // spotlight position setting
	glLightfv(GL_LIGHT1, GL_POSITION, _lightPosition); // general light position setting
	glLightfv(GL_LIGHT1, GL_AMBIENT, general_light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, general_light_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, general_light_diffuse);

	//light direction setting
	glRotatef(spotlight.angleX, 1, 0, 0);
	glRotatef(spotlight.angleZ, 0, 0, 1);

	GLfloat lightdir[4] = { 0, -1,0, 1 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightdir);
	glRotatef(-spotlight.angleZ, 0, 0, 1);
	glRotatef(-spotlight.angleX, 1, 0, 0);


	for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
		balls[i].update();
	}

	my_elephant.draw = !Camera.elephant_pov;

	my_elephant.Update(); // draws elephant
	
	//Iron_Men.Draw();
	glTranslatef(50, 3, 50);
	glutSolidTeapot(2);
	glTranslatef(-50, -3, -50);
	
	glPushMatrix();
	board.draw();
	glutSolidCube(1);

	glPopMatrix();

	//draws gui window
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glFlush();

	glutSwapBuffers();
}



// Requests to draw the next frame.
void timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, v);
	
}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {

	if(!Camera.elephant_pov){
		switch (key) {
		case GLUT_KEY_LEFT: Camera.moveLeft(); break;
		case GLUT_KEY_RIGHT: Camera.moveRight(); break;
		case GLUT_KEY_UP: Camera.moveUp(); break;
		case GLUT_KEY_DOWN: Camera.moveDown(); break;

		}
	}
	
	
	glutPostRedisplay();
}

void normal(unsigned char key, int, int) {
	
		if (!Camera.elephant_pov) {
			switch (key) {
				case '+': Camera.moveBackward(); break;
				case '-': Camera.moveForward(); break;
				case 'q': Camera.rotateX_left(); break;
				case 'v':  Camera.rotateX_right(); break;
				case 't': Camera.rotateY_up(); break;
				case 'l': Camera.rotateY_down(); break;



				case '1': spotlight.increase_angleX(); break;
				case '2':spotlight.decrease_angleX(); break;
				case '3': spotlight.increase_angleZ(); break;
				case '4':spotlight.decrease_angleZ(); break;
				case '5':spotlight.moveRight(); break;
				case '6':spotlight.moveLeft(); break;
				case '7':spotlight.moveForward(); break;
				case '8':spotlight.moveInward(); break;
			}
	}


	glutPostRedisplay();

}


// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {

	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bouncing Balls");
	init();

	// Setup GLUT display function
	// We will also call ImGui_ImplFreeGLUT_InstallFuncs() to get all the other functions installed for us, 
	// otherwise it is possible to install our own functions and call the imgui_impl_freeglut.h functions ourselves.



	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	io.Fonts->AddFontDefault();

	

	//glut functions setting with my functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(normal);
	glutTimerFunc(100, timer, 0);

	//glut function setting with ImGui implementation for freeglut functions, so we can have control the gui as we want to
	
	glutMotionFunc(ImGui_ImplFreeGLUT_MotionFunc);
	glutPassiveMotionFunc(ImGui_ImplFreeGLUT_MotionFunc);
	glutMouseFunc(ImGui_ImplFreeGLUT_MouseFunc);
	glutMouseWheelFunc(ImGui_ImplFreeGLUT_MouseWheelFunc);

	ImGui_ImplFreeGLUT_Init();
	//ImGui_ImplFreeGLUT_InstallFuncs();
	//ImGui_ImplOpenGL2_Init();


	


	// Setup style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	glutMainLoop();

	// Cleanup
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplFreeGLUT_Shutdown();
	ImGui::DestroyContext();

	return 0;

}