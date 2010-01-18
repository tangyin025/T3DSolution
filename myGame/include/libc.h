
#ifndef __LIBC_H__
#define __LIBC_H__

#include "myCommon.h"
#include <stdarg.h>
#include <string>

#if _MSC_VER < 1400
#define vsnprintf _vsnprintf
#define vswprintf _vsnwprintf
#endif

char * asprintf(const char * format, ...);

wchar_t * aswprintf(const wchar_t * format, ...);

char * avsprintf(const char * format, va_list args);

wchar_t * avswprintf(const wchar_t * format, va_list args);

std::basic_string<char> str_printf(const char * format, ...);

std::basic_string<wchar_t> str_printf(const wchar_t * format, ...);

std::basic_string<wchar_t> mstringToWstring(const char * str);

std::basic_string<char> wstringToMstring(const wchar_t * str);

#endif // __LIBC_H__
