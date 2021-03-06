
#ifndef __MYCOMMON_H__
#define __MYCOMMON_H__

#include <t3dCommon.h>

#ifndef VERIFY
#ifdef _DEBUG
#define VERIFY(expr) _ASSERT( expr )
#else
#define VERIFY(expr) expr
#endif
#endif

namespace my
{
	using t3d::charT;

	using t3d::real;

	using t3d::uint16;

	using t3d::uint32;

	using t3d::fixp16;

	using t3d::fixp28;
}

#endif // __MYCOMMON_H__
