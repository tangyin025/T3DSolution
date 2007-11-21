/*
 * File: console1_1/main.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "MyApp.h"
#include "MyDyn.h"

#include <iostream>
using namespace std;

#define TEST_EXPR(expr) \
	if(expr) \
	{ \
		std::cout << str_printf("succeed: %s", (#expr)) << std::endl; \
	} \
	else \
	{ \
		std::cout << str_printf("failure: %s", (#expr)) << std::endl; \
	}

int main(int argc, char ** argv)
{
	VECTOR4D v0, v1;

	// a box just in x plane, z == 0
	VECTOR4D_InitXYZ(&v0, 0, 0, 0);
	VECTOR4D_InitXYZ(&v1, 1, 1, 0);
	t3dBox box0(v0, v1);
	TEST_EXPR(t3dBox::flat == box0.get_type());

	// a box 1, 1, 1
	VECTOR4D_InitXYZ(&v0, 0, 0, 0);
	VECTOR4D_InitXYZ(&v1, 1, 1, 1);
	t3dBox box1(v0, v1);

	// a box .5, .5, .5
	VECTOR4D_InitXYZ(&v0, -0.5, -0.5, -0.5);
	VECTOR4D_InitXYZ(&v1,  0.5,  0.5,  0.5);
	t3dBox box2(v0, v1);

	t3dBox box3 = box1 & box2;
	t3dBox box4 = box1 | box2;

	TEST_EXPR(box3 == t3dBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5));
	TEST_EXPR(box4 == t3dBox(-0.5, -0.5, -0.5, 1, 1, 1));

	return 0;
}
