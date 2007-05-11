/**
 * File: T3DLIB2/t3dlib4.h
 */

#ifndef __T3DLIB4_H__
#define __T3DLIB4_H__

#include "t3dcommons.h"

#define PI					(3.1415926535897932384626433832795f)
#define EPSILON_E3			(1.0e-3)
#define EPSILON_E4			(1.0e-4)
#define EPSILON_E5			(1.0e-5)
#define EPSILON_E6			(1.0e-6)

#define IS_ZERO_FLOAT(f)	(abs((REAL)(f)) < EPSILON_E6)
#define DEG_TO_RAD(deg)		(((deg) / 180.0f) * PI)
#define RAD_TO_DEG(rad)		(((rad) / PI) * 180.0f)

#pragma warning(disable : 4201)
typedef struct T3DLIB_API VECTOR2D_TYP
{
	union
	{
		REAL M[2];

		struct
		{
			REAL x, y;
		};
	};

} VECTOR2D, POINT2D, * VECTOR2D_PTR, * POINT2D_PTR;

typedef struct T3DLIB_API VECTOR3D_TYP
{
	union
	{
		REAL M[3];

		struct
		{
			REAL x, y, z;
		};

		struct
		{
			VECTOR2D _2D;
		};
	};

} VECTOR3D, POINT3D, * VECTOR3D_PTR, * POINT3D_PTR;

typedef struct T3DLIB_API VECTOR4D_TYP
{
	union
	{
		REAL M[4];

		struct
		{
			REAL x, y, z, w;
		};

		struct
		{
			VECTOR2D _2D;
		};

		struct
		{
			VECTOR3D _3D;
		};
	};

} VECTOR4D, POINT4D, * VECTOR4D_PTR, * POINT4D_PTR;

typedef struct T3DLIB_API VECTOR2DI_TYP
{
	union
	{
		int M[2];

		struct
		{
			int x, y;
		};
	};

} VECTOR2DI, POINT2DI, * VECTOR2DI_PTR, * POINT2DI_PTR;

typedef struct T3DLIB_API VECTOR3DI_TYP
{
	union
	{
		int M[3];

		struct
		{
			int x, y, z;
		};

		struct
		{
			VECTOR2DI _2D;
		};
	};

} VECTOR3DI, POINT3DI, * VECTOR3DI_PTR, * POINT3DI_PTR;

typedef struct T3DLIB_API VECTOR4DI_TYP
{
	union
	{
		int M[4];

		struct
		{
			int x, y, z, w;
		};

		struct
		{
			VECTOR2DI _2D;
		};

		struct
		{
			VECTOR3DI _3D;
		};
	};

} VECTOR4DI, POINT4DI, * VECTOR4DI_PTR, * POINT4DI_PTR;

typedef struct T3DLIB_API MATRIX2X2_TYP
{
	union
	{
		REAL M[2][2];

		struct
		{
			REAL m00, m01;
			REAL m10, m11;
		};
	};

	static const MATRIX2X2_TYP IDENTITY;

} MATRIX2X2, * MATRIX2X2_PTR;

typedef struct T3DLIB_API MATRIX3X2_TYP
{
	union
	{
		REAL M[3][2];

		struct
		{
			REAL m00, m01;
			REAL m10, m11;
			REAL m20, m21;
		};

		struct
		{
			MATRIX2X2 _2X2;
		};
	};

	static const MATRIX3X2_TYP IDENTITY;

} MATRIX3X2, * MATRIX3X2_PTR;

//typedef struct T3DLIB_API MATRIX2X3_TYP
//{
//	union
//	{
//		REAL M[2][3];

//		struct
//		{
//			REAL m00, m01, m02;
//			REAL m10, m11, m12;
//		};
//	};

//	static const MATRIX2X3_TYP IDENTITY;

//} MATRIX2X3, * MATRIX2X3_PTR;

typedef struct T3DLIB_API MATRIX3X3_TYP
{
	union
	{
		REAL M[3][3];

		struct
		{
			REAL m00, m01, m02;
			REAL m10, m11, m12;
			REAL m20, m21, m22;
		};

		//struct
		//{
		//	MATRIX2X3 _2X3;
		//};
	};

	static const MATRIX3X3_TYP IDENTITY;

} MATRIX3X3, * MATRIX3X3_PTR;

typedef struct T3DLIB_API MATRIX4X3_TYP
{
	union
	{
		REAL M[4][3];

		struct
		{
			REAL m00, m01, m02;
			REAL m10, m11, m12;
			REAL m20, m21, m22;
			REAL m30, m31, m32;
		};

		//struct
		//{
		//	MATRIX2X3 _2X3;
		//};

		struct
		{
			MATRIX3X3 _3X3;
		};
	};

	static const MATRIX4X3_TYP IDENTITY;

} MATRIX4X3, * MATRIX4X3_PTR;

//typedef struct T3DLIB_API MATRIX2X4_TYP
//{
//	union
//	{
//		REAL M[2][4];

//		struct
//		{
//			REAL m00, m01, m02, m03;
//			REAL m10, m11, m12, m13;
//		};
//	};

//	static const MATRIX2X4_TYP IDENTITY;

//} MATRIX2X4, * MATRIX2X4_PTR;

//typedef struct T3DLIB_API MATRIX3X4_TYP
//{
//	union
//	{
//		REAL M[3][4];

//		struct
//		{
//			REAL m00, m01, m02, m03;
//			REAL m10, m11, m12, m13;
//			REAL m20, m21, m22, m23;
//		};

//		struct
//		{
//			MATRIX2X4 _2X4;
//		};
//	};

//	static const MATRIX3X4_TYP IDENTITY;

//} MATRIX3X4, * MATRIX3X4_PTR;

typedef struct T3DLIB_API MATRIX4X4_TYP
{
	union
	{
		REAL M[4][4];

		struct
		{
			REAL m00, m01, m02, m03;
			REAL m10, m11, m12, m13;
			REAL m20, m21, m22, m23;
			REAL m30, m31, m32, m33;
		};

		//struct
		//{
		//	MATRIX2X4 _2X4;
		//};

		//struct
		//{
		//	MATRIX3X4 _3X4;
		//};
	};

	static const MATRIX4X4_TYP IDENTITY;

} MATRIX4X4, * MATRIX4X4_PTR;
#pragma warning(default : 4201)

inline VECTOR2D * VECTOR2D_Zero(VECTOR2D * pv0)
{
	memset(pv0, 0, sizeof(*pv0));
	return pv0;
}

inline VECTOR2D * VECTOR2D_Copy(VECTOR2D * pvres, const VECTOR2D * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	return pvres;
}

inline VECTOR2D * VECTOR2D_InitXY(VECTOR2D * pvres, const REAL x, const REAL y)
{
	pvres->x = x;
	pvres->y = y;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Add(VECTOR2D * pvres, const VECTOR2D * pv0, const VECTOR2D * pv1)
{
	pvres->x = pv0->x + pv1->x;
	pvres->y = pv0->y + pv1->y;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Add(VECTOR2D * pv0, const VECTOR2D * pv1)
{
	pv0->x += pv1->x;
	pv0->y += pv1->y;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Add(VECTOR2D * pvres, const VECTOR2D * pv0, const REAL scale)
{
	pvres->x = pv0->x + scale;
	pvres->y = pv0->y + scale;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Add(VECTOR2D * pv0, const REAL scale)
{
	pv0->x += scale;
	pv0->y += scale;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Sub(VECTOR2D * pvres, const VECTOR2D * pv0, const VECTOR2D * pv1)
{
	pvres->x = pv0->x - pv1->x;
	pvres->y = pv0->y - pv1->y;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Sub(VECTOR2D * pv0, const VECTOR2D * pv1)
{
	pv0->x -= pv1->x;
	pv0->y -= pv1->y;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Sub(VECTOR2D * pvres, const VECTOR2D * pv0, const REAL scale)
{
	pvres->x = pv0->x - scale;
	pvres->y = pv0->y - scale;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Sub(VECTOR2D * pv0, const REAL scale)
{
	pv0->x -= scale;
	pv0->y -= scale;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Mul(VECTOR2D * pvres, const VECTOR2D * pv0, const VECTOR2D * pv1)
{
	pvres->x = pv0->x * pv1->x;
	pvres->y = pv0->y * pv1->y;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Mul(VECTOR2D * pv0, const VECTOR2D * pv1)
{
	pv0->x *= pv1->x;
	pv0->y *= pv1->y;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Mul(VECTOR2D * pvres, const VECTOR2D * pv0, const REAL scale)
{
	pvres->x = pv0->x * scale;
	pvres->y = pv0->y * scale;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Mul(VECTOR2D * pv0, const REAL scale)
{
	pv0->x *= scale;
	pv0->y *= scale;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Div(VECTOR2D * pvres, const VECTOR2D * pv0, const VECTOR2D * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));

	pvres->x = pv0->x / pv1->x;
	pvres->y = pv0->y / pv1->y;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Div(VECTOR2D * pv0, const VECTOR2D * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));

	pv0->x /= pv1->x;
	pv0->y /= pv1->y;
	return pv0;
}

inline VECTOR2D * VECTOR2D_Div(VECTOR2D * pvres, const VECTOR2D * pv0, const REAL scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	REAL scale_inv = 1.0f / scale;
	pvres->x = pv0->x * scale_inv;
	pvres->y = pv0->y * scale_inv;
	return pvres;
}

inline VECTOR2D * VECTOR2D_Div(VECTOR2D * pv0, const REAL scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	REAL scale_inv = 1.0f / scale;
	pv0->x *= scale_inv;
	pv0->y *= scale_inv;
	return pv0;
}

inline REAL VECTOR2D_Dot(const VECTOR2D * pv0, const VECTOR2D * pv1)
{
	return pv0->x * pv1->x + pv0->y * pv1->y;
}

inline REAL VECTOR2D_Length(const VECTOR2D * pv0)
{
	return sqrt(pv0->x * pv0->x + pv0->y * pv0->y);
}

inline VECTOR2D * VECTOR2D_Normalize(VECTOR2D * pres, const VECTOR2D * pv0)
{
	assert(!IS_ZERO_FLOAT(VECTOR2D_Length(pv0)));

	REAL len_inv = 1.0f / sqrt(pv0->x * pv0->x + pv0->y * pv0->y);
	pres->x = pv0->x * len_inv;
	pres->y = pv0->y * len_inv;
	return pres;
}

inline VECTOR2D * VECTOR2D_Normalize(VECTOR2D * pv0)
{
	assert(!IS_ZERO_FLOAT(VECTOR2D_Length(pv0)));

	REAL len_inv = 1.0f / sqrt(pv0->x * pv0->x + pv0->y * pv0->y);
	pv0->x *= len_inv;
	pv0->y *= len_inv;
	return pv0;
}

inline REAL VECTOR2D_CosTheta(const VECTOR2D * pv0, const VECTOR2D * pv1)
{
	assert(!IS_ZERO_FLOAT(VECTOR2D_Length(pv0)));
	assert(!IS_ZERO_FLOAT(VECTOR2D_Length(pv1)));

	return	(pv0->x * pv1->x + pv0->y * pv1->y) /
				(sqrt(pv0->x * pv0->x + pv0->y * pv0->y) *
					sqrt(pv1->x * pv1->x + pv1->y * pv1->y));
}

inline void VECTOR2D_Print(const VECTOR2D * pv0)
{
	printf("VECTOR2D {%f : %f}", pv0->x, pv0->y);
}

inline VECTOR3D * VECTOR3D_Zero(VECTOR3D * pv0)
{
	memset(pv0, 0, sizeof(*pv0));
	return pv0;
}

inline VECTOR3D * VECTOR3D_Copy(VECTOR3D * pvres, const VECTOR3D * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	return pvres;
}

inline VECTOR3D * VECTOR3D_Init(VECTOR3D * pvres, const VECTOR2D * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	pvres->z = 1.0f;
	return pvres;
}

inline VECTOR3D * VECTOR3D_InitXY(VECTOR3D * pvres, const REAL x, const REAL y)
{
	pvres->x = x;
	pvres->y = y;
	pvres->z = 1.0f;
	return pvres;
}

inline VECTOR3D * VECTOR3D_InitXYZ(VECTOR3D * pvres, const REAL x, const REAL y, const REAL z)
{
	pvres->x = x;
	pvres->y = y;
	pvres->z = z;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Add(VECTOR3D * pvres, const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pvres->x = pv0->x + pv1->x;
	pvres->y = pv0->y + pv1->y;
	pvres->z = pv0->z + pv1->z;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Add(VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pv0->x += pv1->x;
	pv0->y += pv1->y;
	pv0->z += pv1->z;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Add(VECTOR3D * pvres, const VECTOR3D * pv0, const REAL scale)
{
	pvres->x = pv0->x + scale;
	pvres->y = pv0->y + scale;
	pvres->z = pv0->z + scale;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Add(VECTOR3D * pv0, const REAL scale)
{
	pv0->x += scale;
	pv0->y += scale;
	pv0->z += scale;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Sub(VECTOR3D * pvres, const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pvres->x = pv0->x - pv1->x;
	pvres->y = pv0->y - pv1->y;
	pvres->z = pv0->z - pv1->z;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Sub(VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pv0->x -= pv1->x;
	pv0->y -= pv1->y;
	pv0->z -= pv1->z;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Sub(VECTOR3D * pvres, const VECTOR3D * pv0, const REAL scale)
{
	pvres->x = pv0->x - scale;
	pvres->y = pv0->y - scale;
	pvres->z = pv0->z - scale;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Sub(VECTOR3D * pv0, const REAL scale)
{
	pv0->x -= scale;
	pv0->y -= scale;
	pv0->z -= scale;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Mul(VECTOR3D * pvres, const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pvres->x = pv0->x * pv1->x;
	pvres->y = pv0->y * pv1->y;
	pvres->z = pv0->z * pv1->z;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Mul(VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pv0->x *= pv1->x;
	pv0->y *= pv1->y;
	pv0->z *= pv1->z;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Mul(VECTOR3D * pvres, const VECTOR3D * pv0, const REAL scale)
{
	pvres->x = pv0->x * scale;
	pvres->y = pv0->y * scale;
	pvres->z = pv0->z * scale;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Mul(VECTOR3D * pv0, const REAL scale)
{
	pv0->x *= scale;
	pv0->y *= scale;
	pv0->z *= scale;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Div(VECTOR3D * pvres, const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));
	assert(!IS_ZERO_FLOAT(pv1->z));

	pvres->x = pv0->x / pv1->x;
	pvres->y = pv0->y / pv1->y;
	pvres->z = pv0->z / pv1->z;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Div(VECTOR3D * pv0, const VECTOR3D * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));
	assert(!IS_ZERO_FLOAT(pv1->z));

	pv0->x /= pv1->x;
	pv0->y /= pv1->y;
	pv0->z /= pv1->z;
	return pv0;
}

inline VECTOR3D * VECTOR3D_Div(VECTOR3D * pvres, const VECTOR3D * pv0, const REAL scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	REAL scale_inv = 1.0f / scale;
	pvres->x = pv0->x * scale_inv;
	pvres->y = pv0->y * scale_inv;
	pvres->z = pv0->z * scale_inv;
	return pvres;
}

inline VECTOR3D * VECTOR3D_Div(VECTOR3D * pv0, const REAL scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	REAL scale_inv = 1.0f / scale;
	pv0->x *= scale_inv;
	pv0->y *= scale_inv;
	pv0->z *= scale_inv;
	return pv0;
}

inline REAL VECTOR3D_Dot(const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	return pv0->x * pv1->x + pv0->y * pv1->y + pv0->z * pv1->z;
}

inline VECTOR3D * VECTOR3D_Cross(VECTOR3D * pvres, const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	pvres->x = pv0->y * pv1->z - pv0->z * pv1->y;
	pvres->y = pv0->z * pv1->x - pv0->x * pv1->z;
	pvres->z = pv0->x * pv1->y - pv0->y * pv1->x;
	return pvres;
}

inline REAL VECTOR3D_Length(const VECTOR3D * pv0)
{
	return sqrt(pv0->x * pv0->x + pv0->y * pv0->y + pv0->z * pv0->z);
}

inline VECTOR3D * VECTOR3D_Normalize(VECTOR3D * pres, const VECTOR3D * pv0)
{
	assert(!IS_ZERO_FLOAT(VECTOR3D_Length(pv0)));

	REAL len_inv = 1.0f / sqrt(pv0->x * pv0->x + pv0->y * pv0->y + pv0->z * pv0->z);
	pres->x = pv0->x * len_inv;
	pres->y = pv0->y * len_inv;
	pres->z = pv0->z * len_inv;
	return pres;
}

inline VECTOR3D * VECTOR3D_Normalize(VECTOR3D * pv0)
{
	assert(!IS_ZERO_FLOAT(VECTOR3D_Length(pv0)));

	REAL len_inv = 1.0f / sqrt(pv0->x * pv0->x + pv0->y * pv0->y + pv0->z * pv0->z);
	pv0->x *= len_inv;
	pv0->y *= len_inv;
	pv0->z *= len_inv;
	return pv0;
}

inline REAL VECTOR3D_CosTheta(const VECTOR3D * pv0, const VECTOR3D * pv1)
{
	assert(!IS_ZERO_FLOAT(VECTOR3D_Length(pv0)));
	assert(!IS_ZERO_FLOAT(VECTOR3D_Length(pv1)));

	return	(pv0->x * pv1->x + pv0->y * pv1->y + pv0->z * pv1->z) /
				(sqrt(pv0->x * pv0->x + pv0->y * pv0->y + pv0->z * pv0->z) *
					sqrt(pv1->x * pv1->x + pv1->y * pv1->y + pv1->z * pv1->z));
}

inline void VECTOR3D_Print(const VECTOR3D * pv0)
{
	printf("VECTOR3D {%f : %f : %f}", pv0->x, pv0->y, pv0->z);
}

inline VECTOR4D * VECTOR4D_Zero(VECTOR4D * pv0)
{
	memset(pv0, 0, sizeof(*pv0));
	return pv0;
}

inline VECTOR4D * VECTOR4D_Copy(VECTOR4D * pvres, const VECTOR4D * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	return pvres;
}

inline VECTOR4D * VECTOR4D_Init(VECTOR4D * pvres, const VECTOR3D * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	pvres->w = 1.0f;
	return pvres;
}

inline VECTOR4D * VECTOR4D_InitXYZ(VECTOR4D * pvres, const REAL x, const REAL y, const REAL z)
{
	pvres->x = x;
	pvres->y = y;
	pvres->z = z;
	pvres->w = 1.0f;
	return pvres;
}

inline VECTOR4D * VECTOR4D_InitXYZW(VECTOR4D * pvres, const REAL x, const REAL y, const REAL z, const REAL w)
{
	pvres->x = x;
	pvres->y = y;
	pvres->z = z;
	pvres->w = w;
	return pvres;
}

inline void VECTOR4D_Print(const VECTOR4D * pv0)
{
	printf("VECTOR4D {%f : %f : %f : %f}", pv0->x, pv0->y, pv0->z, pv0->w);
}

inline VECTOR2DI * VECTOR2DI_Zero(VECTOR2DI * pv0)
{
	memset(pv0, 0, sizeof(*pv0));
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Copy(VECTOR2DI * pvres, const VECTOR2DI * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_InitXY(VECTOR2DI * pvres, const int x, const int y)
{
	pvres->x = x;
	pvres->y = y;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Add(VECTOR2DI * pvres, const VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	pvres->x = pv0->x + pv1->x;
	pvres->y = pv0->y + pv1->y;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Add(VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	pv0->x += pv1->x;
	pv0->y += pv1->y;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Add(VECTOR2DI * pvres, const VECTOR2DI * pv0, const int scale)
{
	pvres->x = pv0->x + scale;
	pvres->y = pv0->y + scale;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Add(VECTOR2DI * pv0, const int scale)
{
	pv0->x += scale;
	pv0->y += scale;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Sub(VECTOR2DI * pvres, const VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	pvres->x = pv0->x - pv1->x;
	pvres->y = pv0->y - pv1->y;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Sub(VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	pv0->x -= pv1->x;
	pv0->y -= pv1->y;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Sub(VECTOR2DI * pvres, const VECTOR2DI * pv0, const int scale)
{
	pvres->x = pv0->x - scale;
	pvres->y = pv0->y - scale;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Sub(VECTOR2DI * pv0, const int scale)
{
	pv0->x -= scale;
	pv0->y -= scale;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Mul(VECTOR2DI * pvres, const VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	pvres->x = pv0->x * pv1->x;
	pvres->y = pv0->y * pv1->y;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Mul(VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	pv0->x *= pv1->x;
	pv0->y *= pv1->y;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Mul(VECTOR2DI * pvres, const VECTOR2DI * pv0, const int scale)
{
	pvres->x = pv0->x * scale;
	pvres->y = pv0->y * scale;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Mul(VECTOR2DI * pv0, const int scale)
{
	pv0->x *= scale;
	pv0->y *= scale;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Div(VECTOR2DI * pvres, const VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));

	pvres->x = pv0->x / pv1->x;
	pvres->y = pv0->y / pv1->y;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Div(VECTOR2DI * pv0, const VECTOR2DI * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));

	pv0->x /= pv1->x;
	pv0->y /= pv1->y;
	return pv0;
}

inline VECTOR2DI * VECTOR2DI_Div(VECTOR2DI * pvres, const VECTOR2DI * pv0, const int scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	pvres->x = pv0->x / scale;
	pvres->y = pv0->y / scale;
	return pvres;
}

inline VECTOR2DI * VECTOR2DI_Div(VECTOR2DI * pv0, const int scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	pv0->x /= scale;
	pv0->y /= scale;
	return pv0;
}

inline void VECTOR2DI_Print(const VECTOR2DI * pv0)
{
	printf("VECTOR2DI {%d : %d}", pv0->x, pv0->y);
}

inline VECTOR3DI * VECTOR3DI_Zero(VECTOR3DI * pv0)
{
	memset(pv0, 0, sizeof(*pv0));
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Copy(VECTOR3DI * pvres, const VECTOR3DI * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_InitXYZ(VECTOR3DI * pvres, const int x, const int y, const int z)
{
	pvres->x = x;
	pvres->y = y;
	pvres->z = z;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Add(VECTOR3DI * pvres, const VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	pvres->x = pv0->x + pv1->x;
	pvres->y = pv0->y + pv1->y;
	pvres->z = pv0->z + pv1->z;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Add(VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	pv0->x += pv1->x;
	pv0->y += pv1->y;
	pv0->z += pv1->z;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Add(VECTOR3DI * pvres, const VECTOR3DI * pv0, const int scale)
{
	pvres->x = pv0->x + scale;
	pvres->y = pv0->y + scale;
	pvres->z = pv0->z + scale;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Add(VECTOR3DI * pv0, const int scale)
{
	pv0->x += scale;
	pv0->y += scale;
	pv0->z += scale;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Sub(VECTOR3DI * pvres, const VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	pvres->x = pv0->x - pv1->x;
	pvres->y = pv0->y - pv1->y;
	pvres->z = pv0->z - pv1->z;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Sub(VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	pv0->x -= pv1->x;
	pv0->y -= pv1->y;
	pv0->z -= pv1->z;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Sub(VECTOR3DI * pvres, const VECTOR3DI * pv0, const int scale)
{
	pvres->x = pv0->x - scale;
	pvres->y = pv0->y - scale;
	pvres->z = pv0->z - scale;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Sub(VECTOR3DI * pv0, const int scale)
{
	pv0->x -= scale;
	pv0->y -= scale;
	pv0->z -= scale;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Mul(VECTOR3DI * pvres, const VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	pvres->x = pv0->x * pv1->x;
	pvres->y = pv0->y * pv1->y;
	pvres->z = pv0->z * pv1->z;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Mul(VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	pv0->x *= pv1->x;
	pv0->y *= pv1->y;
	pv0->z *= pv1->z;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Mul(VECTOR3DI * pvres, const VECTOR3DI * pv0, const int scale)
{
	pvres->x = pv0->x * scale;
	pvres->y = pv0->y * scale;
	pvres->z = pv0->z * scale;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Mul(VECTOR3DI * pv0, const int scale)
{
	pv0->x *= scale;
	pv0->y *= scale;
	pv0->z *= scale;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Div(VECTOR3DI * pvres, const VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));
	assert(!IS_ZERO_FLOAT(pv1->z));

	pvres->x = pv0->x / pv1->x;
	pvres->y = pv0->y / pv1->y;
	pvres->z = pv0->z / pv1->z;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Div(VECTOR3DI * pv0, const VECTOR3DI * pv1)
{
	assert(!IS_ZERO_FLOAT(pv1->x));
	assert(!IS_ZERO_FLOAT(pv1->y));
	assert(!IS_ZERO_FLOAT(pv1->z));

	pv0->x /= pv1->x;
	pv0->y /= pv1->y;
	pv0->z /= pv1->z;
	return pv0;
}

inline VECTOR3DI * VECTOR3DI_Div(VECTOR3DI * pvres, const VECTOR3DI * pv0, const int scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	pvres->x = pv0->x / scale;
	pvres->y = pv0->y / scale;
	pvres->z = pv0->z / scale;
	return pvres;
}

inline VECTOR3DI * VECTOR3DI_Div(VECTOR3DI * pv0, const int scale)
{
	assert(!IS_ZERO_FLOAT(scale));

	pv0->x /= scale;
	pv0->y /= scale;
	pv0->z /= scale;
	return pv0;
}

inline void VECTOR3DI_Print(const VECTOR3DI * pv0)
{
	printf("VECTOR3DI {%d : %d : %d}", pv0->x, pv0->y, pv0->z);
}

inline VECTOR4DI * VECTOR4DI_Zero(VECTOR4DI * pv0)
{
	memset(pv0, 0, sizeof(*pv0));
	return pv0;
}

inline VECTOR4DI * VECTOR4DI_Copy(VECTOR4DI * pvres, const VECTOR4DI * pv0)
{
	memcpy(pvres, pv0, sizeof(*pv0));
	return pvres;
}

inline VECTOR4DI * VECTOR4DI_InitXYZW(VECTOR4DI * pvres, const int x, const int y, const int z, const int w)
{
	pvres->x = x;
	pvres->y = y;
	pvres->z = z;
	pvres->w = w;
	return pvres;
}

inline void VECTOR4DI_Print(const VECTOR4DI * pv0)
{
	printf("VECTOR4DI {%d : %d : %d : %d}", pv0->x, pv0->y, pv0->z, pv0->w);
}

inline MATRIX2X2 * MATRIX2X2_Zero(MATRIX2X2 * pmres)
{
	memset(pmres, 0, sizeof(*pmres));
	return pmres;
}

inline MATRIX2X2 * MATRIX2X2_Copy(MATRIX2X2 * pmres, const MATRIX2X2 * pm0)
{
	memcpy(pmres, pm0, sizeof(*pm0));
	return pmres;
}

inline MATRIX2X2 * MATRIX2X2_Init2X2(MATRIX2X2 * pmres, const REAL f00, const REAL f01,
														const REAL f10, const REAL f11)
{
	pmres->m00 = f00;
	pmres->m01 = f01;
	pmres->m10 = f10;
	pmres->m11 = f11;
	return pmres;
}

inline void MATRIX2X2_Print(const MATRIX2X2 * pm0)
{
	printf(	"MATRIX2X2 { %f, %f,\n"
			"            %f, %f, }", pm0->m00, pm0->m01, pm0->m10, pm0->m11);
}

inline MATRIX3X2 * MATRIX3X2_Zero(MATRIX3X2 * pmres)
{
	memset(pmres, 0, sizeof(*pmres));
	return pmres;
}

inline MATRIX3X2 * MATRIX3X2_Copy(MATRIX3X2 * pmres, const MATRIX3X2 * pm0)
{
	memcpy(pmres, pm0, sizeof(*pm0));
	return pmres;
}

inline MATRIX3X2 * MATRIX3X2_Init2X2(MATRIX3X2 * pmres, const MATRIX2X2 * pm0)
{
	memcpy(pmres, pm0, sizeof(*pm0));
	pmres->m20 = 0.0f;
	pmres->m21 = 0.0f;
	return pmres;
}

inline MATRIX3X2 * MATRIX3X2_Init2X2(MATRIX3X2 * pmres, const REAL f00, const REAL f01,
														const REAL f10, const REAL f11)
{
	pmres->m00 = f00;
	pmres->m01 = f01;
	pmres->m10 = f10;
	pmres->m11 = f11;
	pmres->m20 = 0.0f;
	pmres->m21 = 0.0f;
	return pmres;
}

inline MATRIX3X2 * MATRIX3X2_Init3X2(MATRIX3X2 * pmres, const REAL f00, const REAL f01,
														const REAL f10, const REAL f11,
														const REAL f20, const REAL f21)
{
	pmres->m00 = f00;
	pmres->m01 = f01;
	pmres->m10 = f10;
	pmres->m11 = f11;
	pmres->m20 = f20;
	pmres->m21 = f21;
	return pmres;
}

inline void MATRIX3X2_Print(const MATRIX3X2 * pm0)
{
	printf(	"MATRIX3X2 { %f, %f,\n"
			"            %f, %f,\n"
			"            %f, %f, }", pm0->m00, pm0->m01, pm0->m10, pm0->m11, pm0->m20, pm0->m21);
}

inline MATRIX3X3 * MATRIX3X3_Zero(MATRIX3X3 * pmres)
{
	memset(pmres, 0, sizeof(*pmres));
	return pmres;
}

inline MATRIX3X3 * MATRIX3X3_Copy(MATRIX3X3 * pmres, const MATRIX3X3 * pm0)
{
	memcpy(pmres, pm0, sizeof(*pm0));
	return pmres;
}

inline MATRIX3X3 * MATRIX3X3_Init2X2(MATRIX3X3 * pmres, const MATRIX2X2 * pm0)
{
	pmres->m00 = pm0->m00;	pmres->m01 = pm0->m01;	pmres->m02 = 0.0f;
	pmres->m10 = pm0->m10;	pmres->m11 = pm0->m11;	pmres->m12 = 0.0f;
	pmres->m20 = 0.0f;		pmres->m21 = 0.0f;		pmres->m22 = 1.0f;
	return pmres;
}

inline MATRIX3X3 * MATRIX3X3_Init2X2(MATRIX3X3 * pmres, const REAL f00, const REAL f01,
														const REAL f10, const REAL f11)
{
	pmres->m00 = f00;		pmres->m01 = f01;		pmres->m02 = 0.0f;
	pmres->m10 = f10;		pmres->m11 = f11;		pmres->m12 = 0.0f;
	pmres->m20 = 0.0f;		pmres->m21 = 0.0f;		pmres->m22 = 1.0f;
	return pmres;
}

inline MATRIX3X3 * MATRIX3X3_Init3X3(MATRIX3X3 * pmres, const REAL f00, const REAL f01, const REAL f02,
														const REAL f10, const REAL f11, const REAL f12,
														const REAL f20, const REAL f21, const REAL f22)
{
	pmres->m00 = f00;		pmres->m01 = f01;		pmres->m02 = f02;
	pmres->m10 = f10;		pmres->m11 = f11;		pmres->m12 = f12;
	pmres->m20 = f20;		pmres->m21 = f21;		pmres->m22 = f22;
	return pmres;
}

inline void MATRIX3X3_Print(const MATRIX3X3 * pm0)
{
	printf(	"MATRIX3X3 { %f, %f, %f,\n"
			"            %f, %f, %f,\n"
			"            %f, %f, %f, }",	pm0->m00, pm0->m01, pm0->m02,
											pm0->m10, pm0->m11, pm0->m12,
											pm0->m20, pm0->m21, pm0->m22);
}

inline MATRIX4X3 * MATRIX4X3_Zero(MATRIX4X3 * pmres)
{
	memset(pmres, 0, sizeof(*pmres));
	return pmres;
}

inline MATRIX4X3 * MATRIX4X3_Copy(MATRIX4X3 * pmres, const MATRIX4X3 * pm0)
{
	memcpy(pmres, pm0, sizeof(*pm0));
	return pmres;
}

inline MATRIX4X3 * MATRIX4X3_Init3X3(MATRIX4X3 * pmres, const MATRIX3X3 * pm0)
{
	pmres->m00 = pm0->m00;	pmres->m01 = pm0->m01;	pmres->m02 = pm0->m02;
	pmres->m10 = pm0->m10;	pmres->m11 = pm0->m11;	pmres->m12 = pm0->m12;
	pmres->m20 = pm0->m20;	pmres->m21 = pm0->m21;	pmres->m22 = pm0->m22;
	pmres->m30 = 0.0f;		pmres->m31 = 0.0f;		pmres->m32 = 0.0f;
	return pmres;
}

inline MATRIX4X3 * MATRIX4X3_Init3X3(MATRIX4X3 * pmres, const REAL f00, const REAL f01, const REAL f02,
														const REAL f10, const REAL f11, const REAL f12,
														const REAL f20, const REAL f21, const REAL f22)
{
	pmres->m00 = f00;		pmres->m01 = f01;		pmres->m02 = f02;
	pmres->m10 = f10;		pmres->m11 = f11;		pmres->m12 = f12;
	pmres->m20 = f20;		pmres->m21 = f21;		pmres->m22 = f22;
	pmres->m30 = 0.0f;		pmres->m31 = 0.0f;		pmres->m32 = 0.0f;
	return pmres;
}

inline MATRIX4X3 * MATRIX4X3_Init4X3(MATRIX4X3 * pmres, const REAL f00, const REAL f01, const REAL f02,
														const REAL f10, const REAL f11, const REAL f12,
														const REAL f20, const REAL f21, const REAL f22,
														const REAL f30, const REAL f31, const REAL f32)
{
	pmres->m00 = f00;		pmres->m01 = f01;		pmres->m02 = f02;
	pmres->m10 = f10;		pmres->m11 = f11;		pmres->m12 = f12;
	pmres->m20 = f20;		pmres->m21 = f21;		pmres->m22 = f22;
	pmres->m30 = f30;		pmres->m31 = f31;		pmres->m32 = f32;
	return pmres;
}

inline void MATRIX4X3_Print(const MATRIX4X3 * pm0)
{
	printf(	"MATRIX4X3 { %f, %f, %f,\n"
			"            %f, %f, %f,\n"
			"            %f, %f, %f,\n"
			"            %f, %f, %f, }",	pm0->m00, pm0->m01, pm0->m02,
											pm0->m10, pm0->m11, pm0->m12,
											pm0->m20, pm0->m21, pm0->m22,
											pm0->m30, pm0->m31, pm0->m32);
}

inline MATRIX4X4 * MATRIX4X4_Zero(MATRIX4X4 * pmres)
{
	memset(pmres, 0, sizeof(*pmres));
	return pmres;
}

inline MATRIX4X4 * MATRIX4X4_Copy(MATRIX4X4 * pmres, const MATRIX4X4 * pm0)
{
	memcpy(pmres, pm0, sizeof(*pm0));
	return pmres;
}

inline MATRIX4X4 * MATRIX4X4_Init3X3(MATRIX4X4 * pmres, const MATRIX3X3 * pm0)
{
	pmres->m00 = pm0->m00;	pmres->m01 = pm0->m01;	pmres->m02 = pm0->m02;	pmres->m03 = 0.0f;
	pmres->m10 = pm0->m10;	pmres->m11 = pm0->m11;	pmres->m12 = pm0->m12;	pmres->m13 = 0.0f;
	pmres->m20 = pm0->m20;	pmres->m21 = pm0->m21;	pmres->m22 = pm0->m22;	pmres->m23 = 0.0f;
	pmres->m30 = 0.0f;		pmres->m31 = 0.0f;		pmres->m32 = 0.0f;		pmres->m33 = 1.0f;
	return pmres;
}

inline MATRIX4X4 * MATRIX4X4_Init3X3(MATRIX4X4 * pmres, const REAL f00, const REAL f01, const REAL f02,
														const REAL f10, const REAL f11, const REAL f12,
														const REAL f20, const REAL f21, const REAL f22)
{
	pmres->m00 = f00;		pmres->m01 = f01;		pmres->m02 = f02;		pmres->m03 = 0.0f;
	pmres->m10 = f10;		pmres->m11 = f11;		pmres->m12 = f12;		pmres->m13 = 0.0f;
	pmres->m20 = f20;		pmres->m21 = f21;		pmres->m22 = f22;		pmres->m23 = 0.0f;
	pmres->m30 = 0.0f;		pmres->m31 = 0.0f;		pmres->m32 = 0.0f;		pmres->m33 = 1.0f;
	return pmres;
}

inline MATRIX4X4 * MATRIX4X4_Init4X4(MATRIX4X4 * pmres, const REAL f00, const REAL f01, const REAL f02, const REAL f03,
														const REAL f10, const REAL f11, const REAL f12, const REAL f13,
														const REAL f20, const REAL f21, const REAL f22, const REAL f23,
														const REAL f30, const REAL f31, const REAL f32, const REAL f33)
{
	pmres->m00 = f00;		pmres->m01 = f01;		pmres->m02 = f02;		pmres->m03 = f03;
	pmres->m10 = f10;		pmres->m11 = f11;		pmres->m12 = f12;		pmres->m13 = f13;
	pmres->m20 = f20;		pmres->m21 = f21;		pmres->m22 = f22;		pmres->m23 = f23;
	pmres->m30 = f30;		pmres->m31 = f31;		pmres->m32 = f32;		pmres->m33 = f33;
	return pmres;
}

inline void MATRIX4X4_Print(const MATRIX4X4 * pm0)
{
	printf(	"MATRIX4X4 { %f, %f, %f, %f,\n"
			"            %f, %f, %f, %f,\n"
			"            %f, %f, %f, %f,\n"
			"            %f, %f, %f, %f, }",	pm0->m00, pm0->m01, pm0->m02, pm0->m03,
												pm0->m10, pm0->m11, pm0->m12, pm0->m13,
												pm0->m20, pm0->m21, pm0->m22, pm0->m23,
												pm0->m30, pm0->m31, pm0->m32, pm0->m33);
}

inline MATRIX2X2 * Mat_Transpose_2X2(MATRIX2X2 * pmres, const MATRIX2X2 * pm0)
{
	pmres->m00 = pm0->m00;
	pmres->m01 = pm0->m10;
	pmres->m10 = pm0->m01;
	pmres->m11 = pm0->m11;
	return pmres;
}

inline MATRIX2X2 * Mat_Transpose_2X2(MATRIX2X2 * pm0)
{
	REAL ftmp;
	SWAP(pm0->m01, pm0->m10, ftmp);
	return pm0;
}

inline MATRIX3X3 * Mat_Transpose_3X3(MATRIX3X3 * pmres, const MATRIX3X3 * pm0)
{
	pmres->m00 = pm0->m00;	pmres->m01 = pm0->m10;	pmres->m02 = pm0->m20;
	pmres->m10 = pm0->m01;	pmres->m11 = pm0->m11;	pmres->m12 = pm0->m21;
	pmres->m20 = pm0->m02;	pmres->m21 = pm0->m12;	pmres->m22 = pm0->m22;
	return pmres;
}

inline MATRIX3X3 * Mat_Transpose_3X3(MATRIX3X3 * pm0)
{
	REAL ftmp;
	SWAP(pm0->m01, pm0->m10, ftmp);
	SWAP(pm0->m02, pm0->m20, ftmp);
	SWAP(pm0->m12, pm0->m21, ftmp);
	return pm0;
}

inline MATRIX4X4 * Mat_Transpose_4X4(MATRIX4X4 * pmres, const MATRIX4X4 * pm0)
{
	pmres->m00 = pm0->m00;	pmres->m01 = pm0->m10;	pmres->m02 = pm0->m20;	pmres->m03 = pm0->m30;
	pmres->m10 = pm0->m01;	pmres->m11 = pm0->m11;	pmres->m12 = pm0->m21;	pmres->m13 = pm0->m31;
	pmres->m20 = pm0->m02;	pmres->m21 = pm0->m12;	pmres->m22 = pm0->m22;	pmres->m23 = pm0->m32;
	pmres->m30 = pm0->m03;	pmres->m31 = pm0->m13;	pmres->m32 = pm0->m23;	pmres->m33 = pm0->m33;
	return pmres;
}

inline MATRIX4X4 * Mat_Transpose_4X4(MATRIX4X4 * pm0)
{
	REAL ftmp;
	SWAP(pm0->m01, pm0->m10, ftmp);
	SWAP(pm0->m02, pm0->m20, ftmp);
	SWAP(pm0->m03, pm0->m30, ftmp);
	SWAP(pm0->m12, pm0->m21, ftmp);
	SWAP(pm0->m13, pm0->m31, ftmp);
	SWAP(pm0->m23, pm0->m32, ftmp);
	return pm0;
}

inline REAL Mat_Det_2X2(const MATRIX2X2 * pm0)
{
	return pm0->m00 * pm0->m11 - pm0->m01 * pm0->m10;
}

inline REAL Mat_Det_3X3(const MATRIX3X3 * pm0)
{
	return	(pm0->m00 * pm0->m11 * pm0->m22 + pm0->m01 * pm0->m12 * pm0->m20 + pm0->m02 * pm0->m10 * pm0->m21) -
			(pm0->m00 * pm0->m12 * pm0->m21 + pm0->m01 * pm0->m10 * pm0->m22 + pm0->m02 * pm0->m11 * pm0->m20);
}

inline REAL Mat_Det_4X4(const MATRIX4X4 * pm0)
{
	return	(pm0->m00 * pm0->m11 * pm0->m22 * pm0->m33 + pm0->m01 * pm0->m12 * pm0->m23 * pm0->m30 + pm0->m02 * pm0->m13 * pm0->m20 * pm0->m31 + pm0->m03 * pm0->m10 * pm0->m21 * pm0->m32) -
			(pm0->m00 * pm0->m13 * pm0->m22 * pm0->m31 + pm0->m01 * pm0->m10 * pm0->m23 * pm0->m32 + pm0->m02 * pm0->m11 * pm0->m20 * pm0->m33 + pm0->m03 * pm0->m12 * pm0->m21 * pm0->m30);
}

inline MATRIX2X2 * Mat_Add_2X2(MATRIX2X2 * pmres, const MATRIX2X2 * pm0, const MATRIX2X2 * pm1)
{
	pmres->m00 = pm0->m00 + pm1->m00;
	pmres->m01 = pm0->m01 + pm1->m01;
	pmres->m10 = pm0->m10 + pm1->m10;
	pmres->m11 = pm0->m11 + pm1->m11;
	return pmres;
}

inline MATRIX2X2 * Mat_Add_2X2(MATRIX2X2 * pm0, const MATRIX2X2 * pm1)
{
	pm0->m00 += pm1->m00;
	pm0->m01 += pm1->m01;
	pm0->m10 += pm1->m10;
	pm0->m11 += pm1->m11;
	return pm0;
}

inline MATRIX2X2 * Mat_Add_2X2(MATRIX2X2 * pmres, const MATRIX2X2 * pm0, const REAL scale)
{
	pmres->m00 = pm0->m00 + scale;
	pmres->m01 = pm0->m01 + scale;
	pmres->m10 = pm0->m10 + scale;
	pmres->m11 = pm0->m11 + scale;
	return pmres;
}

inline MATRIX2X2 * Mat_Add_2X2(MATRIX2X2 * pm0, const REAL scale)
{
	pm0->m00 += scale;
	pm0->m01 += scale;
	pm0->m10 += scale;
	pm0->m11 += scale;
	return pm0;
}

inline MATRIX3X3 * Mat_Add_3X3(MATRIX3X3 * pmres, const MATRIX3X3 * pm0, const MATRIX3X3 * pm1)
{
	pmres->m00 = pm0->m00 + pm1->m00;	pmres->m01 = pm0->m01 + pm1->m01;	pmres->m02 = pm0->m02 + pm1->m02;
	pmres->m10 = pm0->m10 + pm1->m10;	pmres->m11 = pm0->m11 + pm1->m11;	pmres->m12 = pm0->m12 + pm1->m12;
	pmres->m20 = pm0->m20 + pm1->m20;	pmres->m21 = pm0->m21 + pm1->m21;	pmres->m22 = pm0->m22 + pm1->m22;
	return pmres;
}

inline MATRIX3X3 * Mat_Add_3X3(MATRIX3X3 * pm0, const MATRIX3X3 * pm1)
{
	pm0->m00 += pm1->m00;	pm0->m01 += pm1->m01;	pm0->m02 += pm1->m02;
	pm0->m10 += pm1->m10;	pm0->m11 += pm1->m11;	pm0->m12 += pm1->m12;
	pm0->m20 += pm1->m20;	pm0->m21 += pm1->m21;	pm0->m22 += pm1->m22;
	return pm0;
}

inline MATRIX3X3 * Mat_Add_3X3(MATRIX3X3 * pmres, const MATRIX3X3 * pm0, const REAL scale)
{
	pmres->m00 = pm0->m00 + scale;	pmres->m01 = pm0->m01 + scale;	pmres->m02 = pm0->m02 + scale;
	pmres->m10 = pm0->m10 + scale;	pmres->m11 = pm0->m11 + scale;	pmres->m12 = pm0->m12 + scale;
	pmres->m20 = pm0->m20 + scale;	pmres->m21 = pm0->m21 + scale;	pmres->m22 = pm0->m22 + scale;
	return pmres;
}

inline MATRIX3X3 * Mat_Add_3X3(MATRIX3X3 * pm0, const REAL scale)
{
	pm0->m00 += scale;	pm0->m01 += scale;	pm0->m02 += scale;
	pm0->m10 += scale;	pm0->m11 += scale;	pm0->m12 += scale;
	pm0->m20 += scale;	pm0->m21 += scale;	pm0->m22 += scale;
	return pm0;
}

inline MATRIX4X4 * Mat_Add_4X4(MATRIX4X4 * pmres, const MATRIX4X4 * pm0, const MATRIX4X4 * pm1)
{
	pmres->m00 = pm0->m00 + pm1->m00;	pmres->m01 = pm0->m01 + pm1->m01;	pmres->m02 = pm0->m02 + pm1->m02;	pmres->m03 = pm0->m03 + pm1->m03;
	pmres->m10 = pm0->m10 + pm1->m10;	pmres->m11 = pm0->m11 + pm1->m11;	pmres->m12 = pm0->m12 + pm1->m12;	pmres->m13 = pm0->m13 + pm1->m13;
	pmres->m20 = pm0->m20 + pm1->m20;	pmres->m21 = pm0->m21 + pm1->m21;	pmres->m22 = pm0->m22 + pm1->m22;	pmres->m23 = pm0->m23 + pm1->m23;
	pmres->m30 = pm0->m30 + pm1->m30;	pmres->m31 = pm0->m31 + pm1->m31;	pmres->m32 = pm0->m32 + pm1->m32;	pmres->m33 = pm0->m33 + pm1->m33;
	return pmres;
}

inline MATRIX4X4 * Mat_Add_4X4(MATRIX4X4 * pm0, const MATRIX4X4 * pm1)
{
	pm0->m00 += pm1->m00;	pm0->m01 += pm1->m01;	pm0->m02 += pm1->m02;	pm0->m03 += pm1->m03;
	pm0->m10 += pm1->m10;	pm0->m11 += pm1->m11;	pm0->m12 += pm1->m12;	pm0->m13 += pm1->m13;
	pm0->m20 += pm1->m20;	pm0->m21 += pm1->m21;	pm0->m22 += pm1->m22;	pm0->m23 += pm1->m23;
	pm0->m30 += pm1->m30;	pm0->m31 += pm1->m31;	pm0->m32 += pm1->m32;	pm0->m33 += pm1->m33;
	return pm0;
}

inline MATRIX4X4 * Mat_Add_4X4(MATRIX4X4 * pmres, const MATRIX4X4 * pm0, const REAL scale)
{
	pmres->m00 = pm0->m00 + scale;	pmres->m01 = pm0->m01 + scale;	pmres->m02 = pm0->m02 + scale;	pmres->m03 = pm0->m03 + scale;
	pmres->m10 = pm0->m10 + scale;	pmres->m11 = pm0->m11 + scale;	pmres->m12 = pm0->m12 + scale;	pmres->m13 = pm0->m13 + scale;
	pmres->m20 = pm0->m20 + scale;	pmres->m21 = pm0->m21 + scale;	pmres->m22 = pm0->m22 + scale;	pmres->m23 = pm0->m23 + scale;
	pmres->m30 = pm0->m30 + scale;	pmres->m31 = pm0->m31 + scale;	pmres->m32 = pm0->m32 + scale;	pmres->m33 = pm0->m33 + scale;
	return pmres;
}

inline MATRIX4X4 * Mat_Add_4X4(MATRIX4X4 * pm0, const REAL scale)
{
	pm0->m00 += scale;	pm0->m01 += scale;	pm0->m02 += scale;	pm0->m03 += scale;
	pm0->m10 += scale;	pm0->m11 += scale;	pm0->m12 += scale;	pm0->m13 += scale;
	pm0->m20 += scale;	pm0->m21 += scale;	pm0->m22 += scale;	pm0->m23 += scale;
	pm0->m30 += scale;	pm0->m31 += scale;	pm0->m32 += scale;	pm0->m33 += scale;
	return pm0;
}

inline MATRIX2X2 * Mat_Mul_2X2(MATRIX2X2 * pmres, const MATRIX2X2 * pm0, const MATRIX2X2 * pm1)
{
	pmres->m00 = pm0->m00 * pm1->m00 + pm0->m01 * pm1->m10;
	pmres->m01 = pm0->m00 * pm1->m01 + pm0->m01 * pm1->m11;
	pmres->m10 = pm0->m10 * pm1->m00 + pm0->m11 * pm1->m10;
	pmres->m11 = pm0->m10 * pm1->m01 + pm0->m11 * pm1->m11;
	return pmres;
}

inline MATRIX2X2 * Mat_Mul_2X2(MATRIX2X2 * pmres, const MATRIX2X2 * pm0, const REAL scale)
{
	pmres->m00 = pm0->m00 * scale;
	pmres->m01 = pm0->m01 * scale;
	pmres->m10 = pm0->m10 * scale;
	pmres->m11 = pm0->m11 * scale;
	return pmres;
}

inline MATRIX2X2 * Mat_Mul_2X2(MATRIX2X2 * pm0, const REAL scale)
{
	pm0->m00 *= scale;
	pm0->m01 *= scale;
	pm0->m10 *= scale;
	pm0->m11 *= scale;
	return pm0;
}

inline MATRIX3X2 * Mat_Mul_3X2(MATRIX3X2 * pmres, const MATRIX3X2 * pm0, const MATRIX3X2 * pm1)
{
	pmres->m00 = pm0->m00 * pm1->m00 + pm0->m01 * pm1->m10;
	pmres->m01 = pm0->m00 * pm1->m01 + pm0->m01 * pm1->m11;
	pmres->m10 = pm0->m10 * pm1->m00 + pm0->m11 * pm1->m10;
	pmres->m11 = pm0->m10 * pm1->m01 + pm0->m11 * pm1->m11;
	pmres->m20 = pm0->m20 * pm1->m00 + pm0->m21 * pm1->m10 + pm1->m20;
	pmres->m21 = pm0->m20 * pm1->m01 + pm0->m21 * pm1->m11 + pm1->m21;
	return pmres;
}

inline MATRIX3X3 * Mat_Mul_3X3(MATRIX3X3 * pmres, const MATRIX3X3 * pm0, const MATRIX3X3 * pm1)
{
	pmres->m00 = pm0->m00 * pm1->m00 + pm0->m01 * pm1->m10 + pm0->m02 * pm1->m20;
	pmres->m01 = pm0->m00 * pm1->m01 + pm0->m01 * pm1->m11 + pm0->m02 * pm1->m21;
	pmres->m02 = pm0->m00 * pm1->m02 + pm0->m01 * pm1->m12 + pm0->m02 * pm1->m22;
	pmres->m10 = pm0->m10 * pm1->m00 + pm0->m11 * pm1->m10 + pm0->m12 * pm1->m20;
	pmres->m11 = pm0->m10 * pm1->m01 + pm0->m11 * pm1->m11 + pm0->m12 * pm1->m21;
	pmres->m12 = pm0->m10 * pm1->m02 + pm0->m11 * pm1->m12 + pm0->m12 * pm1->m22;
	pmres->m20 = pm0->m20 * pm1->m00 + pm0->m21 * pm1->m10 + pm0->m22 * pm1->m20;
	pmres->m21 = pm0->m20 * pm1->m01 + pm0->m21 * pm1->m11 + pm0->m22 * pm1->m21;
	pmres->m22 = pm0->m20 * pm1->m02 + pm0->m21 * pm1->m12 + pm0->m22 * pm1->m22;
	return pmres;
}

inline MATRIX3X3 * Mat_Mul_3X3(MATRIX3X3 * pmres, const MATRIX3X3 * pm0, const REAL scale)
{
	pmres->m00 = pm0->m00 * scale;	pmres->m01 = pm0->m01 * scale;	pmres->m02 = pm0->m02 * scale;
	pmres->m10 = pm0->m10 * scale;	pmres->m11 = pm0->m11 * scale;	pmres->m12 = pm0->m12 * scale;
	pmres->m20 = pm0->m20 * scale;	pmres->m21 = pm0->m21 * scale;	pmres->m22 = pm0->m22 * scale;
	return pmres;
}

inline MATRIX3X3 * Mat_Mul_3X3(MATRIX3X3 * pm0, const REAL scale)
{
	pm0->m00 *= scale;	pm0->m01 *= scale;	pm0->m02 *= scale;
	pm0->m10 *= scale;	pm0->m11 *= scale;	pm0->m12 *= scale;
	pm0->m20 *= scale;	pm0->m21 *= scale;	pm0->m22 *= scale;
	return pm0;
}

inline MATRIX4X3 * Mat_Mul_4X3(MATRIX4X3 * pmres, const MATRIX4X3 * pm0, const MATRIX4X3 * pm1)
{
	pmres->m00 = pm0->m00 * pm1->m00 + pm0->m01 * pm1->m10 + pm0->m02 * pm1->m20;
	pmres->m01 = pm0->m00 * pm1->m01 + pm0->m01 * pm1->m11 + pm0->m02 * pm1->m21;
	pmres->m02 = pm0->m00 * pm1->m02 + pm0->m01 * pm1->m12 + pm0->m02 * pm1->m22;

	pmres->m10 = pm0->m10 * pm1->m00 + pm0->m11 * pm1->m10 + pm0->m12 * pm1->m20;
	pmres->m11 = pm0->m10 * pm1->m01 + pm0->m11 * pm1->m11 + pm0->m12 * pm1->m21;
	pmres->m12 = pm0->m10 * pm1->m02 + pm0->m11 * pm1->m12 + pm0->m12 * pm1->m22;

	pmres->m20 = pm0->m20 * pm1->m00 + pm0->m21 * pm1->m10 + pm0->m22 * pm1->m20;
	pmres->m21 = pm0->m20 * pm1->m01 + pm0->m21 * pm1->m11 + pm0->m22 * pm1->m21;
	pmres->m22 = pm0->m20 * pm1->m02 + pm0->m21 * pm1->m12 + pm0->m22 * pm1->m22;

	pmres->m30 = pm0->m30 * pm1->m00 + pm0->m31 * pm1->m10 + pm0->m32 * pm1->m20 + pm1->m30;
	pmres->m31 = pm0->m30 * pm1->m01 + pm0->m31 * pm1->m11 + pm0->m32 * pm1->m21 + pm1->m31;
	pmres->m32 = pm0->m30 * pm1->m02 + pm0->m31 * pm1->m12 + pm0->m32 * pm1->m22 + pm1->m32;
	return pmres;
}

inline MATRIX4X4 * Mat_Mul_4X4(MATRIX4X4 * pmres, const MATRIX4X4 * pm0, const MATRIX4X4 * pm1)
{
	pmres->m00 = pm0->m00 * pm1->m00 + pm0->m01 * pm1->m10 + pm0->m02 * pm1->m20 + pm0->m03 * pm1->m30;
	pmres->m01 = pm0->m00 * pm1->m01 + pm0->m01 * pm1->m11 + pm0->m02 * pm1->m21 + pm0->m03 * pm1->m31;
	pmres->m02 = pm0->m00 * pm1->m02 + pm0->m01 * pm1->m12 + pm0->m02 * pm1->m22 + pm0->m03 * pm1->m32;
	pmres->m03 = pm0->m00 * pm1->m03 + pm0->m01 * pm1->m13 + pm0->m02 * pm1->m23 + pm0->m03 * pm1->m33;

	pmres->m10 = pm0->m10 * pm1->m00 + pm0->m11 * pm1->m10 + pm0->m12 * pm1->m20 + pm0->m13 * pm1->m30;
	pmres->m11 = pm0->m10 * pm1->m01 + pm0->m11 * pm1->m11 + pm0->m12 * pm1->m21 + pm0->m13 * pm1->m31;
	pmres->m12 = pm0->m10 * pm1->m02 + pm0->m11 * pm1->m12 + pm0->m12 * pm1->m22 + pm0->m13 * pm1->m32;
	pmres->m13 = pm0->m10 * pm1->m03 + pm0->m11 * pm1->m13 + pm0->m12 * pm1->m23 + pm0->m13 * pm1->m33;

	pmres->m20 = pm0->m20 * pm1->m00 + pm0->m21 * pm1->m10 + pm0->m22 * pm1->m20 + pm0->m23 * pm1->m30;
	pmres->m21 = pm0->m20 * pm1->m01 + pm0->m21 * pm1->m11 + pm0->m22 * pm1->m21 + pm0->m23 * pm1->m31;
	pmres->m22 = pm0->m20 * pm1->m02 + pm0->m21 * pm1->m12 + pm0->m22 * pm1->m22 + pm0->m23 * pm1->m32;
	pmres->m23 = pm0->m20 * pm1->m03 + pm0->m21 * pm1->m13 + pm0->m22 * pm1->m23 + pm0->m23 * pm1->m33;

	pmres->m30 = pm0->m30 * pm1->m00 + pm0->m31 * pm1->m10 + pm0->m32 * pm1->m20 + pm0->m33 * pm1->m30;
	pmres->m31 = pm0->m30 * pm1->m01 + pm0->m31 * pm1->m11 + pm0->m32 * pm1->m21 + pm0->m33 * pm1->m31;
	pmres->m32 = pm0->m30 * pm1->m02 + pm0->m31 * pm1->m12 + pm0->m32 * pm1->m22 + pm0->m33 * pm1->m32;
	pmres->m33 = pm0->m30 * pm1->m03 + pm0->m31 * pm1->m13 + pm0->m32 * pm1->m23 + pm0->m33 * pm1->m33;
	return pmres;
}

inline MATRIX4X4 * Mat_Mul_4X4(MATRIX4X4 * pmres, const MATRIX4X4 * pm0, const REAL scale)
{
	pmres->m00 = pm0->m00 * scale;	pmres->m01 = pm0->m01 * scale;	pmres->m02 = pm0->m02 * scale;	pmres->m03 = pm0->m03 * scale;
	pmres->m10 = pm0->m10 * scale;	pmres->m11 = pm0->m11 * scale;	pmres->m12 = pm0->m12 * scale;	pmres->m13 = pm0->m13 * scale;
	pmres->m20 = pm0->m20 * scale;	pmres->m21 = pm0->m21 * scale;	pmres->m22 = pm0->m22 * scale;	pmres->m23 = pm0->m23 * scale;
	pmres->m30 = pm0->m30 * scale;	pmres->m31 = pm0->m31 * scale;	pmres->m32 = pm0->m32 * scale;	pmres->m33 = pm0->m33 * scale;
	return pmres;
}

inline MATRIX4X4 * Mat_Mul_4X4(MATRIX4X4 * pm0, const REAL scale)
{
	pm0->m00 *= scale;	pm0->m01 *= scale;	pm0->m02 *= scale;	pm0->m03 *= scale;
	pm0->m10 *= scale;	pm0->m11 *= scale;	pm0->m12 *= scale;	pm0->m13 *= scale;
	pm0->m20 *= scale;	pm0->m21 *= scale;	pm0->m22 *= scale;	pm0->m23 *= scale;
	pm0->m30 *= scale;	pm0->m31 *= scale;	pm0->m32 *= scale;	pm0->m33 *= scale;
	return pm0;
}

inline VECTOR2D * Mat_Mul_VECTOR2D_2X2(VECTOR2D * pvres, const VECTOR2D * pv0, const MATRIX2X2 * pm0)
{
	pvres->x = pv0->x * pm0->m00 + pv0->y * pm0->m10;
	pvres->y = pv0->x * pm0->m01 + pv0->y * pm0->m11;
	return pvres;
}

inline VECTOR3D * Mat_Mul_VECTOR3D_3X2(VECTOR3D * pvres, const VECTOR3D * pv0, const MATRIX3X2 * pm0)
{
	assert(pv0->z == 1.0f);

	pvres->x = pv0->x * pm0->m00 + pv0->y * pm0->m10 + pm0->m20;
	pvres->y = pv0->x * pm0->m01 + pv0->y * pm0->m11 + pm0->m21;
	pvres->z = 1.0f;
	return pvres;
}

inline VECTOR3D * Mat_Mul_VECTOR3D_3X3(VECTOR3D * pvres, const VECTOR3D * pv0, const MATRIX3X3 * pm0)
{
	pvres->x = pv0->x * pm0->m00 + pv0->y * pm0->m10 + pv0->z * pm0->m20;
	pvres->y = pv0->x * pm0->m01 + pv0->y * pm0->m11 + pv0->z * pm0->m21;
	pvres->z = pv0->x * pm0->m02 + pv0->y * pm0->m12 + pv0->z * pm0->m22;
	return pvres;
}

inline VECTOR4D * Mat_Mul_VECTOR4D_4X3(VECTOR4D * pvres, const VECTOR4D * pv0, const MATRIX4X3 * pm0)
{
	assert(pv0->w == 1.0f);

	pvres->x = pv0->x * pm0->m00 + pv0->y * pm0->m10 + pv0->z * pm0->m20 + pm0->m30;
	pvres->y = pv0->x * pm0->m01 + pv0->y * pm0->m11 + pv0->z * pm0->m21 + pm0->m31;
	pvres->z = pv0->x * pm0->m02 + pv0->y * pm0->m12 + pv0->z * pm0->m22 + pm0->m32;
	pvres->w = 1.0f;
	return pvres;
}

inline VECTOR4D * Mat_Mul_VECTOR4D_4X4(VECTOR4D * pvres, const VECTOR4D * pv0, const MATRIX4X4 * pm0)
{
	pvres->x = pv0->x * pm0->m00 + pv0->y * pm0->m10 + pv0->z * pm0->m20 + pv0->w * pm0->m30;
	pvres->y = pv0->x * pm0->m01 + pv0->y * pm0->m11 + pv0->z * pm0->m21 + pv0->w * pm0->m31;
	pvres->z = pv0->x * pm0->m02 + pv0->y * pm0->m12 + pv0->z * pm0->m22 + pv0->w * pm0->m32;
	pvres->w = pv0->x * pm0->m03 + pv0->y * pm0->m13 + pv0->z * pm0->m23 + pv0->w * pm0->m33;
	return pvres;
}

#define MAX_COLOR_INTENSITY16		(0x0020)
#define MAX_COLOR_INTENSITY16G		(0x0040)
#define MAX_COLOR_INTENSITY32		(0x0100)

//#define MAX_COLOR_INTENSITY16_SHIFT		(5)
//#define MAX_COLOR_INTENSITY16G_SHIFT	(6)
//#define MAX_COLOR_INTENSITY32_SHIFT		(8)

#define COLOR_ADD_16R(c0, c1)		(COLOR_TABLE_ADD16[(c0)][(c1)])
#define COLOR_ADD_16G(c0, c1)		(COLOR_TABLE_ADD16G[(c0)][(c1)])
#define COLOR_ADD_16B(c0, c1)		(COLOR_TABLE_ADD16[(c0)][(c1)])

#define COLOR_ADD_32R(c0, c1)		(COLOR_TABLE_ADD32[(c0)][(c1)])
#define COLOR_ADD_32G(c0, c1)		(COLOR_TABLE_ADD32[(c0)][(c1)])
#define COLOR_ADD_32B(c0, c1)		(COLOR_TABLE_ADD32[(c0)][(c1)])

#define COLOR_MUL_16R(c0, c1)		(COLOR_TABLE_MUL16[(c0)][(c1)])
#define COLOR_MUL_16G(c0, c1)		(COLOR_TABLE_MUL16G[(c0)][(c1)])
#define COLOR_MUL_16B(c0, c1)		(COLOR_TABLE_MUL16[(c0)][(c1)])

#define COLOR_MUL_32R(c0, c1)		(COLOR_TABLE_MUL32[(c0)][(c1)])
#define COLOR_MUL_32G(c0, c1)		(COLOR_TABLE_MUL32[(c0)][(c1)])
#define COLOR_MUL_32B(c0, c1)		(COLOR_TABLE_MUL32[(c0)][(c1)])

//#define COLOR_ADD_16R(c0, c1)		(*(*COLOR_TABLE_ADD16 + ((c0) << MAX_COLOR_INTENSITY16_SHIFT) + (c1)))
//#define COLOR_ADD_16G(c0, c1)		(*(*COLOR_TABLE_ADD16G + ((c0) << MAX_COLOR_INTENSITY16G_SHIFT) + (c1)))
//#define COLOR_ADD_16B(c0, c1)		(*(*COLOR_TABLE_ADD16 + ((c0) << MAX_COLOR_INTENSITY16_SHIFT) + (c1)))
//
//#define COLOR_ADD_32R(c0, c1)		(*(*COLOR_TABLE_ADD32 + ((c0) << MAX_COLOR_INTENSITY32_SHIFT) + (c1)))
//#define COLOR_ADD_32G(c0, c1)		(*(*COLOR_TABLE_ADD32 + ((c0) << MAX_COLOR_INTENSITY32_SHIFT) + (c1)))
//#define COLOR_ADD_32B(c0, c1)		(*(*COLOR_TABLE_ADD32 + ((c0) << MAX_COLOR_INTENSITY32_SHIFT) + (c1)))
//
//#define COLOR_MUL_16R(c0, c1)		(*(*COLOR_TABLE_MUL16 + ((c0) << MAX_COLOR_INTENSITY16_SHIFT) + (c1)))
//#define COLOR_MUL_16G(c0, c1)		(*(*COLOR_TABLE_MUL16G + ((c0) << MAX_COLOR_INTENSITY16G_SHIFT) + (c1)))
//#define COLOR_MUL_16B(c0, c1)		(*(*COLOR_TABLE_MUL16 + ((c0) << MAX_COLOR_INTENSITY16_SHIFT) + (c1)))
//
//#define COLOR_MUL_32R(c0, c1)		(*(*COLOR_TABLE_MUL32 + ((c0) << MAX_COLOR_INTENSITY32_SHIFT) + (c1)))
//#define COLOR_MUL_32G(c0, c1)		(*(*COLOR_TABLE_MUL32 + ((c0) << MAX_COLOR_INTENSITY32_SHIFT) + (c1)))
//#define COLOR_MUL_32B(c0, c1)		(*(*COLOR_TABLE_MUL32 + ((c0) << MAX_COLOR_INTENSITY32_SHIFT) + (c1)))

#define FIXP16_SHIFT				(16)
#define FIXP16_MAG					(0x00010000)
#define FIXP16_DMASK				(0x0000FFFF)
#define FIXP16_WMASK				(0xFFFF0000)

#define FIXP28_SHIFT				(28)
#define FIXP28_MAG					(0x10000000)
#define FIXP28_DMASK				(0x0FFFFFFF)
#define FIXP28_WMASK				(0xF0000000)

//#pragma warning(disable : 4201)
//typedef struct T3DLIB_API FIXP16_TYP
//{
//	union
//	{
//		int val;
//
//		struct
//		{
//			short			integer;
//			unsigned short	decimal;
//		};
//
//		//struct
//		//{
//		//	unsigned char	c1;
//		//	unsigned char	c2;
//		//	unsigned char	c3;
//		//	unsigned char	c4;
//		//};
//	};
//
//} FIXP16, * FIXP16_PTR;

//typedef struct T3DLIB_API RGB16_TYP
//{
//	union
//	{
//		unsigned short val;
//	};
//
//} RGB16, * RGB16_PTR;

//typedef struct T3DLIB_API RGB32_TYP
//{
//	union
//	{
//		unsigned int val;
//
//		struct
//		{
//			unsigned char	x;
//			unsigned char	r;
//			unsigned char	g;
//			unsigned char	b;
//		};
//	};
//
//} RGB32, * RGB32_PTR;
//#pragma warning(default : 4201)

typedef unsigned short RGB16_TYP;
typedef RGB16_TYP RGB16, * RGB16_PTR;

typedef unsigned int RGB32_TYP;
typedef RGB32_TYP RGB32, * RGB32_PTR;

typedef int FIXP16_TYP;
typedef FIXP16_TYP FIXP16, * FIXP16_PTR;

typedef int FIXP28_TYP;
typedef FIXP28_TYP FIXP28, * FIXP28_PTR;

extern T3DLIB_API unsigned char COLOR_TABLE_ADD16[MAX_COLOR_INTENSITY16][MAX_COLOR_INTENSITY16];
extern T3DLIB_API unsigned char COLOR_TABLE_ADD16G[MAX_COLOR_INTENSITY16G][MAX_COLOR_INTENSITY16G];
extern T3DLIB_API unsigned char COLOR_TABLE_ADD32[MAX_COLOR_INTENSITY32][MAX_COLOR_INTENSITY32];
extern T3DLIB_API unsigned char COLOR_TABLE_MUL16[MAX_COLOR_INTENSITY16][MAX_COLOR_INTENSITY16];
extern T3DLIB_API unsigned char COLOR_TABLE_MUL16G[MAX_COLOR_INTENSITY16G][MAX_COLOR_INTENSITY16G];
extern T3DLIB_API unsigned char COLOR_TABLE_MUL32[MAX_COLOR_INTENSITY32][MAX_COLOR_INTENSITY32];

T3DLIB_API bool Init_T3dlib4(int bpp);

inline RGB16 * RGB16_Add(RGB16 * pcres, const RGB16 * pc0, const RGB16 * pc1)
{
	//((XRGB16 *)pcres)->r = COLOR_ADD_16R(((XRGB16 *)pc0)->r, ((XRGB16 *)pc1)->r);
	//((XRGB16 *)pcres)->g = COLOR_ADD_16G(((XRGB16 *)pc0)->g, ((XRGB16 *)pc1)->g);
	//((XRGB16 *)pcres)->b = COLOR_ADD_16B(((XRGB16 *)pc0)->b, ((XRGB16 *)pc1)->b);

	*pcres = (unsigned short)_RGB16BIT(
			COLOR_ADD_16R(_16BIT_GETR(*pc0), _16BIT_GETR(*pc1)),
			COLOR_ADD_16G(_16BIT_GETG(*pc0), _16BIT_GETG(*pc1)),
			COLOR_ADD_16B(_16BIT_GETB(*pc0), _16BIT_GETB(*pc1)));
	return pcres;
}

inline RGB16 * RGB16_Mul(RGB16 * pcres, const RGB16 * pc0, const RGB16 * pc1)
{
	//((XRGB16 *)pcres)->r = COLOR_MUL_16R(((XRGB16 *)pc0)->r, ((XRGB16 *)pc1)->r);
	//((XRGB16 *)pcres)->g = COLOR_MUL_16G(((XRGB16 *)pc0)->g, ((XRGB16 *)pc1)->g);
	//((XRGB16 *)pcres)->b = COLOR_MUL_16B(((XRGB16 *)pc0)->b, ((XRGB16 *)pc1)->b);

	*pcres = (unsigned short)_RGB16BIT(
			COLOR_MUL_16R(_16BIT_GETR(*pc0), _16BIT_GETR(*pc1)),
			COLOR_MUL_16G(_16BIT_GETG(*pc0), _16BIT_GETG(*pc1)),
			COLOR_MUL_16B(_16BIT_GETB(*pc0), _16BIT_GETB(*pc1)));
	return pcres;
}

inline RGB32 * RGB32_Add(RGB32 * pcres, const RGB32 * pc0, const RGB32 * pc1)
{
	//((XRGB32 *)pcres)->r = COLOR_ADD_32R(((XRGB32 *)pc0)->r, ((XRGB32 *)pc1)->r);
	//((XRGB32 *)pcres)->g = COLOR_ADD_32G(((XRGB32 *)pc0)->g, ((XRGB32 *)pc1)->g);
	//((XRGB32 *)pcres)->b = COLOR_ADD_32B(((XRGB32 *)pc0)->b, ((XRGB32 *)pc1)->b);

	*pcres = (unsigned int)_RGB32BIT(
			COLOR_ADD_32R(_32BIT_GETR(*pc0), _32BIT_GETR(*pc1)),
			COLOR_ADD_32G(_32BIT_GETG(*pc0), _32BIT_GETG(*pc1)),
			COLOR_ADD_32B(_32BIT_GETB(*pc0), _32BIT_GETB(*pc1)));
	return pcres;
}

inline RGB32 * RGB32_Mul(RGB32 * pcres, const RGB32 * pc0, const RGB32 * pc1)
{
	//((XRGB32 *)pcres)->r = COLOR_MUL_32R(((XRGB32 *)pc0)->r, ((XRGB32 *)pc1)->r);
	//((XRGB32 *)pcres)->g = COLOR_MUL_32G(((XRGB32 *)pc0)->g, ((XRGB32 *)pc1)->g);
	//((XRGB32 *)pcres)->b = COLOR_MUL_32B(((XRGB32 *)pc0)->b, ((XRGB32 *)pc1)->b);

	*pcres = (unsigned int)_RGB32BIT(
			COLOR_MUL_32R(_32BIT_GETR(*pc0), _32BIT_GETR(*pc1)),
			COLOR_MUL_32G(_32BIT_GETG(*pc0), _32BIT_GETG(*pc1)),
			COLOR_MUL_32B(_32BIT_GETB(*pc0), _32BIT_GETB(*pc1)));
	return pcres;
}

#endif // __T3DLIB4_H__
