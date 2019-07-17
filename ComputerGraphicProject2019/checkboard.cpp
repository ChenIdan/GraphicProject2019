

#include "checkboard.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>     /* srand, rand */


GLfloat CHECKBOARD_WHITE[] = { 1, 1, 1 };
GLfloat CHECKBOARD_RED[] = { 1, 0, 0 };
GLfloat CHECKBOARD_GREEN[] = { 0, 1, 0 };
GLfloat CHECKBOARD_MAGENTA[] = { 1, 0, 1 };



checkboard::checkboard(int my_width, int my_depth) {
	width = my_width;
	depth = my_depth;
}

float checkboard::centerx()
{
	return width / 2;
}

float checkboard::centerz()
{
	return depth / 2;
}

void checkboard::create()
{
	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);
	
	
	
	glBegin(GL_QUADS);
	for (int x = 0; x < width - 1; x += 1) {
		
		for (int z = 0; z < depth - 1; z += 1) {
			
			
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
				((x+z) % 2 == 0) ? CHECKBOARD_RED : CHECKBOARD_WHITE);
			for (float tx = 0; tx < 1; tx += 0.1) {
				for (float tz = 0; tz <1; tz += 0.1) {
				
					glNormal3d(0, 1, 0);

					glVertex3d(x+tx, 0, z+tz);
					glVertex3d(x+tx + 0.1, 0, z+tz);
					glVertex3d(x+tx + 0.1, 0, z+tz + 0.1);
					glVertex3d(x+tx, 0,z+ tz + 0.1);
				


				}
			}
		}
	}
	glEnd();
	
	glEndList();
}

void checkboard::draw() {
	glCallList(displayListId);
}

