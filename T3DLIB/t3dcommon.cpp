
#include "stdafx.h"
#include "t3dcommon.h"

#include <cassert>
#include <sstream>

namespace t3d
{
	//Exception::Exception(const std::basic_string<charT> info)
	//	: m_info(info), m_file(_T("unknown")), m_line(-1)
	//{
	//	assert(false);
	//}

	//Exception::Exception(const std::basic_string<charT> info, const std::basic_string<charT> file, int line)
	//	: m_info(info), m_file(file), m_line(line)
	//{
	//}

	//Exception::~Exception()
	//{
	//}

	//std::basic_string<charT> Exception::what(void) const
	//{
	//	return m_info;
	//}

	//std::basic_string<charT> Exception::getFullDesc(void) const
	//{
	//	std::basic_stringstream<charT> osstr;
	//	osstr << m_file << _T(" (") << m_line << _T("): ") << what();
	//	return osstr.str();
	//}

	Exception::Exception(const std::basic_string<charT> & file, int line)
		: m_file(file)
		, m_line(line)
	{
	}

	Exception::~Exception(void)
	{
	}

	std::basic_string<charT> Exception::getFullDesc(void) const
	{
		std::basic_stringstream<charT> osstr;
		osstr << m_file << _T(" (") << m_line << _T("): ") << what();
		return osstr.str();
	}

	CustomException::CustomException(const std::basic_string<charT> & file, int line, const std::basic_string<charT> & info)
		: Exception(file, line)
		, m_info(info)
	{
	}

	std::basic_string<charT> CustomException::what(void) const throw()
	{
		return m_info;
	}
}
