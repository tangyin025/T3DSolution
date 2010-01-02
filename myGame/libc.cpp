
#include "stdafx.h"
#include <cstdio>
#include <cassert>
#include <crtdbg.h>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include "libc.h"
#include "myWindow.h"

#define FAILED_EXCEPT(expr) \
	if(!(expr) ) { /*throw std::exception(#expr);*/ T3D_CUSEXCEPT(_T(#expr)); }

char * asprintf(const char * format, ...)
{
	static const size_t def_size = 512;
	static const size_t inc_size = 512;

	assert(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	char * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_EXCEPT(NULL != (buffer = (char *)realloc(buffer, new_size * sizeof(char))));

		va_list args;
		va_start(args, format);
		ret_size = vsnprintf(buffer, new_size, format, args);
		va_end(args);
	}

	return buffer;
}

wchar_t * aswprintf(const wchar_t * format, ...)
{
	static const size_t def_size = 512;
	static const size_t inc_size = 512;

	assert(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	wchar_t * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_EXCEPT(NULL != (buffer = (wchar_t *)realloc(buffer, new_size * sizeof(wchar_t))));

		va_list args;
		va_start(args, format);
		ret_size = vswprintf(buffer, new_size, format, args);
		va_end(args);
	}

	return buffer;
}

char * avsprintf(const char * format, va_list args)
{
	static const size_t def_size = 512;
	static const size_t inc_size = 512;

	assert(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	char * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_EXCEPT(NULL != (buffer = (char *)realloc(buffer, new_size * sizeof(char))));

		ret_size = vsnprintf(buffer, new_size, format, args);
	}

	return buffer;
}

wchar_t * avswprintf(const wchar_t * format, va_list args)
{
	static const size_t def_size = 512;
	static const size_t inc_size = 512;

	assert(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	wchar_t * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_EXCEPT(NULL != (buffer = (wchar_t *)realloc(buffer, new_size * sizeof(wchar_t))));

		ret_size = vswprintf(buffer, new_size, format, args);
	}

	return buffer;
}

std::basic_string<char> str_printf(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	boost::scoped_ptr<char> ptr(avsprintf(format, args));
	va_end(args);

	return std::basic_string<char>(ptr.get());
}

std::basic_string<wchar_t> str_printf(const wchar_t * format, ...)
{
	va_list args;
	va_start(args, format);
	boost::scoped_ptr<wchar_t> ptr(avswprintf(format, args));
	va_end(args);

	return std::basic_string<wchar_t>(ptr.get());
}

std::basic_string<wchar_t> mstringToWstring(const char * str)
{
	int wlen;
	if(0 == (wlen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, NULL, 0)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	boost::scoped_array<wchar_t> ptr(new wchar_t[wlen]);
	if(0 == (wlen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, ptr.get(), wlen)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	return std::basic_string<wchar_t>(ptr.get());
}

std::basic_string<char> wstringToMstring(const wchar_t * str)
{
	int wlen;
	if(0 == (wlen = WideCharToMultiByte(CP_ACP, WC_SEPCHARS, str, -1, NULL, 0, NULL, NULL)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	boost::scoped_array<char> ptr(new char[wlen]);
	if(0 == (wlen = WideCharToMultiByte(CP_ACP, WC_SEPCHARS, str, -1, ptr.get(), wlen, NULL, NULL)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	return std::basic_string<char>(ptr.get());
}
