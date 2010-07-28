
#include <libc.h>
#include <myGame.h>
#include <myUtility.h>
#include <myPhysics.h>
#include <myCollision.h>
#include <myScene.h>

using t3d::charT;

using t3d::real;

#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
#endif
