#include "elephant_legs.h"
#include "Object_Model.h"
#include <stdio.h>

char back_left_obj[] = "back_left.obj";
char front_left_obj[] = "front_left.obj";
char back_right_obj[] = "back_right.obj";
char front_right_obj[] = "front_right.obj";

elephant_legs::elephant_legs(float _locX, float _locY, float _locZ , float my_size_scale_factor, float my_vertex_normal_angel)
{

	locX = _locX;
	locY = _locY;
	locZ = _locZ;

	size_scale_factor = my_size_scale_factor;
	vertex_normal_angel = my_vertex_normal_angel;

	leg_rot = 0;

	elephant_angel = 0;

	front_right = Object_Model(front_right_obj,locX, locY, locZ, size_scale_factor, 0, 0, 0, my_vertex_normal_angel);
	front_left = Object_Model(front_left_obj, locX, locY, locZ, size_scale_factor, 0, 0, 0, my_vertex_normal_angel);
	back_right = Object_Model(back_right_obj, locX, locY, locZ, size_scale_factor, 0, 0, 0, my_vertex_normal_angel);
	back_left= Object_Model(back_left_obj, locX, locY, locZ, size_scale_factor, 0, 0, 0, my_vertex_normal_angel);

	
}


void elephant_legs::Update(bool draw) {

	Object_Model arr[] = { front_right, front_left, back_right, back_left };
	int i;
	for (i = 0; i < 4; i++) {
		arr[i].thetaY = elephant_angel; //sets leg rotation angel
		arr[i].locX = locX;
		arr[i].locY = locY;
		arr[i].locZ = locZ;
		arr[i].Update(draw);
	}

}

void elephant_legs::move_legs() {

}

elephant_legs::elephant_legs() {

}

