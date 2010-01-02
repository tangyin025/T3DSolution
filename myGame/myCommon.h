
#ifndef __MYCOMMON_H__
#define __MYCOMMON_H__
//
//#ifdef MYGAME_EXPORTS
//#define MYGAME_API __declspec(dllexport)
//#else
//#define MYGAME_API __declspec(dllimport)
//#endif

#include "t3dCommon.h"

namespace my
{
	using t3d::charT;

	using t3d::real;

	using t3d::uint16;

	using t3d::uint32;

	using t3d::fixp16;

	using t3d::fixp28;
}

//#define FREEIMAGE_LIB

//#define BOOST_ALL_NO_LIB
//
//#pragma warning(disable: 4510) // warning C4510: 'std::_List_nod<_Ty,_Alloc>::_Node' : default constructor could not be generated
//
//#pragma warning(disable: 4610) // warning C4610: struct 'std::_List_nod<_Ty,_Alloc>::_Node' can never be instantiated - user defined constructor required
//
//#pragma warning(disable: 4819) //warning C4819: The file contains a character that cannot be represented in the current code page (932). Save the file in Unicode format to prevent data loss
//
//#pragma warning(disable: 4996) //warning C4996: 'vsnprintf': This function or variable may be unsafe. Consider using vsnprintf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

#endif // __MYCOMMON_H__
