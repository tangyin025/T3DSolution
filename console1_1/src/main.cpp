/*
 * File: console1_1/main.cpp
 */

#include <iostream>
using namespace std;
#include <xmmintrin.h>
#include <crtdbg.h>

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"
#pragma comment(lib, "winmm.lib")

bool foo(int elem)
{
	cout << elem << ", ";
	return true;
}

void Print_Bone_Position(BONE_ARRAYV1 * pbones, BONE_SINGLE_ARRAYV1 * pbone_singles, size_t root, int indent)
{
	int i;
	for(i = 0; i < indent; i++)
		printf("\t");

	VECTOR4D_Print(&pbone_singles->elems[root].kpos.vkey);

	for(i = 0; i < (int)pbones->elems[root].subs.length; i++)
	{
		Print_Bone_Position(pbones, pbone_singles, pbones->elems[root].subs.elems[i], indent + 1);
	}
}

void Print_Bone_Rotation(BONE_ARRAYV1 * pbones, BONE_SINGLE_ARRAYV1 * pbone_singles, size_t root, int indent)
{
	int i;
	for(i = 0; i < indent; i++)
		printf("\t");

	VECTOR4D_Print(&pbone_singles->elems[root].krot.vkey);

	for(i = 0; i < (int)pbones->elems[root].subs.length; i++)
	{
		Print_Bone_Rotation(pbones, pbone_singles, pbones->elems[root].subs.elems[i], indent + 1);
	}
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

	//typedef struct SLIST<int> MyList;
	//typedef struct SLIST_NODE<int> MyNode;
	//MyList list;
	//MyNode * pnode, * phead, * plast;

	//Create_SList(&list, 5);
	//for(int i = 0; i < 5; i++)
	//{
	//	Append_SList(&list, &pnode);
	//	pnode->elem = i;
	//}

	//plast = phead = pnode = GetHead_SNode(&list);
	//while(phead != GetNext_SNode(&list, &pnode))
	//{
	//	if(pnode->elem % 2 == 0)
	//	{
	//		Remove_SNode(plast, pnode);
	//		pnode = plast;
	//	}
	//	plast = pnode;
	//}

	//phead = pnode = GetHead_SNode(&list);
	//while(phead != GetNext_SNode(&list, &pnode))
	//{
	//	std::cout << pnode->elem << ", ";
	//}
	//std::cout << std::endl;

	////for(int i = 1; i < (int)list.length; i++)
	////	std::cout << list.nodes[i].elem << ", ";
	////std::cout << std::endl;

	//Clear_SList(&list);
	//phead = pnode = GetHead_SNode(&list);
	//while(phead != GetNext_SNode(&list, &pnode))
	//{
	//	std::cout << pnode->elem << ", ";
	//}
	//std::cout << std::endl;

	//Destroy_SList(&list);

	//ARRAYV1<int> arr_i;
	//Create_Array(&arr_i, 5);
	//int * pi;
	//for(int i = 0; i < 10; i++)
	//{
	//	if(Append_Array(&arr_i, &pi))
	//		*pi = i;
	//}
	//for(int i = 0; i < (int)arr_i.length; i++)
	//	std::cout << arr_i.elems[i] << ", ";
	//std::cout << std::endl;
	//std::cout << arr_i.length << ", " << arr_i.size << std::endl;
	//Clear_Array(&arr_i);
	//std::cout << arr_i.length << ", " << arr_i.size << std::endl;
	//Destroy_Array(&arr_i);

	//int bpp = 16;
	//if(!Init_T3dlib1(bpp)
	//	|| !Init_T3dlib4(bpp)
	//	|| !Init_T3dlib5(bpp)
	//	|| !Init_T3dlib6(bpp))
	//{
	//	cout << "Init t3dlibs failed !!!" << endl;
	//	exit(1);
	//}

	//msModel model;
	//char buffer[MAX_BUFFER_SIZE];
	//int line;
	//char file[MAX_BUFFER_SIZE];
	//INIT_ZERO(model);
	//if(!Create_MsModel_From_File(&model, "MilkShape 3D ASCII.txt"))
	//{
	//	Get_Last_Error(buffer, file, &line);
	//	std::cout << buffer << " " << line << endl;
	//	Destroy_MsModel(&model);
	//	exit(1);
	//}

	//MATERIALV1 mat;
	//INIT_ZERO(mat);
	//if(!Create_Material_From_MsModel32(&mat, &model, "Material01"))
	//{
	//	Get_Last_Error(buffer, file, &line);
	//	std::cout << buffer << " " << line << endl;
	//	Destroy_Material(&mat);
	//	Destroy_MsModel(&model);
	//	exit(1);
	//}
	//Destroy_Material(&mat);

	//OBJECT4DV1 obj;
	//INIT_ZERO(obj);
	//if(!Create_Object4D_From_MsModel(&obj, &model, "Box01"))
	//{
	//	Get_Last_Error(buffer, file, &line);
	//	std::cout << buffer << " " << line << endl;
	//	Destroy_Object4D(&obj);
	//	Destroy_MsModel(&model);
	//	exit(1);
	//}
	//Destroy_Object4D(&obj);
	//Destroy_MsModel(&model);

	//int i;
	//for(i = 0; i < 500; i += 10)
	//{
	//	REAL a, b;
	//	a = Fast_Sin((REAL)i);
	//	b = sin(DEG_TO_RAD(i));
	//	printf("fast sin: %3.6f, sin: %3.6f, error: %3.6f\n",
	//		a, b, abs(a - b));
	//}

	//for(i = 0; i < 500; i += 10)
	//{
	//	REAL a, b;
	//	a = Fast_Cos((REAL)i);
	//	b = cos(DEG_TO_RAD(i));
	//	printf("fast cos: %3.6f, cos: %3.6f, error: %3.6f\n",
	//		a, b, abs(a - b));
	//}

	//// performance test:
	//// note: must be run at release mode ***
	//int limit = 999999;
	//REAL a = 0;
	//DWORD begin = timeGetTime();
	//for(i = 0; i < limit; i++)
	//{
	//	a += Fast_Sin(50);
	//}
	//DWORD end = timeGetTime();
	//DWORD error_f = end - begin;

	//begin = timeGetTime();
	//for(i = 0; i < limit; i++)
	//{
	//	// the const value's caculating will not be done at runtime!
	//	a += sin(DEG_TO_RAD(50));
	//}
	//end = timeGetTime();
	//DWORD error = end - begin;

	//cout << "fast time: " << error_f << endl;
	//cout << "normal time: " << error << endl;

	//cout << a << endl;

	// ====================================================================================
	// 2007-08-11
	// ====================================================================================

	msModel model;
	INIT_ZERO(model);
	SKELETON4DV1 ske;
	INIT_ZERO(ske);

	if(!Create_MsModel_From_File(&model, "MilkShape 3D ASCII.txt"))
		goto on_error;

	if(!Create_Skeleton4D_From_MsModel(&ske, &model, "aaa"))
		goto on_error;

	Skeleton4D_Print(&ske);

	Animate_Skeleton4D_By_Time(&ske, 25);

	printf("\n");

	Print_Bone_Position(&ske.bone_list, &ske.bone_list_t, ske.root, 0);

	printf("\n");

	Print_Bone_Rotation(&ske.bone_list, &ske.bone_list_t, ske.root, 0);

	Destroy_Skeleton4D(&ske);
	Destroy_MsModel(&model);

	_CrtDumpMemoryLeaks();
	return 0;

on_error:
	char message[MAX_BUFFER_SIZE];
	Get_Last_Error(message);
	printf("%s \n", message);
	return 1;
}
