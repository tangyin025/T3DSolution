
#include "stdafx.h"
#include <cstdio>
#include <stdarg.h>
#include <crtdbg.h>
#include "libc.h"
#include "myWindow.h"

#define FAILED_CUSEXCEPT(expr) { if( !(expr) ) T3D_CUSEXCEPT( _T(#expr) ) }

char * asprintf(const char * format, ...)
{
	static const size_t def_size = 512;
	static const size_t inc_size = 512;

	_ASSERT(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	char * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_CUSEXCEPT(NULL != (buffer = (char *)realloc(buffer, new_size * sizeof(char))));

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

	_ASSERT(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	wchar_t * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_CUSEXCEPT(NULL != (buffer = (wchar_t *)realloc(buffer, new_size * sizeof(wchar_t))));

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

	_ASSERT(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	char * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_CUSEXCEPT(NULL != (buffer = (char *)realloc(buffer, new_size * sizeof(char))));

		ret_size = vsnprintf(buffer, new_size, format, args);
	}

	return buffer;
}

wchar_t * avswprintf(const wchar_t * format, va_list args)
{
	static const size_t def_size = 512;
	static const size_t inc_size = 512;

	_ASSERT(inc_size <= def_size);
	size_t new_size = def_size - inc_size;
	size_t ret_size = def_size;
	wchar_t * buffer = NULL;

	while(ret_size >= new_size)
	{
		new_size += inc_size;
		FAILED_CUSEXCEPT(NULL != (buffer = (wchar_t *)realloc(buffer, new_size * sizeof(wchar_t))));

		ret_size = vswprintf(buffer, new_size, format, args);
	}

	return buffer;
}

std::basic_string<char> str_printf(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	std::basic_string<char> ret;
	int nLen;
	for(ret.resize(512); -1 == (nLen = vsnprintf(&ret[0], ret.size(), format, args)); ret.resize(ret.size() + 512))
	{
	}
	va_end(args);

	ret.resize(nLen); // NOTE: not include the terminating null !
	return ret;
}

std::basic_string<wchar_t> str_printf(const wchar_t * format, ...)
{
	va_list args;
	va_start(args, format);
	std::basic_string<wchar_t> ret;
	int nLen;
	for(ret.resize(512); -1 == (nLen = vswprintf(&ret[0], ret.size(), format, args)); ret.resize(ret.size() + 512))
	{
	}
	va_end(args);

	ret.resize(nLen);
	return ret;
}

std::basic_string<wchar_t> mstringToWString(const std::basic_string<char> & mstr)
{
	int nLen;
	if(0 == (nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, mstr.c_str(), -1, NULL, 0)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	std::basic_string<wchar_t> ret;
	ret.resize(nLen - 1);
	if(0 == (nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, mstr.c_str(), -1, &ret[0], nLen)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	ret.resize(nLen - 1);
	return ret;
}

std::basic_string<char> wstringToMString(const std::basic_string<wchar_t> & wstr)
{
	int nLen;
	if(0 == (nLen = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_SEPCHARS, wstr.c_str(), -1, NULL, 0, NULL, NULL)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	std::basic_string<char> ret;
	ret.resize(nLen - 1);
	if(0 == (nLen = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_SEPCHARS, wstr.c_str(), -1, &ret[0], nLen, NULL, NULL)))
	{
		T3D_WINEXCEPT(::GetLastError());
	}

	ret.resize(nLen - 1);
	return ret;
}
