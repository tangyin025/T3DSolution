
#include "stdafx.h"
#include "MyDialog.h"

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// check memory leak
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	MyDialog dlg;
	dlg.doModel();
	return 0;
}
