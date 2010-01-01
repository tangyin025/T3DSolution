
#ifndef __T3DCOMMON_H__
#define __T3DCOMMON_H__

#include <cfloat>
#include <algorithm>
#include <string>

//#define T3DLIB_DOUBLE_PRECISION

#ifdef _DEBUG
#define T3DLIB_REPORT_PRECISION_ERROR
#endif

namespace t3d
{
	#define EPSILON_E3			(1.0e-3)
	#define EPSILON_E4			(1.0e-4)
	#define EPSILON_E5			(1.0e-5)
	#define EPSILON_E6			(1.0e-6)
	#define EPSILON_E12			(1.0e-12)

#ifdef T3DLIB_DOUBLE_PRECISION
	typedef double				real;
	#define REAL_MIN			DBL_MIN
	#define REAL_MAX			DBL_MAX
	#define REAL_ZERO_LIMIT		EPSILON_E12
#else
	typedef float				real;
	#define REAL_MIN			FLT_MIN
	#define REAL_MAX			FLT_MAX
	#define REAL_ZERO_LIMIT		EPSILON_E6
#endif

#ifdef _UNICODE
	typedef wchar_t				charT;
	#define	__T(x)				L##x
	#define _T(x)				__T(x)
#else
	typedef char				charT;
	#define _T(x)				x
#endif

	#define SAFE_FREE(p)		if(p != NULL) { free(p);		p = NULL; }
	#define SAFE_DELETE(p)		if(p != NULL) { delete p;		p = NULL; }
	#define SAFE_DELETE_ARR(p)	if(p != NULL) { delete[] p;		p = NULL; }
	#define SAFE_FCLOSE(p)		if(p != NULL) { fclose(p);		p = NULL; }
	#define SAFE_RELEASE(p)		if(p != NULL) { p->Release();	p = NULL; }

	typedef unsigned short		uint16;
	typedef unsigned int		uint32;

	typedef int					fixp16;
	typedef int					fixp28;

	#define FIXP16_MIN			SHRT_MIN
	#define FIXP16_MAX			SHRT_MAX

	#define FIXP28_MIN			-8
	#define FIXP28_MAX			7

	class Exception
	{
	public:
		virtual std::basic_string<charT> what(void) const throw() = 0;

	public:
		Exception(const std::basic_string<charT> & file, int line);

		virtual ~Exception(void);

		std::basic_string<charT> getFullDesc(void) const throw();

	protected:
		std::basic_string<charT> m_file;

		int m_line;
	};

	class CustomException : public Exception
	{
	public:
		CustomException(const std::basic_string<charT> & file, int line, const std::basic_string<charT> & info);

	public:
		std::basic_string<charT> what(void) const throw();

	protected:
		std::basic_string<charT> m_info;
	};

#define T3D_CUSEXCEPT(x) { throw t3d::CustomException(_T(__FILE__), __LINE__, (x)); }

	template <typename elem_t>
	elem_t min(const elem_t & e0, const elem_t & e1, const elem_t & e2)
	{
		return std::min(e0, std::min(e1, e2));
	}

	template <typename elem_t>
	elem_t max(const elem_t & e0, const elem_t & e1, const elem_t & e2)
	{
		return std::max(e0, std::max(e1, e2));
	}

	template <typename elem_t>
	elem_t limit(const elem_t & value, const elem_t & min, const elem_t & max)
	{
		return std::min(max, std::max(min, value));
	}
}

#define NOMINMAX

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#endif // __T3DCOMMON_H__
