/*
 * File: T3DLIB/t3dCommons.h
 */

#ifndef __T3DCOMMONS_H__
#define __T3DCOMMONS_H__

#define T3DLIB_DOUBLE_PRECISION	0
#define T3DLIB_FIXP12_ZBUFFER		0

#ifdef T3DLIB_EXPORTS
#define T3DLIB_API __declspec(dllexport)
#else
#define T3DLIB_API __declspec(dllimport)
#endif

#if T3DLIB_DOUBLE_PRECISION
typedef double	REAL;
#else
typedef float	REAL;
#endif

#define MAX_BUFFER_SIZE				MAX_PATH
#define TEXT_BKMODE_OPAQUE			OPAQUE
#define TEXT_BKMODE_TRANSPARENT		TRANSPARENT
#define INIT_ZERO(s)				memset(&(s), 0, sizeof(s))
#define SAFE_FREE(p)				{ if(p != NULL) { free(p);		p = NULL; } }
#define SAFE_DELETE(p)				{ if(p != NULL) { delete p;		p = NULL; } }
#define SAFE_DELETES(p)				{ if(p != NULL) { delete[] p;	p = NULL; } }
#define SAFE_FCLOSE(p)				{ if(p != NULL) { fclose(p);	p = NULL; } }
#define SAFE_RELEASE(p)				{ if(p != NULL) { p->Release();	p = NULL; } }
#define ON_ERROR_GOTO(e)			{ Set_Last_Error((e), __FILE__, __LINE__) ; goto ON_ERROR; }

#define SET_BIT(byte, option)		((byte) |= (option))
#define RESET_BIT(byte, option)		((byte) &= ~(option))

#define SFORMAT0(pbuf, sfmt)						(sprintf((pbuf), (sfmt)), pbuf)
#define SFORMAT1(pbuf, sfmt, arg1)					(sprintf((pbuf), (sfmt), arg1), pbuf)
#define SFORMAT2(pbuf, sfmt, arg1, arg2)			(sprintf((pbuf), (sfmt), arg1, arg2), pbuf)
#define SFORMAT3(pbuf, sfmt, arg1, arg2, arg3)		(sprintf((pbuf), (sfmt), arg1, arg2, arg3), pbuf)

#ifdef _DEBUG
#define _WARNING(e)									{ if(e) { _RPT0(_CRT_WARN, "warn: " #e "\n"); } }
#define _CTOR_DECLARE(class_name)					class_name()
#define _CTOR_IMPLEMENT(class_name)					class_name::class_name() { memset(this, 0xFF, sizeof(*this)); }
#define _CTOR_IMPLEMENT_T1(class_name, type_name1) \
													template<typename type_name1> class_name<type_name1>::class_name() { memset(this, 0, sizeof(*this)); }
#define _DTOR_DECLARE(class_name)					~class_name()
#define _DTOR_IMPLEMENT(class_name, destroy_func)	class_name::~class_name() { destroy_func(this); }
#define _DTOR_IMPLEMENT_W1(class_name, destroy_func, warn_memb1) \
													class_name::~class_name() { _WARNING(warn_memb1 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_W2(class_name, destroy_func, warn_memb1, warn_memb2) \
													class_name::~class_name() { _WARNING(warn_memb1 != NULL); _WARNING(warn_memb2 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_W3(class_name, destroy_func, warn_memb1, warn_memb2, warn_memb3) \
													class_name::~class_name() { _WARNING(warn_memb1 != NULL); _WARNING(warn_memb2 != NULL); _WARNING(warn_memb3 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_T1(class_name, destroy_func) \
													template<typename type_name1> class_name<type_name1>::~class_name() { destroy_func(this); }
#define _DTOR_IMPLEMENT_T1_W1(class_name, type_name1, destroy_func, warn_memb1) \
													template<typename type_name1> class_name<type_name1>::~class_name() { _WARNING(warn_memb1 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_T1_W2(class_name, type_name1, destroy_func, warn_memb1, warn_memb2) \
													template<typename type_name1> class_name<type_name1>::~class_name() { _WARNING(warn_memb1 != NULL); _WARNING(warn_memb2 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_T1_W3(class_name, type_name1, destroy_func, warn_memb1, warn_memb2, warn_memb3) \
													template<typename type_name1> class_name<type_name1>::~class_name() { _WARNING(warn_memb1 != NULL); _WARNING(warn_memb2 != NULL); _WARNING(warn_memb3 != NULL); destroy_func(this); }
#else
#define _WARNING(e)
#define _CTOR_DECLARE(class_name)
#define _CTOR_IMPLEMENT(class_name)
#define _CTOR_IMPLEMENT_T1(class_name, type_name1)
#define _DTOR_DECLARE(class_name)
#define _DTOR_IMPLEMENT(class_name, destroy_func)
#define _DTOR_IMPLEMENT_W1(class_name, destory_func, warn_memb1)
#define _DTOR_IMPLEMENT_W2(class_name, destory_func, warn_memb1, warn_memb2)
#define _DTOR_IMPLEMENT_W3(class_name, destory_func, warn_memb1, warn_memb2, warn_memb3)
#define _DTOR_IMPLEMENT_T1(class_name, destroy_func)
#define _DTOR_IMPLEMENT_T1_W1(class_name, type_name1, destroy_func, warn_memb1)
#define _DTOR_IMPLEMENT_T1_W2(class_name, type_name1, destroy_func, warn_memb1, warn_memb2)
#define _DTOR_IMPLEMENT_T1_W3(class_name, type_name1, destroy_func, warn_memb1, warn_memb2, warn_memb3)
#endif

#define SWAP(a, b, temp)	{ temp = a; a = b; b = temp; }
#define MAX(a, b)			(((a) > (b)) ? (a) : (b))
#define MIN(a, b)			(((a) < (b)) ? (a) : (b))
#define NEG(v)				( (v) = -(v) )

T3DLIB_API char * Set_Last_Error(const char * pmessage, const char * pfile, const int line);

extern __declspec(thread) char				gbuffer[MAX_BUFFER_SIZE];

#endif // __T3DCOMMONS_H__
