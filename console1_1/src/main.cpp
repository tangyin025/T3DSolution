/**
 * File: console1_1/main.cpp
 */

#include <iostream>
using namespace std;
#include <xmmintrin.h>

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib6.h"

bool foo(int elem)
{
	cout << elem << ", ";
	return true;
}

int main(int argc, char ** argv)
{
	//cout << foo() << endl;

	//VECTOR2D v1 = {1.0f, 1.0f};
	//VECTOR2D v2 = {0.0f, 1.0f};
	//VECTOR3D_PTR vp;
	//cout << VECTOR2D_CosTheta(&v1, &v2) << endl;
	//cout << RAD_TO_DEG(0.5 * PI) << endl;
	//cout << DEG_TO_RAD(45) / PI << endl;
	//cout << sizeof(*vp) << endl;

	//VECTOR3D v1 = {1.0f, 1.0f, 0.0f},
	//		 v2 = {1.0f, 1.0f, 1.0f};
	//cout << VECTOR3D_Length(&v1) << endl;
	//cout << VECTOR3D_Length(&v2) << endl;
	//cout << VECTOR3D_CosTheta(&v1, &v2) << endl;
	//printf("%.10f\n", VECTOR3D_CosTheta(&v1, &v2));

	//VECTOR3D v1 = {1.0f, 0.0f, 0.0f},
	//		 v2 = {0.0f, 1.0f, 0.0f},
	//		 v3;
	//VECTOR3D_Cross(&v3, &v1, &v2);
	//VECTOR3D_Print(&v3);
	//cout << endl;

	//MATRIX4X4 m = {	2.0f, 4.0f,	3.0f, 8.0f,
	//				5.1f, 6.0f, 7.0f, 8.8f,
	//				7.7f, 9.9f, 1.4f, 6.6f,
	//				1.1f, 2.1f, 3.3f, 2.9f};
	//MATRIX4X4 m2;
	//MATRIX4X4_Print(&m);
	//cout << endl;
	//MATRIX4X4_Print(Mat_Transpose_4X4(&m2, &m));
	//cout << endl;
	//MATRIX4X4_Print(Mat_Transpose_4X4(&m));
	//cout << endl;

	//VECTOR2D v1(2.0f, 3.0f);
	//VECTOR2D v2(4.0f, 5.0f);
	//VECTOR2D v3, v4;
	//v3 = v1 + v2;
	//VECTOR2D_Add(&v4, &v1, &v2);
	//VECTOR2D_Print(&v3);
	//cout << endl;
	//VECTOR2D_Print(&v4);

	//MATRIX2X2_Print(&MATRIX2X2::IDENTITY);

	//ERRORREP errrep;
	//Regist_Error_Reporter(&errrep);
	//char error[MAX_PATH];
	//char c[MAX_PATH];
	//cout << "please input error message:" << endl;
	//cin >> error;
	//Set_Last_Error(error, __FILE__, __LINE__);

	//do
	//{
	//	cout << "show the last error now? (Y/N)" << endl;
	//	cin >> c;
	//}
	//while(strncmp(c, "y", 2) && strncmp(c, "Y", 2));

	//char stmp[MAX_PATH];
	//int itmp;
	//cout << Get_Last_Error(error, stmp, &itmp) << endl;

	//short a[100], b[100];
	//Mem_Set_Word(a, -1, sizeof(a) / sizeof(*a));
	//Mem_Cpy_Word(b, a, sizeof(a) / sizeof(*a));
	//cout << a[0] << ", " << a[99] << endl;
	//cout << b[0] << ", " << b[99] << endl;
	//cout << a << " : " << a[100] << endl;
	//cout << b << " : " << b[100] << endl;
	//cout << &b[104] << " : " << b[104] << endl;

	//Init_T3dlib4(32);
	//RGB32 c1, c2, c3;
	//c1 = _RGB32BIT(123, 0, 255);
	//c2 = _RGB32BIT(25, 25, 255);
	//RGB32_Mul(&c3, &c1, &c2);
	//cout << _32BIT_GETR(c3) << endl;
	//cout << _32BIT_GETG(c3) << endl;
	//cout << _32BIT_GETB(c3) << endl;

	//Init_T3dlib4(32);
	//cout << "PF_MMX_INSTRUCTIONS_AVAILABLE == "
	//	<< IsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE) << endl;
	//cout << "PF_XMMI_INSTRUCTIONS_AVAILABLE == "
	//	<< IsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE) << endl;

	//VECTOR4D v0, v1, v2;
	//VECTOR4D_InitXYZ(&v0, 1.0, 2.0, 3.0);
	//VECTOR4D_InitXYZ(&v1, 2.0, 3.0, 4.0);
	//cout << "v0" << endl;
	//VECTOR4D_Print(&v0);
	//cout << "v1" << endl;
	//VECTOR4D_Print(&v1);
	//_asm
	//{
	//	movaps	xmm0,	v0._M
	//	//pfadd	xmm0,	v1._M	// for 3dnow instruction
	//	addps	xmm0,	v1._M	// for sse instruction
	//	movaps	v2._M,	xmm0
	//}
	//cout << "v0 + v1" << endl;
	//VECTOR4D_Print(&v2);
	//_asm
	//{
	//	movaps	xmm0,	v0._M
	//	mulps	xmm0,	v1._M
	//	movaps	v2._M,	xmm0
	//}
	//cout << "v0 * v1" << endl;
	//VECTOR4D_Print(&v2);

	//MATRIX4X4 m = {	1.0, 2.0, 3.0, 1.0,
	//				1.0, 2.0, 3.0, 1.0,
	//				1.0, 2.0, 3.0, 1.0,
	//				1.0, 2.0, 3.0, 1.0, };
	//VECTOR3D_Mul(&v1._3D, 2.0);
	//Mat_Mul_VECTOR4D_4X4(&v2, &v1, &m);
	//VECTOR4D_Print(&v1);
	//VECTOR4D_Print(&v2);
	//REAL rad = (REAL)3.1415968489;
	//REAL deg = RAD_TO_DEG(rad);
	//cout << deg << endl;

	typedef struct SLIST<int> MyList;
	typedef struct SLIST_NODE<int> MyNode;
	MyList list;
	MyNode * pnode, * phead, * plast;

	Create_SList(&list, 5);
	for(int i = 0; i < 5; i++)
	{
		Append_SList(&list, &pnode);
		pnode->elem = i;
	}

	plast = phead = pnode = GetHead_SList(&list);
	while(phead != GetNext_SList(&list, &pnode))
	{
		if(pnode->elem % 2 == 0)
		{
			Remove_SNode(plast, pnode);
			pnode = plast;
		}
		plast = pnode;
	}

	phead = pnode = GetHead_SList(&list);
	while(phead != GetNext_SList(&list, &pnode))
	{
		std::cout << pnode->elem << ", ";
	}

	Clear_SList(&list);
	phead = pnode = GetHead_SList(&list);
	while(phead != GetNext_SList(&list, &pnode))
	{
		std::cout << pnode->elem << ", ";
	}

	Destroy_SList(&list);

	return 0;
}
