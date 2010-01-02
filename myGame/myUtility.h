
#ifndef __MYUTILITY_H__
#define __MYUTILITY_H__

#include "myCommon.h"
#include <t3dlib1.h>
#include <t3dlib2.h>
#include <t3dlib6.h>
#include <map>
#include <deque>
#include <stack>
#include <boost/shared_ptr.hpp>
#include "myMath.h"
#include "myResource.h"
#include "mySkeleton.h"
#include "myCollision.h"

namespace my
{
	// /////////////////////////////////////////////////////////////////////////////////////
	// FPSManager
	// /////////////////////////////////////////////////////////////////////////////////////

	class FPSManager
	{
	public:
		FPSManager(void);

	public:
		void start(void);

		void addFrame(void);

		real getFPS(void);

		DWORD getLastUpdateTime(void);

	protected:
		DWORD interval_time;
		DWORD last_time;
		DWORD past_time;
		DWORD past_frames;
		real m_fps;
	};

	typedef boost::shared_ptr<FPSManager> FPSManagerPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// Timer
	// /////////////////////////////////////////////////////////////////////////////////////

	class Timer
	{
	public:
		Timer(void);

		~Timer(void);

	public:
		bool isPaused(void);

		void start(void);

		void pause(void);

		double getElapsedTime(void);

		double getLastUpdateTime(void);

	private:
		bool m_paused;

		double m_frequency;

		LARGE_INTEGER m_lastTime;
	};

	typedef boost::shared_ptr<Timer> TimerPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// EularCamera
	// /////////////////////////////////////////////////////////////////////////////////////

	class EularCamera
	{
	public:
		static t3d::Vec4<real> & updateVec4OnMovFront(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovFrontRight(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovRight(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovRightBack(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovBack(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovBackLeft(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovLeft(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovLeftFront(t3d::Vec4<real> & vres, real angle, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovUp(t3d::Vec4<real> & vres, real scaler);

		static t3d::Vec4<real> & updateVec4OnMovDown(t3d::Vec4<real> & vres, real scaler);

		static t3d::Vec4<real> buildMovOffset(t3d::DIKeyboard * keyboard, real angle, real scaler);

		static t3d::Vec4<real> buildRotOffset(t3d::DIMouse * mouse);

	public:
		EularCamera(void);

		~EularCamera(void);

	public:
		void setDefaultPosition(const t3d::Vec4<real> & pos);

		const t3d::Vec4<real> & getDefaultPosition(void) const;

		void setDefaultRotation(const t3d::Vec4<real> & rot);

		const t3d::Vec4<real> & getDefaultRotation(void) const;

		void setPosition(const t3d::Vec4<real> & pos);

		void addPosition(const t3d::Vec4<real> & pos);

		const t3d::Vec4<real> & getPosition(void) const;

		void setRotation(const t3d::Vec4<real> & rot);

		void addRotation(const t3d::Vec4<real> & rot);

		const t3d::Vec4<real> & getRotation(void) const;

		void setPitch(real value);

		void addPitch(real value);

		real getPitch(void) const;

		void setYaw(real value);

		void addYaw(real value);

		real getYaw(void) const;

		void setRoll(real value);

		void addRoll(real value);

		real getRoll(void) const;

		void setMovSpeed(real speed);

		real getMovSpeed(void) const;

		void reset(void);

		void update(t3d::DIKeyboard * keyboard, t3d::DIMouse * mouse, real step_time);

	protected:
		t3d::Vec4<real> m_posDefault;

		t3d::Vec4<real> m_rotDefault;

		t3d::Vec4<real> m_pos;

		t3d::Vec4<real> m_rot;

		real m_movSpeed;
	};

	typedef boost::shared_ptr<EularCamera> EularCameraPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ConsoleSimulator
	// /////////////////////////////////////////////////////////////////////////////////////

	class ConsoleSimulator
	{
	//protected:
	public:
		int m_step;

		size_t m_maxLine;

		typedef std::deque</*const*/ std::basic_string<charT> > StringDeque; // *** stlport unsupport deque<const type>

		StringDeque m_lines;

	public:
		ConsoleSimulator(size_t maxLine = 5, int step = ::GetSystemMetrics(SM_CYMENU));

		~ConsoleSimulator(void);

		void report(const std::basic_string<charT> & info);

		void clear(void);

		virtual void draw(t3d::DDSurface * surface, int x, int y) const;
	};

	typedef boost::shared_ptr<ConsoleSimulator> ConsoleSimulatorPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// MenuSystem
	// /////////////////////////////////////////////////////////////////////////////////////

	class MenuItemArrow
	{
	protected:
		int m_width;

		int m_height;

	public:
		MenuItemArrow(int width = ::GetSystemMetrics(SM_CYMENU), int height = ::GetSystemMetrics(SM_CYMENU));

		void setWidth(int width);

		int getWidth(void) const;

		void setHeight(int height);

		int getHeight(void) const;

		void draw(t3d::DDSurface * surface, int x, int y) const;
	};

	class MenuItemCheck
	{
	protected:
		int m_width;

		int m_height;

	public:
		MenuItemCheck(int width = ::GetSystemMetrics(SM_CYMENU), int height = ::GetSystemMetrics(SM_CYMENU));

		void setWidth(int width);

		int getWidth(void) const;

		void setHeight(int height);

		int getHeight(void) const;

		void draw(t3d::DDSurface * surface, int x, int y) const;
	};

	class MenuItem
	{
	protected:
		MenuItemArrow m_arrow;

		MenuItemCheck m_check;

		std::basic_string<charT> m_text;

		int m_width;

		int m_height;

	public:
		MenuItem(const std::basic_string<charT> & text, int width, int height = ::GetSystemMetrics(SM_CYMENU));

		void setText(const std::basic_string<charT> & text);

		const std::basic_string<charT> & getText(void) const;

		void setWidth(int width);

		int getWidth(void) const;

		void setHeight(int height);

		int getHeight(void) const;

		void draw(t3d::DDSurface * surface, int x, int y, bool arrow = false, bool check = false) const;
	};

	class MenuItemNode;

	typedef boost::shared_ptr<MenuItemNode> MenuItemNodePtr;

	class Menu
	{
	public:
		enum MenuCheckType
		{
			SingleCheckType,
			MultiCheckType
		};

	protected:
		typedef std::vector<MenuItemNodePtr> MenuItemNodePtrList;

		MenuItemNodePtrList m_items;

		int m_width;

		MenuCheckType m_checkType;

	public:
		Menu(int width);

		size_t createMenuItemNode(const std::basic_string<charT> & itemText, int itemHeight = ::GetSystemMetrics(SM_CYMENU));

		MenuItemNodePtr getMenuItemNode(size_t item_i) const;

		MenuItemNodePtr getMenuItemNode(const std::basic_string<charT> & itemText) const;

		size_t getMenuItemNodeCount(void) const;

		int getWidth(void) const;

		int getHeight(void) const;

		void setCheckType(MenuCheckType checkType);

		MenuCheckType getCheckType(void) const;

		void singleCheckItemNode(size_t item_i);

		void draw(t3d::DDSurface * surface, int x, int y) const;
	};

	class MenuItemNode : public MenuItem
	{
	protected:
		Menu m_subMenu;

		bool m_checked;

	public:
		MenuItemNode(const std::basic_string<charT> & text, int width, int height = ::GetSystemMetrics(SM_CYMENU));

		Menu & getSubMenu(void);

		const Menu & getSubMenu(void) const;

		void setCheck(bool checked);

		bool getCheck(void) const;

		void draw(t3d::DDSurface * surface, int x, int y) const;
	};

	class MenuSystem : public Menu
	{
	protected:
		typedef std::vector<Menu *> PMenuStack;

		PMenuStack m_menuStack;

	public:
		MenuSystem(int width);

		void selectMenuItemNode(size_t item_i);

		void onKeyRelease(UINT vkcode);

		void draw(t3d::DDSurface * surface, int x, int y) const;
	};

	typedef boost::shared_ptr<MenuSystem> MenuSystemPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// Grid
	// /////////////////////////////////////////////////////////////////////////////////////

	class Grid
	{
	protected:
		t3d::VertexList m_axisList;

		t3d::VertexList m_gridList;

	public:
		Grid(
			real lengthAndWidth = 100,
			real gridLinesEvery = 10);

		~Grid(void);

		void drawZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & axisColor = my::Color(0.1f, 0.1f, 0.1f),
			const t3d::Vec4<real> & gridColor = my::Color(0.6f, 0.6f, 0.6f));
	};

	typedef boost::shared_ptr<Grid> GridPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// Material
	// /////////////////////////////////////////////////////////////////////////////////////

	class Material
	{
	public:
		t3d::Vec4<real> ambient;
		t3d::Vec4<real> diffuse;
		t3d::Vec4<real> specular;
		t3d::Vec4<real> emissive;

	public:
		Material(void);

		~Material(void);
	};

	typedef boost::shared_ptr<Material> MaterialPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ObjectBase
	// /////////////////////////////////////////////////////////////////////////////////////

	class ObjectBase
		: public t3d::VertexListContext
		, public t3d::NormalListContext
		, public t3d::UVListContext
	{
	public:
		ObjectBase(void);

		virtual ~ObjectBase(void);

	public:
		virtual size_t getTriangleCount(void) const = 0;

		virtual const t3d::Vec4<real> & getTriangleVertex0(size_t i) const = 0;

		virtual const t3d::Vec4<real> & getTriangleVertex1(size_t i) const = 0;

		virtual const t3d::Vec4<real> & getTriangleVertex2(size_t i) const = 0;

		virtual const t3d::Vec4<real> & getTriangleNormal0(size_t i) const = 0;

		virtual const t3d::Vec4<real> & getTriangleNormal1(size_t i) const = 0;

		virtual const t3d::Vec4<real> & getTriangleNormal2(size_t i) const = 0;

		virtual const t3d::Vec2<real> & getTriangleUV0(size_t i) const = 0;

		virtual const t3d::Vec2<real> & getTriangleUV1(size_t i) const = 0;

		virtual const t3d::Vec2<real> & getTriangleUV2(size_t i) const = 0;

	public:
		virtual void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) = 0;

		virtual void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) = 0;

		virtual void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) = 0;

		virtual void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) = 0;

		virtual void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawSolidZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) = 0;

		virtual void drawSolidZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawSolidZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) = 0;

		virtual void drawSolidZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawGouraudZBufferRW(
			t3d::RenderContext * rc) = 0;

		virtual void drawGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) = 0;

		virtual void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) = 0;

		virtual void drawTextureZBufferW(
			t3d::RenderContext * rc) = 0;

		virtual void drawTextureZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc) = 0;

		virtual void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTextureZBufferRW(
			t3d::RenderContext * rc) = 0;

		virtual void drawTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc) = 0;

		virtual void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) = 0;

		virtual void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc) = 0;

		virtual void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) = 0;

		virtual void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) = 0;

		virtual void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc) = 0;

		virtual void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) = 0;

		virtual void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc) = 0;

		virtual void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) = 0;
	};

	typedef boost::shared_ptr<ObjectBase> ObjectBasePtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// Object
	// /////////////////////////////////////////////////////////////////////////////////////

	class Object
		: public ObjectBase
	{
	public:
		Object(void);

	public:
		size_t getTriangleCount(void) const;

		const t3d::Vec4<real> & getTriangleVertex0(size_t i) const;

		const t3d::Vec4<real> & getTriangleVertex1(size_t i) const;

		const t3d::Vec4<real> & getTriangleVertex2(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal0(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal1(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal2(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV0(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV1(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV2(size_t i) const;

	public:
		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawSolidZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawSolidZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawSolidZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawSolidZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawTextureZBufferW(
			t3d::RenderContext * rc);

		void drawTextureZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc);

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferRW(
			t3d::RenderContext * rc);

		void drawTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);
	};

	typedef boost::shared_ptr<Object> ObjectPtr;

	//// /////////////////////////////////////////////////////////////////////////////////////
	//// SimpleAxisAlignedBoxObject
	//// /////////////////////////////////////////////////////////////////////////////////////

	//typedef std::vector<AxisAlignedBox> AxisAlignedBoxList;

	//class SimpleAxisAlignedBoxObject : public Object
	//{
	//protected:
	//	AxisAlignedBoxList m_axisAlignedBoxList;

	//public:
	//	void initAxisAlignedBoxList(void);

	//	void drawWireZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color);

	//	void drawWireZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color,
	//		const t3d::Mat4<real> & mmat);

	//	void drawWireZBufferRWWithoutThirdInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color);

	//	void drawWireZBufferRWWithoutThirdInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color,
	//		const t3d::Mat4<real> & mmat);

	//	void drawWireZBufferRWWithBackfaceInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color);

	//	void drawWireZBufferRWWithBackfaceInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color,
	//		const t3d::Mat4<real> & mmat);

	//	void drawWireZBufferRWWithBackfaceWithoutThirdInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color);

	//	void drawWireZBufferRWWithBackfaceWithoutThirdInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Vec4<real> & color,
	//		const t3d::Mat4<real> & mmat);

	//	void drawGouraudZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box);

	//	void drawGouraudZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Mat4<real> & mmat,
	//		const t3d::Mat4<real> & mrot);

	//	//void drawGouraudZBufferRWWithBackfaceInsideBox(
	//	//	t3d::RenderContext * rc,
	//	//	const AxisAlignedBox & box);

	//	//void drawGouraudZBufferRWWithBackfaceInsideBox(
	//	//	t3d::RenderContext * rc,
	//	//	const AxisAlignedBox & box,
	//	//	const t3d::Mat4<real> & mmat,
	//	//	const t3d::Mat4<real> & mrot);

	//	void drawTextureZBufferWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box);

	//	void drawTextureZBufferWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Mat4<real> & mmat);

	//	//void drawTextureZBufferWWithBackfaceInsideBox(
	//	//	t3d::RenderContext * rc,
	//	//	const AxisAlignedBox & box);

	//	//void drawTextureZBufferWWithBackfaceInsideBox(
	//	//	t3d::RenderContext * rc,
	//	//	const AxisAlignedBox & box,
	//	//	const t3d::Mat4<real> & mmat);

	//	void drawTextureZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box);

	//	void drawTextureZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Mat4<real> & mmat);

	//	//void drawTextureZBufferRWWithBackfaceInsideBox(
	//	//	t3d::RenderContext * rc,
	//	//	const AxisAlignedBox & box);

	//	//void drawTextureZBufferRWWithBackfaceInsideBox(
	//	//	t3d::RenderContext * rc,
	//	//	const AxisAlignedBox & box,
	//	//	const t3d::Mat4<real> & mmat);

	//	void drawGouraudTextureZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box);

	//	void drawGouraudTextureZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Mat4<real> & mmat,
	//		const t3d::Mat4<real> & mrot);

	//	void drawGouraudTextureZBufferRWWithBackfaceInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box);

	//	void drawGouraudTextureZBufferRWWithBackfaceInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Mat4<real> & mmat,
	//		const t3d::Mat4<real> & mrot);

	//	void drawGouraudTexturePerspectiveLPZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box);

	//	void drawGouraudTexturePerspectiveLPZBufferRWInsideBox(
	//		t3d::RenderContext * rc,
	//		const AxisAlignedBox & box,
	//		const t3d::Mat4<real> & mmat,
	//		const t3d::Mat4<real> & mrot);
	//};

	// /////////////////////////////////////////////////////////////////////////////////////
	// ObjectFromOgreMesh
	// /////////////////////////////////////////////////////////////////////////////////////

	class ObjectFromOgreMesh : public Object
	{
	public:
		ObjectFromOgreMesh(
			IOStream * meshStream);

		~ObjectFromOgreMesh(void);
	};

	typedef boost::shared_ptr<ObjectFromOgreMesh> ObjectFromOgreMeshPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexObject
	// /////////////////////////////////////////////////////////////////////////////////////

	class IndexObject
		: public ObjectBase
		, public t3d::VertexIndexListContext
	{
	public:
		IndexObject(void);

	public:
		size_t getTriangleCount(void) const;

		const t3d::Vec4<real> & getTriangleVertex0(size_t i) const;

		const t3d::Vec4<real> & getTriangleVertex1(size_t i) const;

		const t3d::Vec4<real> & getTriangleVertex2(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal0(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal1(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal2(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV0(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV1(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV2(size_t i) const;

	public:
		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawSolidZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawSolidZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawSolidZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawSolidZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawTextureZBufferW(
			t3d::RenderContext * rc);

		void drawTextureZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc);

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferRW(
			t3d::RenderContext * rc);

		void drawTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);
	};

	typedef boost::shared_ptr<IndexObject> IndexObjectPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexPlaneObject
	// /////////////////////////////////////////////////////////////////////////////////////

	class IndexPlaneObject : public IndexObject
	{
	protected:
		enum PLANE_TYPE
		{
			X_PLANE,
			NEGATIVE_X_PLANE,
			Y_PLANE,
			NEGATIVE_Y_PLANE,
			Z_PLANE,
			NEGATIVE_Z_PLANE
		};

		void pushSingleIndexPlane(
			real width,
			real height,
			int subdivisionsAlongWidth,
			int subdivisionsAlongHeight,
			PLANE_TYPE planeType,
			real planeDepth,
			bool reverse);

		IndexPlaneObject(void);

	public:
		IndexPlaneObject(
			real width,
			real height,
			int subdivisionsAlongWidth = 10,
			int subdivisionsAlongHeight = 10,
			bool reverse = false);

		~IndexPlaneObject(void);
	};

	typedef boost::shared_ptr<IndexPlaneObject> IndexPlaneObjectPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexSphereObject
	// /////////////////////////////////////////////////////////////////////////////////////

	class IndexSphereObject : public IndexObject
	{
	public:
		IndexSphereObject(
			real radius,
			int subdivisionsAroundAxis = 20,
			int subdivisionsAroundHeight = 20,
			bool reverse = false);

		~IndexSphereObject(void);
	};

	typedef boost::shared_ptr<IndexSphereObject> IndexSphereObjectPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexCubeObject
	// /////////////////////////////////////////////////////////////////////////////////////

	class IndexCubeObject : public IndexPlaneObject
	{
	public:
		IndexCubeObject(
			real width,
			real height,
			real depth,
			int subdivisionsAroundWidth = 1,
			int subdivisionsAroundHeight = 1,
			int subdivisionsAroundDepth = 1,
			bool reverse = false);

		~IndexCubeObject(void);
	};

	typedef boost::shared_ptr<IndexCubeObject> IndexCubeObjectPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexConeObject
	// /////////////////////////////////////////////////////////////////////////////////////

	class IndexConeObject : public IndexObject
	{
	public:
		IndexConeObject(
			real radius,
			real height,
			int subdivisionsAroundAxis = 20,
			int subdivisionsAroundHeight = 1,
			int subdivisionsOnCaps = 1);

		~IndexConeObject(void);
	};

	typedef boost::shared_ptr<IndexConeObject> IndexConeObjectPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// BoneAssignmentIndexObject
	// /////////////////////////////////////////////////////////////////////////////////////

	class BoneAssignmentIndexObject : public IndexObject
	{
	public:
		t3d::VertexList m_origVertexList;

		t3d::NormalList m_origNormalList;

		t3d::BoneAssignmentList m_boneAssignmentList;

	public:
		const t3d::VertexList & getOriginalVertexList(void) const;

		t3d::VertexList & getOriginalVertexList(void);

		void pushOriginalVertex(real x, real y, real z);

		void pushOriginalVertex(real x, real y, real z, const t3d::Mat4<real> & mmat);

		void pushOriginalVertex(t3d::VertexList::const_reference vver);

		void pushOriginalVertex(t3d::VertexList::const_reference vver, const t3d::Mat4<real> & mmat);

		t3d::VertexList::const_iterator getOriginalVertexListBegin(void) const;

		t3d::VertexList::const_iterator getOriginalVertexListEnd(void) const;

		t3d::VertexList::iterator getOriginalVertexListBegin(void);

		t3d::VertexList::iterator getOriginalVertexListEnd(void);

		const t3d::NormalList & getOriginalNormalList(void) const;

		t3d::NormalList & getOriginalNormalList(void);

		void pushOriginalNormal(real x, real y, real z);

		void pushOriginalNormal(real x, real y, real z, const t3d::Mat4<real> & mmat);

		void pushOriginalNormal(t3d::NormalList::const_reference vver);

		void pushOriginalNormal(t3d::NormalList::const_reference vver, const t3d::Mat4<real> & mmat);

		t3d::NormalList::const_iterator getOriginalNormalListBegin(void) const;

		t3d::NormalList::const_iterator getOriginalNormalListEnd(void) const;

		t3d::NormalList::iterator getOriginalNormalListBegin(void);

		t3d::NormalList::iterator getOriginalNormalListEnd(void);

		const t3d::BoneAssignmentList & getBoneAssignmentList(void) const;

		t3d::BoneAssignmentList & getBoneAssignmentList(void);

		void pushBoneAssignment(size_t vertex_i, size_t bone_i, real weight);

		void pushBoneAssignment(t3d::BoneAssignmentList::const_reference boneAssignment);

		t3d::BoneAssignmentList::const_iterator getBoneAssignmentListBegin(void) const;

		t3d::BoneAssignmentList::const_iterator getBoneAssignmentListEnd(void) const;

		t3d::BoneAssignmentList::const_iterator getBoneAssignmentListBegin(void);

		t3d::BoneAssignmentList::const_iterator getBoneAssignmentListEnd(void);

	public:
		BoneAssignmentIndexObject(void);

		~BoneAssignmentIndexObject(void);

	public:
		void bindVertexListFromBoneTransformList(
			const t3d::BoneTransformList & boneTransformList);

		void bindVertexListNormalListFromBoneTransformList(
			const t3d::BoneTransformList & boneTransformList);
	};

	typedef boost::shared_ptr<BoneAssignmentIndexObject> BoneAssignmentIndexObjectPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// BoneAssignmentIndexObjectFromOgreMesh
	// /////////////////////////////////////////////////////////////////////////////////////

	class BoneAssignmentIndexObjectFromOgreMesh : public BoneAssignmentIndexObject
	{
	public:
		BoneAssignmentIndexObjectFromOgreMesh(
			IOStream * meshStream);

		~BoneAssignmentIndexObjectFromOgreMesh(void);
	};

	typedef boost::shared_ptr<BoneAssignmentIndexObjectFromOgreMesh> BoneAssignmentIndexObjectFromOgreMeshPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// SkeletonAnimationsFromOgreSkeleton
	// /////////////////////////////////////////////////////////////////////////////////////

	//typedef boost::shared_ptr<SkeletonAnimationManager> SkeletonAnimationManagerPtr;

	class SkeletonAnimationsFromOgreSkeleton : public SkeletonAnimationManager
	{
	public:
		t3d::BoneNodeList m_origBoneNodeList;

		t3d::BoneTransformList m_origBoneInverseTransformList;

		t3d::STreeNode::IndexList m_rootIndexList;

		typedef std::map<std::basic_string<char>, size_t> BoneIndexMap;

		BoneIndexMap m_boneIndexMap;

	public:
		void pushOrigBoneNode(t3d::BoneNodeList::const_reference origBoneNode);

		void pushOrigBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end);

		t3d::BoneNodeList::const_iterator getOrigBoneNodeListBegin(void) const;

		t3d::BoneNodeList::iterator getOrigBoneNodeListBegin(void);

		t3d::BoneNodeList::const_iterator getOrigBoneNodeListEnd(void) const;

		t3d::BoneNodeList::iterator getOrigBoneNodeListEnd(void);

		t3d::BoneNodeList::size_type getOrigBoneNodeListSize(void) const;

		void resizeOrigBoneNodeList(t3d::BoneNodeList::size_type size);

		void clearOrigBoneNodeList(void);

		t3d::BoneNodeList::reference origBoneNodeAt(t3d::BoneNodeList::size_type i);

		t3d::BoneNodeList::const_reference origBoneNodeAt(t3d::BoneNodeList::size_type i) const;

		t3d::BoneNodeList & getOrigBoneNodeList(void);

		const t3d::BoneNodeList & getOrigBoneNodeList(void) const;

		void pushOrigBoneInverseTransform(t3d::BoneTransformList::const_reference origBoneInverseTransform);

		void pushOrigBoneInverseTransformList(t3d::BoneTransformList::const_iterator begin, t3d::BoneTransformList::const_iterator end);

		t3d::BoneTransformList::const_iterator getOrigBoneInverseTransformListBegin(void) const;

		t3d::BoneTransformList::iterator getOrigBoneInverseTransformListBegin(void);

		t3d::BoneTransformList::const_iterator getOrigBoneInverseTransformListEnd(void) const;

		t3d::BoneTransformList::iterator getOrigBoneInverseTransformListEnd(void);

		t3d::BoneTransformList::size_type getOrigBoneInverseTransformListSize(void) const;

		void resizeOrigBoneInverseTransformList(t3d::BoneTransformList::size_type size);

		void clearOrigBoneInverseTransformList(void);

		t3d::BoneTransformList::reference origBoneInverseTransformAt(t3d::BoneTransformList::size_type i);

		t3d::BoneTransformList::const_reference origBoneInverseTransformAt(t3d::BoneTransformList::size_type i) const;

		t3d::BoneTransformList & getOrigBoneInverseTransformList(void);

		const t3d::BoneTransformList & getOrigBoneInverseTransformList(void) const;

		void pushRootIndex(t3d::STreeNode::IndexList::const_reference rootIndex);

		void pushRootIndexList(t3d::STreeNode::IndexList::const_iterator begin, t3d::STreeNode::IndexList::const_iterator end);

		t3d::STreeNode::IndexList::const_iterator getRootIndexListBegin(void) const;

		t3d::STreeNode::IndexList::iterator getRootIndexListBegin(void);

		t3d::STreeNode::IndexList::const_iterator getRootIndexListEnd(void) const;

		t3d::STreeNode::IndexList::iterator getRootIndexListEnd(void);

		t3d::STreeNode::IndexList::size_type getRootIndexListSize(void) const;

		void resizeRootIndexList(t3d::STreeNode::IndexList::size_type size);

		void clearRootIndexList(void);

		t3d::STreeNode::IndexList::reference rootIndexAt(t3d::STreeNode::IndexList::size_type i);

		t3d::STreeNode::IndexList::const_reference rootIndexAt(t3d::STreeNode::IndexList::size_type i) const;

		t3d::STreeNode::IndexList & getRootIndexList(void);

		const t3d::STreeNode::IndexList & getRootIndexList(void) const;

		void insertBoneIndex(const std::basic_string<char> & boneName, size_t bone_i);

		bool isBoneIndexExistent(const std::basic_string<char> & boneName) const;

		size_t getBoneIndex(const std::basic_string<char> & boneName) const;

	public:
		SkeletonAnimationsFromOgreSkeleton(
			IOStream * skeletonStream);

		~SkeletonAnimationsFromOgreSkeleton(void);
	};

	typedef boost::shared_ptr<SkeletonAnimationsFromOgreSkeleton> SkeletonAnimationsFromOgreSkeletonPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// DrawnHelper
	// /////////////////////////////////////////////////////////////////////////////////////

	class DrawnHelper
	{
	protected:
		IndexSphereObject sphere0;

		IndexCubeObject cube;

		IndexPlaneObject plane;

	public:
		DrawnHelper(void);

		~DrawnHelper(void);

		void drawLinePointAndPointZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & p0,
			const t3d::Vec4<real> & p1,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY);

		void drawLinePointAndNormalZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & point,
			const t3d::Vec4<real> & normal,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY);

		void drawTriangleWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			const t3d::Vec4<real> & v2,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY);

		void drawTriangleGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			const t3d::Vec4<real> & v2,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawTriangleGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			const t3d::Vec4<real> & v2,
			const t3d::Vec2<real> & t0,
			const t3d::Vec2<real> & t1,
			const t3d::Vec2<real> & t2,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawTriangleGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			const t3d::Vec4<real> & v2,
			const t3d::Vec2<real> & t0,
			const t3d::Vec2<real> & t1,
			const t3d::Vec2<real> & t2,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawSphereWireZBufferRW(
			t3d::RenderContext * rc,
			real radius,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY);

		void drawSphereGouraudZBufferRW(
			t3d::RenderContext * rc,
			real radius,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawSphereGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			real radius,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawCubeWireZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> halfSize,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY);

		void drawCubeGouraudZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> halfSize,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawCubeGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> halfSize,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawPlaneWireZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> direction,
			real distance,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY);

		void drawPlaneGouraudZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> direction,
			real distance,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawPlaneGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> direction,
			real distance,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);

		void drawPlaneGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			t3d::Vec4<real> direction,
			real distance,
			const t3d::Mat4<real> & mmat = my::Mat4<real>::IDENTITY,
			const t3d::Mat4<real> & mrot = my::Mat4<real>::IDENTITY);
	};
}

#endif // __MYUTILITY_H__
