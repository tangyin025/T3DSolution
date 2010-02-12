
#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "myCommon.h"
#include <t3dlib1.h>
#include <t3dlib2.h>
#include <t3dlib3.h>
#include <t3dlib6.h>
#include "myWindow.h"
#include "myMath.h"
#include "myResource.h"
#include <list>
#include <atltypes.h>
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
			_ASSERT(NULL != s_ptr); return * s_ptr;
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
		static ColorConversion & getSingleton(void)
		{
			_ASSERT(NULL != s_ptr); return * s_ptr;
		}

	public:
		ColorConversion(void);

		virtual ~ColorConversion(void);

	public:
		virtual uint32 convertColor(const my::Color & color) = 0;

		virtual uint32 convertColor(const t3d::Vec4<int> & color) = 0;

		virtual my::ImagePtr convertImage(const my::Image * image) = 0;
	};

	typedef boost::shared_ptr<ColorConversion> ColorConversionPtr;

	class ColorConversion16 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::ImagePtr convertImage(const my::Image * image);
	};

	class ColorConversion32 : public ColorConversion
	{
	public:
		uint32 convertColor(const my::Color & color);

		uint32 convertColor(const t3d::Vec4<int> & color);

		my::ImagePtr convertImage(const my::Image * image);
	};

	class Game : public Application
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
			CONFIG_DESC(DWORD _width, DWORD _height, int _smode);

		public:
			DWORD width;
			DWORD height;
			int smode;
		};

	protected:
		ErrorReporterPtr m_errorRpt;

		ResourceMgrPtr m_resourceMgr;

		Window * m_pwnd;

		t3d::DDrawPtr m_ddraw;

		//t3d::DDSurfacePtr m_sprim;

		//CRect m_rprim;

		t3d::DDSurfacePtr m_sback;

		CRect m_rback;

		t3d::RenderContextPtr m_rc;

		ColorConversionPtr m_cc;

		t3d::ZBufferPtr m_zbuff;

		t3d::DInputPtr m_dinput;

		t3d::DSoundPtr m_dsound;

		t3d::DIKeyboardPtr m_keyboard;

		t3d::DIMousePtr m_mouse;

	public:
		Game(void);

		~Game(void);

	public:
		bool prepare(const CONFIG_DESC & cfg);

		void bltBackSurfaceToPrimary(void);

		//int run(LPTSTR lpCmdLine);

		int run(const CONFIG_DESC & cfg = CONFIG_DESC(800, 600, SM_WINDOWED));

		void onIdle(void);

	public:
		virtual bool onInit(void) { return true; }

		virtual bool onFrame(void) { return true; }

		virtual void onShutdown(void) {}
	};
}

#endif // __MYGAME_H__