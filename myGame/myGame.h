
#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "myCommon.h"
#include <t3dlib1.h>
#include <t3dlib2.h>
#include <t3dlib3.h>
#include <t3dlib6.h>
#include "myWindow.h"
#include "myMath.h"
#include "myImage.h"
#include "myResource.h"
#include <list>
#include <boost/shared_array.hpp>

namespace my
{
	class ErrorListener
	{
	public:
		virtual ~ErrorListener(void);

		virtual void onReport(const std::basic_string<charT> & info) = 0;
	};

	class ErrorReporter
	{
	protected:
		static ErrorReporter * s_ptr;

	public:
		static ErrorReporter & getSingleton(void)
		{
			assert(NULL != s_ptr); return * s_ptr;
		}

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
		static ColorConversion & getSingleton(void)
		{
			assert(NULL != s_ptr); return * s_ptr;
		}

	public:
		ColorConversion(void);

		virtual ~ColorConversion(void);

	public:
		virtual uint32 convertColor(const my::Color & color) = 0;

		virtual uint32 convertColor(const t3d::Vec4<int> & color) = 0;

		virtual my::ImagePtr convertImage(const my::Image & image) = 0;
	};

	typedef boost::shared_ptr<ColorConversion> ColorConversionPtr;

	class ColorConversion16 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::ImagePtr convertImage(const my::Image & image);
	};

	class ColorConversion32 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::ImagePtr convertImage(const my::Image & image);
	};

	typedef boost::shared_ptr<ErrorReporter> ErrorReporterPtr;

	//typedef boost::shared_ptr<t3d::DDraw> DDrawPtr;

	//typedef boost::shared_ptr<t3d::DDraw::Surface> DDrawSurfacePtr;

	//typedef boost::shared_ptr<t3d::DDraw::Clipper> DDrawClipperPtr;

	//typedef boost::shared_ptr<t3d::DInput> DInputPtr;

	//typedef boost::shared_ptr<t3d::DInput::Keyboard> DInputKeyboardPtr;

	//typedef boost::shared_ptr<t3d::DInput::Mouse> DInputMousePtr;

	//typedef boost::shared_ptr<t3d::DInput::Joystick> DInputJoystickPtr;

	//typedef boost::shared_ptr<t3d::DSound> DSoundPtr;

	//typedef boost::shared_ptr<t3d::DSound::Buffer> DSoundBufferPtr;

	typedef boost::shared_ptr<t3d::RenderContext> RenderContextPtr;

	typedef boost::shared_array<fixp28> ZBufferPtr;

	class GameBase : public Application
	{
	public:
		enum SCREEN_MODE
		{
			SM_WINDOWED = 0,
			SM_FULLSCREEN16 = 16,
			SM_FULLSCREEN32 = 32,
		};

		struct CONFIG_DESC
		{
		public:
			CONFIG_DESC(DWORD _width = 800, DWORD _height = 600, int _smode = SM_WINDOWED);

		public:
			DWORD width;
			DWORD height;
			int smode;
		};

	protected:
		ErrorReporterPtr m_errorRpt;

		ResourceMgrPtr m_resourceMgr;

		Window * m_win;

		t3d::DDrawPtr m_ddraw;

		t3d::DDSurfacePtr m_sprim;

		t3d::DDSurfacePtr m_sback;

		RECT m_rprim;

		RECT m_rback;

		RenderContextPtr m_rc;

		ColorConversionPtr m_cc;

		ZBufferPtr m_zbuff;

		DWORD m_zbuffPitch;

	public:
		GameBase(HINSTANCE hinst);

		~GameBase(void);

	public:
		void prepare(const CONFIG_DESC & cfg);

		void prepareConfig(const CONFIG_DESC & cfg);

		void bltBackSurfaceToPrimary(void);

		void fillBackSurface(LPRECT lpRect, const t3d::Vec4<int> & color = my::Vec4<int>(197, 197, 197));

		void clearZBuffer(LPRECT lpRect, t3d::fixp28 value = 0);
	};

	class Game : public GameBase, public Application::IdleListener
	{
	protected:
		t3d::DInputPtr m_dinput;

		t3d::DSoundPtr m_dsound;

		t3d::DIKeyboardPtr m_keyboard;

		t3d::DIMousePtr m_mouse;

	public:
		Game(HINSTANCE hinst = Application::getModuleHandle());

		~Game(void);

	public:
		virtual bool onInit(void) = 0;

		virtual bool onFrame(void) = 0;

		virtual void onShutdown(void) = 0;

	public:
		//int run(LPTSTR lpCmdLine);

		int run(const CONFIG_DESC & cfg = Game::CONFIG_DESC());

		void nodifyIdle(void);
	};
}

#endif // __MYGAME_H__
