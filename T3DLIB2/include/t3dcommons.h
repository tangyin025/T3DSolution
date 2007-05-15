/**
 * File: T3DLIB2/t3dcommons.h
 */

#ifndef __T3DCOMMONS_H__
#define __T3DCOMMONS_H__

#ifdef T3DLIB2_EXPORTS
#define T3DLIB_API __declspec(dllexport)
#else
#define T3DLIB_API __declspec(dllimport)
#endif // T3DLIB2_EXPORTS

#ifdef T3DLIB2_DOUBLE_PRECISION
typedef double	REAL;
#else
typedef float	REAL;
#endif // T3DLIB2_DOUBLE_PRECISION

#define SWAP(a, b, temp)	{ temp = a; a = b; b = temp; }
#define MAX(a, b)			(((a) > (b)) ? (a) : (b))
#define MIN(a, b)			(((a) < (b)) ? (a) : (b))
#define NEG(v)				( (v) = -(v) )

#endif // __T3DCOMMONS_H__
