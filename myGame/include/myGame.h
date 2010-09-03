
#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "myCommon.h"
#include <t3dlib1.h>
#include <t3dlib2.h>
#include <t3dlib3.h>
#include <t3dlib6.h>
#include "mySingleton.h"
#include "myWindow.h"
#include "myMath.h"
#include "myResource.h"
#include <list>
#include <atltypes.h>
#include <boost/shared_ptr.hpp>

namespace my
{
	class ErrorListener
	{
	public:
		virtual ~ErrorListener(void);

		virtual void onReport(const std::basic_string<charT> & info) = 0;
	};

	class ErrorReporter : public Singleton<ErrorReporter>
	{
	public:
		ErrorReporter(void);

		virtual ~ErrorReporter(void);

	public:
		void addErrorListener(ErrorListener * listener);

		void report(const std::basic_string<charT> & info);

	protected:
		typedef std::list<ErrorListener *> ErrorListenerPList;

		ErrorListenerPList m_listenerList;
	};

	typedef boost::shared_ptr<ErrorReporter> ErrorReporterPtr;

//#ifdef _DEBUG
#define REPORT_ERROR(e) my::ErrorReporter::getSingleton().report(e);
//#else
//#define REPORT_ERROR(e)
//#endif

	class ColorConversion
	{
	protected:
		static ColorConversion * s_ptr;

	public:
		static ColorConversion * getSingletonPtr(void)
		{
			_ASSERT(NULL != s_ptr); return s_ptr;
		}

		static ColorConversion & getSingleton(void)
		{
			return * getSingletonPtr();
		}

	public:
		ColorConversion(void);

		virtual ~ColorConversion(void);

	public:
		virtual uint32 convertColor(const my::Color & color) = 0;

		virtual uint32 convertColor(const t3d::Vec4<int> & color) = 0;

		virtual my::ImagePtr convertImage(const my::ImagePtr image) = 0;
	};

	typedef boost::shared_ptr<ColorConversion> ColorConversionPtr;

	class ColorConversion16 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::ImagePtr convertImage(const my::ImagePtr image);
	};

	class ColorConversion32 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::ImagePtr convertImage(const my::ImagePtr image);
	};

	class GameWnd : public Window
	{
	public:
		BEGIN_MSG_MAP(GameWnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		END_MSG_MAP()

		LRESULT OnPaint(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	};

	class Game : public Application
	{
	public:
		enum SCREEN_MODE
		{
			SCREEN_MODE_WINDOWED = 0,
			SCREEN_MODE_FULLSCREEN16,
			SCREEN_MODE_FULLSCREEN32,
		};

	public:
		static Game * getSingletonPtr(void)
		{
			return dynamic_cast<Game *>(my::Application::getSingletonPtr());
		}

		static Game & getSingleton(void)
		{
			return * getSingletonPtr();
		}

	public:
		ErrorReporterPtr m_errorRpt;

		ResourceMgrPtr m_resourceMgr;

		WindowPtr m_wnd;

		t3d::DDrawPtr m_ddraw;

		//t3d::DDSurfacePtr m_primSurface;

		//CRect m_primSurfaceRect;

		t3d::DDSurfacePtr m_backSurface;

		CRect m_backSurfaceRect;

		t3d::DInputPtr m_dinput;

		t3d::DSoundPtr m_dsound;

		t3d::DIKeyboardPtr m_keyboard;

		t3d::DIMousePtr m_mouse;

		DDPIXELFORMAT m_ddpf;

		t3d::RenderContextPtr m_rc;

		ColorConversionPtr m_cc;

		t3d::ZBufferPtr m_zbuff;

	public:
		Game(void);

		~Game(void);

	public:
		WindowPtr newWindow(void);

		bool prepare(const Config & cfg);

		//int run(LPTSTR lpCmdLine);

		int run(const Config & cfg);

		void onIdle(void);

	public:
		virtual bool onInit(const Config & cfg);

		virtual bool onFrame(void);

		virtual void onShutdown(void);
	};
}

#endif // __MYGAME_H__
