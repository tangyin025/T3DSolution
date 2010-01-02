
#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "myCommon.h"

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include "myWindow.h"
#include "myResource.h"
#include "myMath.h"
#include "myImage.h"
#include "t3dlib1.h"
#include "t3dlib2.h"
#include "t3dlib6.h"

namespace my
{
	class MYGAME_API ErrorListener
	{
	public:
		virtual ~ErrorListener(void);

		virtual void onReport(const std::basic_string<charT> & info) = 0;
	};

	class MYGAME_API ErrorReporter
	{
	protected:
		static ErrorReporter * s_ptr;

	public:
		static inline ErrorReporter & getSingleton(void)
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

	class MYGAME_API ColorConversion
	{
	protected:
		static ColorConversion * s_ptr;

	public:
		static inline ColorConversion & getSingleton(void)
		{
			assert(NULL != s_ptr); return * s_ptr;
		}

	public:
		ColorConversion(void);

		virtual ~ColorConversion(void);

	public:
		virtual uint32 convertColor(const my::Color & color) = 0;

		virtual uint32 convertColor(const t3d::Vec4<int> & color) = 0;

		virtual my::Image * convertImage(const my::Image & image) = 0;
	};

	typedef boost::shared_ptr<ColorConversion> ColorConversionPtr;

	class MYGAME_API ColorConversion16 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::Image * convertImage(const my::Image & image);
	};

	class MYGAME_API ColorConversion32 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::Image * convertImage(const my::Image & image);
	};

	typedef boost::shared_ptr<ErrorReporter> ErrorReporterPtr;

	typedef boost::shared_ptr<t3d::DDraw> DDrawPtr;

	typedef boost::shared_ptr<t3d::DDraw::Surface> DDrawSurfacePtr;

	typedef boost::shared_ptr<t3d::DDraw::Clipper> DDrawClipperPtr;

	typedef boost::shared_ptr<t3d::DInput> DInputPtr;

	typedef boost::shared_ptr<t3d::DInput::Keyboard> DInputKeyboardPtr;

	typedef boost::shared_ptr<t3d::DInput::Mouse> DInputMousePtr;

	typedef boost::shared_ptr<t3d::DInput::Joystick> DInputJoystickPtr;

	typedef boost::shared_ptr<t3d::DSound> DSoundPtr;

	typedef boost::shared_ptr<t3d::DSound::Buffer> DSoundBufferPtr;

	typedef boost::shared_ptr<t3d::RenderContext> RenderContextPtr;

	typedef boost::shared_array<fixp28> ZBufferPtr;

	class MYGAME_API GameBase : public Application
	{
	public:
		enum SCREEN_MODE
		{
			SM_WINDOWED = 0,
			SM_FULLSCREEN16 = 16,
			SM_FULLSCREEN32 = 32,
		};

		struct MYGAME_API CONFIG_DESC
		{
		public:
			CONFIG_DESC(DWORD _width = 800, DWORD _height = 600, int _smode = SM_WINDOWED);

		public:
			DWORD width;
			DWORD height;
			int smode;
		};

	public:
		ErrorReporterPtr m_errorRpt;

		ResourceMgrPtr m_resourceMgr;

		Window * m_win;

		DDrawPtr m_ddraw;

		DDrawSurfacePtr m_sprim;

		DDrawSurfacePtr m_sback;

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

		void fillBackSurface(const RECT & rect, const t3d::Vec4<int> & color = my::Vec4<int>(197, 197, 197));

		void clearZBuffer(const RECT & rect, t3d::fixp28 value = 0);
	};

	class MYGAME_API Game : public GameBase, public Application::IdleListener
	{
	protected:
		DInputPtr m_dinput;

		DSoundPtr m_dsound;

		DInputKeyboardPtr m_keyboard;

		DInputMousePtr m_mouse;

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
