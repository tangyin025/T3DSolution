
#include "stdafx.h"
#include "myUtility.h"
#include <tinyxml.h>
#include <atltypes.h>
#include "myWindow.h"

#pragma comment(lib, "winmm.lib")

namespace my
{
	// /////////////////////////////////////////////////////////////////////////////////////
	// FPSManager
	// /////////////////////////////////////////////////////////////////////////////////////

	FPSManager::FPSManager(void)
		: interval_time(1000)
		, last_time(0)
		, past_time(0)
		, past_frames(0)
		, m_fps(0)
	{
	}

	void FPSManager::start(void)
	{
		last_time = ::timeGetTime();
	}

	void FPSManager::addFrame(void)
	{
		DWORD curr_time = ::timeGetTime();
		past_time += curr_time - last_time;
		past_frames += 1;

		if(past_time > interval_time)
		{
			m_fps = (real)past_frames / (real)past_time * 1000;
			past_time = 0;
			past_frames = 0;
		}

		last_time = curr_time;
	}

	real FPSManager::getFPS(void)
	{
		return m_fps;
	}

	DWORD FPSManager::getLastUpdateTime(void)
	{
		return last_time;
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// Timer
	// /////////////////////////////////////////////////////////////////////////////////////

	Timer::Timer(void)
		: m_paused(false)
	{
		LARGE_INTEGER qwFrequency;
		if(!QueryPerformanceFrequency(&qwFrequency))
			T3D_WINEXCEPT(::GetLastError());
		m_frequency = (double)qwFrequency.QuadPart;

		if(!QueryPerformanceCounter(&m_lastTime))
			T3D_WINEXCEPT(::GetLastError());

		pause();
	}

	Timer::~Timer(void)
	{
	}

	bool Timer::isPaused(void)
	{
		return m_paused;
	}

	void Timer::start(void)
	{
		if(!QueryPerformanceCounter(&m_lastTime))
			T3D_WINEXCEPT(::GetLastError());

		m_paused = false;
	}

	void Timer::pause(void)
	{
		if(!isPaused())
		{
			LARGE_INTEGER qwTime;
			if(!QueryPerformanceCounter(&qwTime))
				T3D_WINEXCEPT(::GetLastError());

			m_lastTime.QuadPart = qwTime.QuadPart - m_lastTime.QuadPart;

			m_paused = true;
		}
		else
		{
			LARGE_INTEGER qwTime;
			if(!QueryPerformanceCounter(&qwTime))
				T3D_WINEXCEPT(::GetLastError());

			m_lastTime.QuadPart = qwTime.QuadPart - m_lastTime.QuadPart;

			m_paused = false;
		}
	}

	double Timer::getElapsedTime(void)
	{
		_ASSERT(!isPaused());

		LARGE_INTEGER qwTime;
		if(!QueryPerformanceCounter(&qwTime))
			T3D_WINEXCEPT(::GetLastError());

		double ret = (double)(qwTime.QuadPart - m_lastTime.QuadPart) / m_frequency;

		m_lastTime = qwTime;

		return ret;
	}

	double Timer::getLastUpdateTime(void)
	{
		return (double)m_lastTime.QuadPart / m_frequency;
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// EulerCamera
	// /////////////////////////////////////////////////////////////////////////////////////

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovFront(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(0)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(0)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovFrontRight(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(45)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(45)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovRight(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(90)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(90)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovRightBack(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(135)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(135)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovBack(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(180)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(180)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovBackLeft(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(225)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(225)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovLeft(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(270)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(270)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovLeftFront(t3d::Vec4<real> & vres, real angle, real scaler)
	{
		vres.x = sin(angle + DEG_TO_RAD(315)) * scaler;
		vres.z = cos(angle + DEG_TO_RAD(315)) * scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovUp(t3d::Vec4<real> & vres, real scaler)
	{
		vres.y = scaler;
		return vres;
	}

	t3d::Vec4<real> & EulerCamera::updateVec4OnMovDown(t3d::Vec4<real> & vres, real scaler)
	{
		vres.y = -scaler;
		return vres;
	}

	t3d::Vec4<real> EulerCamera::buildMovOffset(t3d::DIKeyboard * keyboard, real angle, real scaler)
	{
		static const DWORD MOV_STATE_UP		= 0x01;
		static const DWORD MOV_STATE_DOWN	= 0x02;
		static const DWORD MOV_STATE_LEFT	= 0x04;
		static const DWORD MOV_STATE_RIGHT	= 0x08;

		DWORD state = 0;
		if(keyboard->isKeyDown(DIK_W) || keyboard->isKeyDown(DIK_UP))
		{
			state |= MOV_STATE_UP;
		}

		if(keyboard->isKeyDown(DIK_S) || keyboard->isKeyDown(DIK_DOWN))
		{
			state |= MOV_STATE_DOWN;
		}

		if(keyboard->isKeyDown(DIK_A) || keyboard->isKeyDown(DIK_LEFT))
		{
			state |= MOV_STATE_LEFT;
		}

		if(keyboard->isKeyDown(DIK_D) || keyboard->isKeyDown(DIK_RIGHT))
		{
			state |= MOV_STATE_RIGHT;
		}

		my::Vec4<real> vres;
		switch(state)
		{
		case MOV_STATE_UP:
			updateVec4OnMovFront(vres, angle, scaler);
			break;

		case MOV_STATE_UP | MOV_STATE_RIGHT:
			updateVec4OnMovFrontRight(vres, angle, scaler);
			break;

		case MOV_STATE_RIGHT:
			updateVec4OnMovRight(vres, angle, scaler);
			break;

		case MOV_STATE_DOWN | MOV_STATE_RIGHT:
			updateVec4OnMovRightBack(vres, angle, scaler);
			break;

		case MOV_STATE_DOWN:
			updateVec4OnMovBack(vres, angle, scaler);
			break;

		case MOV_STATE_DOWN | MOV_STATE_LEFT:
			updateVec4OnMovBackLeft(vres, angle, scaler);
			break;

		case MOV_STATE_LEFT:
			updateVec4OnMovLeft(vres, angle, scaler);
			break;

		case MOV_STATE_UP | MOV_STATE_LEFT:
			updateVec4OnMovLeftFront(vres, angle, scaler);
			break;

		default:
			break;
		}

		if(keyboard->isKeyDown(DIK_HOME))
		{
			updateVec4OnMovUp(vres, scaler);
		}

		if(keyboard->isKeyDown(DIK_END))
		{
			updateVec4OnMovDown(vres, scaler);
		}
		return vres;
	}

	t3d::Vec4<real> EulerCamera::buildRotOffset(t3d::DIMouse * mouse)
	{
		return my::Vec4<real>(DEG_TO_RAD(mouse->getY()), DEG_TO_RAD(mouse->getX()), 0);
	}

	EulerCamera::EulerCamera(void)
		: m_posDefault(my::Vec4<real>::ZERO)
		, m_pos(my::Vec4<real>::ZERO)
		, m_rotDefault(my::Vec4<real>::ZERO)
		, m_rot(my::Vec4<real>::ZERO)
		, m_movSpeed(100)
	{
	}

	EulerCamera::~EulerCamera(void)
	{
	}

	void EulerCamera::setDefaultPosition(const t3d::Vec4<real> & pos)
	{
		m_posDefault = pos;
	}

	const t3d::Vec4<real> & EulerCamera::getDefaultPosition(void) const
	{
		return m_posDefault;
	}

	void EulerCamera::setDefaultRotation(const t3d::Vec4<real> & rot)
	{
		m_rotDefault = rot;
	}

	const t3d::Vec4<real> & EulerCamera::getDefaultRotation(void) const
	{
		return m_rotDefault;
	}

	void EulerCamera::setPosition(const t3d::Vec4<real> & pos)
	{
		m_pos = pos;
	}

	void EulerCamera::addPosition(const t3d::Vec4<real> & pos)
	{
		t3d::vec3AddSelf(m_pos, pos);
	}

	const t3d::Vec4<real> & EulerCamera::getPosition(void) const
	{
		return m_pos;
	}

	void EulerCamera::setRotation(const t3d::Vec4<real> & rot)
	{
		m_rot = rot;
	}

	void EulerCamera::addRotation(const t3d::Vec4<real> & rot)
	{
		t3d::vec3AddSelf(m_rot, rot);
	}

	const t3d::Vec4<real> & EulerCamera::getRotation(void) const
	{
		return m_rot;
	}

	void EulerCamera::setPitch(real value)
	{
		m_rot.x = value;
	}

	void EulerCamera::addPitch(real value)
	{
		m_rot.x += value;
	}

	real EulerCamera::getPitch(void) const
	{
		return m_rot.x;
	}

	void EulerCamera::setYaw(real value)
	{
		m_rot.y = value;
	}

	void EulerCamera::addYaw(real value)
	{
		m_rot.y += value;
	}

	real EulerCamera::getYaw(void) const
	{
		return m_rot.y;
	}

	void EulerCamera::setRoll(real value)
	{
		m_rot.z = value;
	}

	void EulerCamera::addRoll(real value)
	{
		m_rot.z += value;
	}

	real EulerCamera::getRoll(void) const
	{
		return m_rot.z;
	}

	void EulerCamera::setMovSpeed(real speed)
	{
		m_movSpeed = speed;
	}

	real EulerCamera::getMovSpeed(void) const
	{
		return m_movSpeed;
	}

	void EulerCamera::reset(void)
	{
		setPosition(getDefaultPosition());

		setRotation(getDefaultRotation());
	}

	void EulerCamera::update(t3d::DIKeyboard * keyboard, t3d::DIMouse * mouse, real step_time)
	{
		if(!keyboard->isKeyDown(DIK_R))
		{
			addPosition(buildMovOffset(keyboard, m_rot.y, m_movSpeed * step_time));

			addRotation(buildRotOffset(mouse));
		}
		else
		{
			reset();
		}
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// ConsoleSimulator
	// /////////////////////////////////////////////////////////////////////////////////////

	ConsoleSimulator::ConsoleSimulator(size_t maxLine /*= 5*/, int step /*= ::GetSystemMetrics(SM_CYMENU)*/)
		: m_step(step)
		, m_maxLine(maxLine)
	{
	}

	ConsoleSimulator::~ConsoleSimulator(void)
	{
	}

	void ConsoleSimulator::report(const std::basic_string<charT> & info)
	{
		m_lines.push_back(info);

		if(m_lines.size() > m_maxLine)
		{
			m_lines.pop_front();
		}
	}

	void ConsoleSimulator::clear(void)
	{
		m_lines.clear();
	}

	void ConsoleSimulator::draw(t3d::DDSurface * surface, int x, int y) const
	{
		HDC hdc = surface->getDC();

		for(int i = 0; i < (int)m_lines.size(); i++)
		{
			::TextOut(hdc, x, y + i * m_step, m_lines[i].c_str(), (int)m_lines[i].length());
		}

		surface->releaseDC(hdc);
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// MenuSystem
	// /////////////////////////////////////////////////////////////////////////////////////

	MenuItemArrow::MenuItemArrow(int width /*= ::GetSystemMetrics(SM_CYMENU)*/, int height /*= ::GetSystemMetrics(SM_CYMENU)*/)
		: m_width(width)
		, m_height(height)
	{
	}

	void MenuItemArrow::setWidth(int width)
	{
		m_width = width;
	}

	int MenuItemArrow::getWidth(void) const
	{
		return m_width;
	}

	void MenuItemArrow::setHeight(int height)
	{
		m_height = height;
	}

	int MenuItemArrow::getHeight(void) const
	{
		return m_height;
	}

	void MenuItemArrow::draw(t3d::DDSurface * surface, int x, int y) const
	{
		CRect rect;
		rect.left = x + (m_width - ::GetSystemMetrics(SM_CXMENUCHECK)) / 2;
		rect.top = y + (m_height - ::GetSystemMetrics(SM_CYMENUCHECK)) / 2;
		rect.right = rect.left + ::GetSystemMetrics(SM_CXMENUCHECK);
		rect.bottom = rect.top + ::GetSystemMetrics(SM_CYMENUCHECK);

		HDC hdc = surface->getDC();

		::DrawFrameControl(hdc, &rect, DFC_MENU, DFCS_MENUARROW);

		surface->releaseDC(hdc);
	}

	MenuItemCheck::MenuItemCheck(int width /*= ::GetSystemMetrics(SM_CYMENU)*/, int height /*= ::GetSystemMetrics(SM_CYMENU)*/)
		: m_width(width)
		, m_height(height)
	{
	}

	void MenuItemCheck::setWidth(int width)
	{
		m_width = width;
	}

	int MenuItemCheck::getWidth(void) const
	{
		return m_width;
	}

	void MenuItemCheck::setHeight(int height)
	{
		m_height = height;
	}

	int MenuItemCheck::getHeight(void) const
	{
		return m_height;
	}

	void MenuItemCheck::draw(t3d::DDSurface * surface, int x, int y) const
	{
		CRect rect;
		rect.left = x + (m_width - ::GetSystemMetrics(SM_CXMENUCHECK)) / 2;
		rect.top = y + (m_height - ::GetSystemMetrics(SM_CYMENUCHECK)) / 2;
		rect.right = rect.left + ::GetSystemMetrics(SM_CXMENUCHECK);
		rect.bottom = rect.top + ::GetSystemMetrics(SM_CYMENUCHECK);

		HDC hdc = surface->getDC();

		::DrawFrameControl(hdc, &rect, DFC_MENU, DFCS_MENUCHECK | DFCS_CHECKED);

		surface->releaseDC(hdc);
	}

	MenuItem::MenuItem(const std::basic_string<charT> & text, int width, int height /*= ::GetSystemMetrics(SM_CYMENU)*/)
		: m_arrow(height, height)
		, m_check(height, height)
		, m_text(text)
		, m_width(width)
		, m_height(height)
	{
	}

	void MenuItem::setText(const std::basic_string<charT> & text)
	{
		m_text = text;
	}

	const std::basic_string<charT> & MenuItem::getText(void) const
	{
		return m_text;
	}

	void MenuItem::setWidth(int width)
	{
		m_width = width;
	}

	int MenuItem::getWidth(void) const
	{
		return m_width;
	}

	void MenuItem::setHeight(int height)
	{
		m_height = height;
	}

	int MenuItem::getHeight(void) const
	{
		return m_height;
	}

	void MenuItem::draw(t3d::DDSurface * surface, int x, int y, bool arrow /*= false*/, bool check /*= false*/) const
	{
		if(check)
		{
			m_check.draw(surface, x, y);
		}

		HDC hdc = surface->getDC();

		::TextOut(hdc, x + m_check.getWidth(), y, m_text.c_str(), (int)m_text.length());

		surface->releaseDC(hdc);

		if(arrow)
		{
			m_arrow.draw(surface, x + getWidth() - m_arrow.getWidth(), y);
		}
	}

	Menu::Menu(int width)
		: m_width(width)
	{
	}

	size_t Menu::createMenuItemNode(const std::basic_string<charT> & itemText, int itemHeight /*= ::GetSystemMetrics(SM_CYMENU)*/)
	{
		m_items.push_back(MenuItemNodePtr(new MenuItemNode(itemText, getWidth(), itemHeight)));

		return m_items.size() - 1;
	}

	MenuItemNodePtr Menu::getMenuItemNode(size_t item_i) const
	{
		return m_items[item_i];
	}

	MenuItemNodePtr Menu::getMenuItemNode(const std::basic_string<charT> & itemText) const
	{
		MenuItemNodePtrList::const_iterator sub_item_iter = m_items.begin();
		for(; sub_item_iter != m_items.end(); sub_item_iter++)
		{
			if(itemText == (*sub_item_iter)->getText())
			{
				return (*sub_item_iter);
			}
		}

		_ASSERT(false);

		return m_items.front();
	}

	size_t Menu::getMenuItemNodeCount(void) const
	{
		return m_items.size();
	}

	int Menu::getWidth(void) const
	{
		return m_width;
	}

	int Menu::getHeight(void) const
	{
		int height = 0;
		MenuItemNodePtrList::const_iterator sub_item_iter = m_items.begin();
		for(; sub_item_iter != m_items.end(); sub_item_iter++)
		{
			height += (*sub_item_iter)->getHeight();
		}

		return height;
	}

	void Menu::setCheckType(MenuCheckType checkType)
	{
		m_checkType = checkType;
	}

	Menu::MenuCheckType Menu::getCheckType(void) const
	{
		return m_checkType;
	}

	void Menu::singleCheckItemNode(size_t item_i)
	{
		_ASSERT(item_i < getMenuItemNodeCount());

		_ASSERT(0 == getMenuItemNode(item_i)->getSubMenu().getMenuItemNodeCount());

		size_t i = 0;
		for(; i < getMenuItemNodeCount(); i++)
		{
			getMenuItemNode(i)->setCheck(false);
		}

		getMenuItemNode(item_i)->setCheck(true);
	}

	void Menu::draw(t3d::DDSurface * surface, int x, int y) const
	{
		size_t i = 0;
		for(; i < getMenuItemNodeCount(); i++)
		{
			MenuItemNodePtr itemNode = getMenuItemNode(i);

			itemNode->draw(surface, x, y);

			y += itemNode->getHeight();
		}
	}

	MenuItemNode::MenuItemNode(const std::basic_string<charT> & text, int width, int height /*= ::GetSystemMetrics(SM_CYMENU)*/)
		: MenuItem(text, width, height)
		, m_subMenu(width)
		, m_checked(false)
	{
	}

	Menu & MenuItemNode::getSubMenu(void)
	{
		return m_subMenu;
	}

	const Menu & MenuItemNode::getSubMenu(void) const
	{
		return m_subMenu;
	}

	void MenuItemNode::setCheck(bool checked)
	{
		m_checked = checked;
	}

	bool MenuItemNode::getCheck(void) const
	{
		return m_checked;
	}

	void MenuItemNode::draw(t3d::DDSurface * surface, int x, int y) const
	{
		MenuItem::draw(surface, x, y, 0 != m_subMenu.getMenuItemNodeCount(), getCheck());
	}

	MenuSystem::MenuSystem(int width)
		: Menu(width)
	{
	}

	void MenuSystem::selectMenuItemNode(size_t item_i)
	{
		_ASSERT(!m_menuStack.empty());

		if(item_i < m_menuStack.back()->getMenuItemNodeCount())
		{
			if(0 != m_menuStack.back()->getMenuItemNode(item_i)->getSubMenu().getMenuItemNodeCount())
			{
				m_menuStack.push_back(&m_menuStack.back()->getMenuItemNode(item_i)->getSubMenu());
			}
			else if(Menu::SingleCheckType == m_menuStack.back()->getCheckType())
			{
				m_menuStack.back()->singleCheckItemNode(item_i);
			}
			else
			{
				m_menuStack.back()->getMenuItemNode(item_i)->setCheck(!m_menuStack.back()->getMenuItemNode(item_i)->getCheck());
			}
		}
	}

	void MenuSystem::onKeyRelease(UINT vkcode)
	{
		switch(vkcode)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if(!m_menuStack.empty())
			{
				selectMenuItemNode(vkcode - '0');
			}
			break;

		case VK_BACK:
			if(!m_menuStack.empty())
			{
				m_menuStack.pop_back();
			}
			break;

		case VK_OEM_3:
			if(!m_menuStack.empty())
			{
				m_menuStack.clear();
			}
			else
			{
				m_menuStack.push_back(this);
			}
			break;
		}
	}

	void MenuSystem::draw(t3d::DDSurface * surface, int x, int y) const
	{
		if(!m_menuStack.empty())
		{
			m_menuStack.back()->draw(surface, x, y);
		}
		else
		{
			HDC hdc = surface->getDC();

			std::basic_string<charT> info = _T("[~] toggle menu");

			::TextOut(hdc, x, y, info.c_str(), (int)info.length());

			surface->releaseDC(hdc);
		}
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// Grid
	// /////////////////////////////////////////////////////////////////////////////////////

	Grid::Grid(
		real lengthAndWidth /*= 100*/,
		real gridLinesEvery /*= 10*/)
	{
		_ASSERT(lengthAndWidth >= 0);
		_ASSERT(gridLinesEvery > 0);

		m_axisList.push_back(my::Vec4<real>(0, 0, -lengthAndWidth));
		m_axisList.push_back(my::Vec4<real>(0, 0,  lengthAndWidth));
		m_axisList.push_back(my::Vec4<real>(-lengthAndWidth, 0, 0));
		m_axisList.push_back(my::Vec4<real>( lengthAndWidth, 0, 0));

		m_gridList.push_back(my::Vec4<real>( lengthAndWidth, 0, -lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>( lengthAndWidth, 0,  lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>(-lengthAndWidth, 0, -lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>(-lengthAndWidth, 0,  lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>(-lengthAndWidth, 0,  lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>( lengthAndWidth, 0,  lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>(-lengthAndWidth, 0, -lengthAndWidth));
		m_gridList.push_back(my::Vec4<real>( lengthAndWidth, 0, -lengthAndWidth));

		for(int i = 1; i < (int)ceil(lengthAndWidth / gridLinesEvery); i++)
		{
			m_gridList.push_back(my::Vec4<real>( i * gridLinesEvery, 0, -lengthAndWidth));
			m_gridList.push_back(my::Vec4<real>( i * gridLinesEvery, 0,  lengthAndWidth));
			m_gridList.push_back(my::Vec4<real>(-i * gridLinesEvery, 0, -lengthAndWidth));
			m_gridList.push_back(my::Vec4<real>(-i * gridLinesEvery, 0,  lengthAndWidth));

			m_gridList.push_back(my::Vec4<real>(-lengthAndWidth, 0, -i * gridLinesEvery));
			m_gridList.push_back(my::Vec4<real>( lengthAndWidth, 0, -i * gridLinesEvery));
			m_gridList.push_back(my::Vec4<real>(-lengthAndWidth, 0,  i * gridLinesEvery));
			m_gridList.push_back(my::Vec4<real>( lengthAndWidth, 0,  i * gridLinesEvery));
		}
	}

	Grid::~Grid(void)
	{
	}

	void Grid::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & axisColor /*= my::Color(0.1f, 0.1f, 0.1f)*/,
		const t3d::Vec4<real> & gridColor /*= my::Color(0.6f, 0.6f, 0.6f)*/)
	{
		rc->clearVertexList();
		rc->pushVertexList(m_axisList.begin(), m_axisList.end());
		rc->drawLineListZBufferRW(axisColor);

		rc->clearVertexList();
		rc->pushVertexList(m_gridList.begin(), m_gridList.end());
		rc->drawLineListZBufferRW(gridColor);
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// Material
	// /////////////////////////////////////////////////////////////////////////////////////

	Material::Material(void)
		: ambient(my::Vec4<real>::UNIT_SCALE)
		, diffuse(my::Vec4<real>::UNIT_SCALE)
		, specular(my::Vec4<real>::UNIT_SCALE)
		, emissive(my::Vec4<real>::UNIT_SCALE)
	{
	}

	Material::~Material(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// ObjectBase
	// /////////////////////////////////////////////////////////////////////////////////////

	ObjectBase::ObjectBase(void)
	{
	}

	ObjectBase::~ObjectBase(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// Object
	// /////////////////////////////////////////////////////////////////////////////////////

	Object::Object(void)
	{
	}

	size_t Object::getTriangleCount(void) const
	{
		_ASSERT(0 == getVertexListSize() % 3);

		return getVertexListSize() / 3;
	}

	const t3d::Vec4<real> & Object::getTriangleVertex0(size_t i) const
	{
		return vertexAt(i * 3 + 0);
	}

	const t3d::Vec4<real> & Object::getTriangleVertex1(size_t i) const
	{
		return vertexAt(i * 3 + 1);
	}

	const t3d::Vec4<real> & Object::getTriangleVertex2(size_t i) const
	{
		return vertexAt(i * 3 + 2);
	}

	const t3d::Vec4<real> & Object::getTriangleNormal0(size_t i) const
	{
		return normalAt(i * 3 + 0);
	}

	const t3d::Vec4<real> & Object::getTriangleNormal1(size_t i) const
	{
		return normalAt(i * 3 + 1);
	}

	const t3d::Vec4<real> & Object::getTriangleNormal2(size_t i) const
	{
		return normalAt(i * 3 + 2);
	}

	const t3d::Vec2<real> & Object::getTriangleUV0(size_t i) const
	{
		return uvAt(i * 3 + 0);
	}

	const t3d::Vec2<real> & Object::getTriangleUV1(size_t i) const
	{
		return uvAt(i * 3 + 1);
	}

	const t3d::Vec2<real> & Object::getTriangleUV2(size_t i) const
	{
		return uvAt(i * 3 + 2);
	}

	void Object::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->drawTriangleListWireZBufferRW(color);
	}

	void Object::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->drawTriangleListWireZBufferRW(color);
	}

	void Object::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->drawTriangleListWireZBufferRWWithBackface(color);
	}

	void Object::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->drawTriangleListWireZBufferRWWithBackface(color);
	}

	void Object::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->drawTriangleListZBufferRW(color);
	}

	void Object::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->drawTriangleListZBufferRW(color);
	}

	void Object::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->drawTriangleListZBufferRWWithBackface(color);
	}

	void Object::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->drawTriangleListZBufferRWWithBackface(color);
	}

	void Object::drawGouraudZBufferRW(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->drawTriangleListGouraudZBufferRW();
	}

	void Object::drawGouraudZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->drawTriangleListGouraudZBufferRW();
	}

	void Object::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->drawTriangleListGouraudZBufferRWWithBackface();
	}

	void Object::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->drawTriangleListGouraudZBufferRWWithBackface();
	}

	void Object::drawTextureZBufferW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferW();
	}

	void Object::drawTextureZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferW();
	}

	void Object::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferWWithBackface();
	}

	void Object::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferWWithBackface();
	}

	void Object::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferW();
	}

	void Object::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferW();
	}

	void Object::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferWWithBackface();
	}

	void Object::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferWWithBackface();
	}

	void Object::drawTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferRW();
	}

	void Object::drawTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferRW();
	}

	void Object::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferRWWithBackface();
	}

	void Object::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTextureZBufferRWWithBackface();
	}

	void Object::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferRW();
	}

	void Object::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferRW();
	}

	void Object::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void Object::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void Object::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTextureZBufferRW();
	}

	void Object::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTextureZBufferRW();
	}

	void Object::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTextureZBufferRWWithBackface();
	}

	void Object::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTextureZBufferRWWithBackface();
	}

	void Object::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRW();
	}

	void Object::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRW();
	}

	void Object::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface();
	}

	void Object::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface();
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// ObjectFromOgreMesh
	// /////////////////////////////////////////////////////////////////////////////////////

	#define DEFINE_XML_ELEMENT(elem_v, elem_p, elem_s)	\
		TiXmlElement * elem_v = elem_p->FirstChildElement(#elem_s); \
		if(NULL == elem_v) \
			T3D_CUSEXCEPT(_T("cannot find ") _T(#elem_s));

	#define DEFINE_XML_ELEMENT_SIMPLE(elem_v, elem_p) \
		DEFINE_XML_ELEMENT(elem_v, elem_p, elem_v)

	#define DEFINE_XML_ATTRIBUTE_CHAR(attr_v, elem_p, attr_s) \
		const char * attr_v; \
		if(NULL == (attr_v = elem_p->Attribute(#attr_s))) \
			T3D_CUSEXCEPT(_T("cannot read ") _T(#elem_p) _T(".") _T(#attr_s));

	#define DEFINE_XML_ATTRIBUTE_CHAR_SIMPLE(attr_v, elem_p) \
		DEFINE_XML_ATTRIBUTE_CHAR(attr_v, elem_p, attr_v)

	#define DEFINE_XML_ATTRIBUTE_INT(attr_v, elem_p, attr_s) \
		int attr_v; \
		if(NULL == (elem_p->Attribute(#attr_s, &attr_v))) \
			T3D_CUSEXCEPT(_T("cannot read ") _T(#elem_p) _T(".") _T(#attr_s));

	#define DEFINE_XML_ATTRIBUTE_INT_SIMPLE(attr_v, elem_p) \
		DEFINE_XML_ATTRIBUTE_INT(attr_v, elem_p, attr_v)

	#define DEFINE_XML_ATTRIBUTE_DOUBLE(attr_v, elem_p, attr_s) \
		double attr_v; \
		if(NULL == (elem_p->Attribute(#attr_s, &attr_v))) \
			T3D_CUSEXCEPT(_T("cannot read ") _T(#elem_p) _T(".") _T(#attr_s));

	#define DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(attr_v, elem_p) \
		DEFINE_XML_ATTRIBUTE_DOUBLE(attr_v, elem_p, attr_v)

	#define DEFINE_XML_ATTRIBUTE_BOOL(attr_v, elem_p, attr_s) \
		bool attr_v; \
		{ DEFINE_XML_ATTRIBUTE_CHAR(__tmp, elem_p, attr_s); \
			attr_v = (0 == strcmp(__tmp, "true")); }

	#define DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(attr_v, elem_p) \
		DEFINE_XML_ATTRIBUTE_BOOL(attr_v, elem_p, attr_v)

	ObjectFromOgreMesh::ObjectFromOgreMesh(
		IOStreamPtr meshStream)
	{
		TiXmlDocument doc;
		doc.LoadFile(static_cast<FILE *>(meshStream->getHandle()), TIXML_DEFAULT_ENCODING);

		DEFINE_XML_ELEMENT_SIMPLE(mesh, (&doc));

		DEFINE_XML_ELEMENT_SIMPLE(submeshes, mesh);

		//DEFINE_XML_ELEMENT_SIMPLE(submesh, submeshes);

		TiXmlElement * submesh = submeshes->FirstChildElement("submesh");
		for(; submesh != NULL; submesh = submesh->NextSiblingElement("submesh"))
		{
			DEFINE_XML_ELEMENT_SIMPLE(geometry, submesh);

			DEFINE_XML_ATTRIBUTE_INT_SIMPLE(vertexcount, geometry);

			if(vertexcount < 0)
				T3D_CUSEXCEPT(_T("invalid geometry.vertexcount"));

			DEFINE_XML_ELEMENT_SIMPLE(vertexbuffer, geometry);

			DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(positions, vertexbuffer);

			DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(normals, vertexbuffer);

			DEFINE_XML_ATTRIBUTE_INT_SIMPLE(texture_coords, vertexbuffer);

			t3d::VertexList vertexList;

			t3d::NormalList normalList;

			t3d::UVList uvList;

			if(positions)
			{
				TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
				for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
				{
					DEFINE_XML_ELEMENT_SIMPLE(position, vertex);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, position);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, position);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, position);

					vertexList.push_back(my::Vec4<real>((real)x, (real)y, (real)-z)); // ***
				}

				if((int)vertexList.size() != vertexcount)
					T3D_CUSEXCEPT(_T("cannot match vertex count"));
			}

			if(normals)
			{
				TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
				for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
				{
					DEFINE_XML_ELEMENT_SIMPLE(normal, vertex);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, normal);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, normal);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, normal);

					normalList.push_back(my::Vec4<real>((real)x, (real)y, (real)-z)); // ***
				}

				if((int)normalList.size() != vertexcount)
					T3D_CUSEXCEPT(_T("cannot match normal count"));
			}

			if(texture_coords > 0)
			{
				TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
				for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
				{
					DEFINE_XML_ELEMENT_SIMPLE(texcoord, vertex);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(u, texcoord);

					if(u < 0)
					{
						if(u > -EPSILON_E6)
							u = 0;
						else
							T3D_CUSEXCEPT(_T("invalid texcoord.u"));
					}
					else if(u > 1)
					{
						if(u < 1 + EPSILON_E6)
							u = 1;
						else
							T3D_CUSEXCEPT(_T("invalid texcoord.u"));
					}

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(v, texcoord);

					if(v < 0)
					{
						if(v > -EPSILON_E6)
							v = 0;
						else
							T3D_CUSEXCEPT(_T("invalid texcoord.u"));
					}
					else if(v > 1)
					{
						if(v < 1 + EPSILON_E6)
							v = 1;
						else
							T3D_CUSEXCEPT(_T("invalid texcoord.u"));
					}

					uvList.push_back(my::Vec2<real>((real)u, (real)(/*1 -*/ v))); // ***
				}

				if((int)uvList.size() != vertexcount)
					T3D_CUSEXCEPT(_T("cannot match uv count"));
			}

			DEFINE_XML_ELEMENT_SIMPLE(faces, submesh);

			DEFINE_XML_ATTRIBUTE_INT(face_count, faces, count);

			if(face_count > 0)
			{
				int prevVertexListSize = (int)getVertexListSize();

				TiXmlElement * face = faces->FirstChildElement("face");
				for(; face != NULL; face = face->NextSiblingElement("face"))
				{
					DEFINE_XML_ATTRIBUTE_INT_SIMPLE(v1, face);

					if(v1 < 0 || v1 >= vertexcount)
						T3D_CUSEXCEPT(_T("invalid face.v1"));

					DEFINE_XML_ATTRIBUTE_INT_SIMPLE(v2, face);

					if(v2 < 0 || v2 >= vertexcount)
						T3D_CUSEXCEPT(_T("invalid face.v2"));

					DEFINE_XML_ATTRIBUTE_INT_SIMPLE(v3, face);

					if(v3 < 0 || v3 >= vertexcount)
						T3D_CUSEXCEPT(_T("invalid face.v3"));

					if(positions)
					{
						pushVertex(vertexList[v1]);
						pushVertex(vertexList[v3]);
						pushVertex(vertexList[v2]);
					}

					if(normals)
					{
						pushNormal(normalList[v1]);
						pushNormal(normalList[v3]);
						pushNormal(normalList[v2]);
					}

					if(texture_coords)
					{
						pushUV(uvList[v1]);
						pushUV(uvList[v3]);
						pushUV(uvList[v2]);
					}
				}

				if((int)getVertexListSize() - prevVertexListSize != face_count * 3)
					T3D_CUSEXCEPT(_T("cannot match face count"));
			}
		}

		//initAxisAlignedBoxList();
	}

	ObjectFromOgreMesh::~ObjectFromOgreMesh(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexObject
	// /////////////////////////////////////////////////////////////////////////////////////

	IndexObject::IndexObject(void)
	{
	}

	size_t IndexObject::getTriangleCount(void) const
	{
		_ASSERT(0 == getVertexIndexListSize() % 3);

		return getVertexIndexListSize() / 3;
	}

	const t3d::Vec4<real> & IndexObject::getTriangleVertex0(size_t i) const
	{
		return vertexAt(vertexIndexAt(i * 3 + 0));
	}

	const t3d::Vec4<real> & IndexObject::getTriangleVertex1(size_t i) const
	{
		return vertexAt(vertexIndexAt(i * 3 + 1));
	}

	const t3d::Vec4<real> & IndexObject::getTriangleVertex2(size_t i) const
	{
		return vertexAt(vertexIndexAt(i * 3 + 2));
	}

	const t3d::Vec4<real> & IndexObject::getTriangleNormal0(size_t i) const
	{
		return normalAt(vertexIndexAt(i * 3 + 0));
	}

	const t3d::Vec4<real> & IndexObject::getTriangleNormal1(size_t i) const
	{
		return normalAt(vertexIndexAt(i * 3 + 1));
	}

	const t3d::Vec4<real> & IndexObject::getTriangleNormal2(size_t i) const
	{
		return normalAt(vertexIndexAt(i * 3 + 2));
	}

	const t3d::Vec2<real> & IndexObject::getTriangleUV0(size_t i) const
	{
		return uvAt(vertexIndexAt(i * 3 + 0));
	}

	const t3d::Vec2<real> & IndexObject::getTriangleUV1(size_t i) const
	{
		return uvAt(vertexIndexAt(i * 3 + 1));
	}

	const t3d::Vec2<real> & IndexObject::getTriangleUV2(size_t i) const
	{
		return uvAt(vertexIndexAt(i * 3 + 2));
	}

	void IndexObject::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListWireZBufferRW(color);
	}

	void IndexObject::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListWireZBufferRW(color);
	}

	void IndexObject::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListWireZBufferRWWithBackface(color);
	}

	void IndexObject::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListWireZBufferRWWithBackface(color);
	}

	void IndexObject::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListZBufferRW(color);
	}

	void IndexObject::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListZBufferRW(color);
	}

	void IndexObject::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListZBufferRWWithBackface(color);
	}

	void IndexObject::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListZBufferRWWithBackface(color);
	}

	void IndexObject::drawGouraudZBufferRW(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudZBufferRW();
	}

	void IndexObject::drawGouraudZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudZBufferRW();
	}

	void IndexObject::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudZBufferRWWithBackface();
	}

	void IndexObject::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudZBufferRWWithBackface();
	}

	void IndexObject::drawTextureZBufferW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferW();
	}

	void IndexObject::drawTextureZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferW();
	}

	void IndexObject::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferWWithBackface();
	}

	void IndexObject::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferWWithBackface();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferW();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferW();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void IndexObject::drawTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferRW();
	}

	void IndexObject::drawTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferRW();
	}

	void IndexObject::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferRWWithBackface();
	}

	void IndexObject::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTextureZBufferRWWithBackface();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferRW();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferRW();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void IndexObject::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		//_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		//rc->clearNormalList();
		//rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void IndexObject::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTextureZBufferRW();
	}

	void IndexObject::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTextureZBufferRW();
	}

	void IndexObject::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTextureZBufferRWWithBackface();
	}

	void IndexObject::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTextureZBufferRWWithBackface();
	}

	void IndexObject::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW();
	}

	void IndexObject::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW();
	}

	void IndexObject::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd());

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd());

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface();
	}

	void IndexObject::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		rc->clearVertexList();
		rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);

		rc->clearNormalList();
		rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);

		rc->clearUVList();
		rc->pushUVList(getUVListBegin(), getUVListEnd());

		rc->clearVertexIndexList();
		rc->pushVertexIndexList(getVertexIndexListBegin(), getVertexIndexListEnd());

		rc->drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface();
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexPlaneObject
	// /////////////////////////////////////////////////////////////////////////////////////

	static int inline _calculateVertexIndex(int x_size, int y_size, int x_index, int y_index, int offset = 0)
	{
		_ASSERT(x_index < x_size);
		_ASSERT(y_index < y_size);

		return y_index * x_size + x_index + offset;

		UNREFERENCED_PARAMETER(y_size);
	}

	void IndexPlaneObject::pushSingleIndexPlane(
		real width,
		real height,
		int subdivisionsAlongWidth,
		int subdivisionsAlongHeight,
		PLANE_TYPE planeType,
		real planeDepth,
		bool reverse)
	{
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		int offset = (int)getVertexListSize();

		for(int j = 0; j <= subdivisionsAlongHeight; j++)
		{
			for(int i = 0; i <= subdivisionsAlongWidth; i++)
			{
				switch(planeType)
				{
				case X_PLANE:
					//     z
					// y - d
					pushVertex(
						planeDepth,
						width / (real)2 - width * i / subdivisionsAlongWidth,
						height / (real)2 - height * j / subdivisionsAlongHeight);

					pushNormal(reverse ? my::Vec4<real>::NEGATIVE_UNIT_X : my::Vec4<real>::UNIT_X);
					break;

				case NEGATIVE_X_PLANE:
					//     y
					// z - d
					pushVertex(
						planeDepth,
						height / (real)2 - height * j / subdivisionsAlongHeight,
						width / (real)2 - width * i / subdivisionsAlongWidth);

					pushNormal(reverse ? my::Vec4<real>::UNIT_X : my::Vec4<real>::NEGATIVE_UNIT_X);
					break;

				case Y_PLANE:
					//     x
					// z - d
					pushVertex(
						height / (real)2 - height * j / subdivisionsAlongHeight,
						planeDepth,
						width / (real)2 - width * i / subdivisionsAlongWidth);

					pushNormal(reverse ? my::Vec4<real>::NEGATIVE_UNIT_Y : my::Vec4<real>::UNIT_Y);
					break;

				case NEGATIVE_Y_PLANE:
					//     z
					// x - d
					pushVertex(
						width / (real)2 - width * i / subdivisionsAlongWidth,
						planeDepth,
						height / (real)2 - height * j / subdivisionsAlongHeight);

					pushNormal(reverse ? my::Vec4<real>::UNIT_Y : my::Vec4<real>::NEGATIVE_UNIT_Y);
					break;

				case Z_PLANE:
					//     y
					// x - d
					pushVertex(
						width / (real)2 - width * i / subdivisionsAlongWidth,
						height / (real)2 - height * j / subdivisionsAlongHeight,
						planeDepth);

					pushNormal(reverse ? my::Vec4<real>::NEGATIVE_UNIT_Z : my::Vec4<real>::UNIT_Z);
					break;

				case NEGATIVE_Z_PLANE:
					//     x
					// y - d
					pushVertex(
						height / (real)2 - height * j / subdivisionsAlongHeight,
						width / (real)2 - width * i / subdivisionsAlongWidth,
						planeDepth);

					pushNormal(reverse ? my::Vec4<real>::UNIT_Z : my::Vec4<real>::NEGATIVE_UNIT_Z);
					break;

				default:
					_ASSERT(false);
				}

				pushUV(i / (real)subdivisionsAlongWidth, /*1 -*/ j / (real)subdivisionsAlongHeight);
			}
		}

		for(int j = 0; j <= subdivisionsAlongHeight; j++)
		{
			for(int i = 0; i <= subdivisionsAlongWidth - 1; i++)
			{
				// (i    , j - 1)
				// (i    , j    ) (i + 1, j    )
				if(j != 0)
				{
					if(reverse)
					{
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i, j - 1, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i, j, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i + 1, j, offset));
					}
					else
					{
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i + 1, j, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i, j, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i, j - 1, offset));
					}
				}

				// (i    , j    ) (i + 1, j    )
				//                (i + 1, j + 1)
				if(j != subdivisionsAlongHeight)
				{
					if(reverse)
					{
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i + 1, j + 1, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i + 1, j, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i, j, offset));
					}
					else
					{
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i, j, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i + 1, j, offset));
						pushVertexIndex(_calculateVertexIndex(subdivisionsAlongWidth + 1, subdivisionsAlongHeight + 1, i + 1, j + 1, offset));
					}
				}
			}
		}
	}

	IndexPlaneObject::IndexPlaneObject(void)
	{
	}

	IndexPlaneObject::IndexPlaneObject(
		real width,
		real height,
		int subdivisionsAlongWidth /*= 10*/,
		int subdivisionsAlongHeight /*= 10*/,
		bool reverse /*= false*/)
	{
		_ASSERT(subdivisionsAlongWidth >= 1);
		_ASSERT(subdivisionsAlongHeight >= 1);

		pushSingleIndexPlane(
			width,
			height,
			subdivisionsAlongWidth,
			subdivisionsAlongHeight,
			Y_PLANE,
			0,
			reverse);

#ifdef _DEBUG
		t3d::VertexIndexList::const_iterator i_iter = getVertexIndexListBegin();
		for(; i_iter != getVertexIndexListEnd(); i_iter++)
		{
			_ASSERT(*i_iter < getVertexListSize());
		}
#endif
	}

	IndexPlaneObject::~IndexPlaneObject(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexSphereObject
	// /////////////////////////////////////////////////////////////////////////////////////

	IndexSphereObject::IndexSphereObject(
		real radius,
		int subdivisionsAroundAxis /*= 20*/,
		int subdivisionsAroundHeight /*= 20*/,
		bool reverse /*= false*/)
	{
		_ASSERT(radius >= 0);
		_ASSERT(subdivisionsAroundAxis >= 3);
		_ASSERT(subdivisionsAroundHeight >= 2);

		for(int j = 0; j <= subdivisionsAroundHeight; j++)
		{
			for(int i = 0; i <= subdivisionsAroundAxis; i++)
			{
				real pheta = DEG_TO_RAD(i / (real)subdivisionsAroundAxis * 360.0f);
				real theta = DEG_TO_RAD(90.0f - j / (real)subdivisionsAroundHeight * 180.0f);

				my::Vec4<real> vertex(
					radius * cos(theta) * sin(pheta),
					radius * sin(theta),
					radius * cos(theta) * cos(pheta));

				pushVertex(vertex);

				if(reverse)
				{
					pushNormal(t3d::vec3Neg(t3d::vec3Normalize(vertex)));
				}
				else
				{
					pushNormal(t3d::vec3Normalize(vertex));
				}

				pushUV(i / (real)subdivisionsAroundAxis, /*1 -*/ j / (real)subdivisionsAroundHeight);
			}
		}

		for(int j = 1; j <= subdivisionsAroundHeight - 1; j++)
		{
			for(int i = 0; i <= subdivisionsAroundAxis - 1; i++)
			{
				// (i    , j - 1)
				// (i    , j    ) (i + 1, j    )
				if(reverse)
				{
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i + 1, j));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i, j));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i, j - 1));
				}
				else
				{
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i, j - 1));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i, j));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i + 1, j));
				}

				// (i    , j    ) (i + 1, j    )
				//                (i + 1, j + 1)
				if(reverse)
				{
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i, j));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i + 1, j));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i + 1, j + 1));
				}
				else
				{
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i + 1, j + 1));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i + 1, j));
					pushVertexIndex(_calculateVertexIndex(subdivisionsAroundAxis + 1, subdivisionsAroundHeight + 1, i, j));
				}
			}
		}

#ifdef _DEBUG
		t3d::VertexIndexList::const_iterator i_iter = getVertexIndexListBegin();
		for(; i_iter != getVertexIndexListEnd(); i_iter++)
		{
			_ASSERT(*i_iter < getVertexListSize());
		}
#endif
	}

	IndexSphereObject::~IndexSphereObject(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexCubeObject
	// /////////////////////////////////////////////////////////////////////////////////////

	IndexCubeObject::IndexCubeObject(
		real width,
		real height,
		real depth,
		int subdivisionsAroundWidth /*= 1*/,
		int subdivisionsAroundHeight /*= 1*/,
		int subdivisionsAroundDepth /*= 1*/,
		bool reverse /*= false*/)
	{
		_ASSERT(width >= 0);
		_ASSERT(height >= 0);
		_ASSERT(depth >= 0);

		_ASSERT(subdivisionsAroundWidth >= 1);
		_ASSERT(subdivisionsAroundHeight >= 1);
		_ASSERT(subdivisionsAroundDepth >= 1);

		pushSingleIndexPlane(
			height,
			width,
			subdivisionsAroundHeight,
			subdivisionsAroundWidth,
			NEGATIVE_Z_PLANE,
			-depth / (real)2,
			reverse);

		pushSingleIndexPlane(
			height,
			width,
			subdivisionsAroundHeight,
			subdivisionsAroundWidth,
			Z_PLANE,
			depth / (real)2,
			reverse);

		pushSingleIndexPlane(
			depth,
			width,
			subdivisionsAroundDepth,
			subdivisionsAroundWidth,
			Y_PLANE,
			height / (real)2,
			reverse);

		pushSingleIndexPlane(
			depth,
			width,
			subdivisionsAroundDepth,
			subdivisionsAroundWidth,
			NEGATIVE_Y_PLANE,
			-height / (real)2,
			reverse);

		pushSingleIndexPlane(
			depth,
			height,
			subdivisionsAroundDepth,
			subdivisionsAroundHeight,
			NEGATIVE_X_PLANE,
			-width / (real)2,
			reverse);

		pushSingleIndexPlane(
			depth,
			height,
			subdivisionsAroundDepth,
			subdivisionsAroundHeight,
			X_PLANE,
			width / (real)2,
			reverse);

#ifdef _DEBUG
		t3d::VertexIndexList::const_iterator i_iter = getVertexIndexListBegin();
		for(; i_iter != getVertexIndexListEnd(); i_iter++)
		{
			_ASSERT(*i_iter < getVertexListSize());
		}
#endif
	}

	IndexCubeObject::~IndexCubeObject(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// IndexConeObject
	// /////////////////////////////////////////////////////////////////////////////////////

	IndexConeObject::IndexConeObject(
		real radius,
		real height,
		int subdivisionsAroundAxis /*= 20*/,
		int subdivisionsAroundHeight /*= 1*/,
		int subdivisionsOnCaps /*= 1*/)
	{
		_ASSERT(subdivisionsAroundAxis >= 3);
		_ASSERT(subdivisionsAroundHeight >= 1);
		_ASSERT(subdivisionsOnCaps >= 1);

		real halfHeight = height / 2;

		for(int i = 0; i < subdivisionsAroundAxis; i++)
		{
			const real theta = DEG_TO_RAD(360 / subdivisionsAroundAxis * i);

			my::Vec4<real> nor(
				height * cos(theta),
				radius,
				height * sin(theta));

			t3d::vec3NormalizeSelf(nor);

			for(int j = 0; j <= subdivisionsAroundHeight; j++)
			{
				real y = halfHeight - height / subdivisionsAroundHeight * j;
				real r = (halfHeight - y) * radius / height;
				real x = r * cos(theta);
				real z = r * sin(theta);

				pushVertex(x, y, z);
				pushNormal(nor);
				pushUV(i / (real)subdivisionsAroundAxis, /*1 -*/ j / (real)subdivisionsAroundHeight);
			}

			for(int j = 0; j <= subdivisionsOnCaps; j++)
			{
				real y = -halfHeight;
				real r = radius - radius / subdivisionsOnCaps * j;
				real x = r * cos(theta);
				real z = r * sin(theta);

				pushVertex(x, y, z);
				pushNormal(0, -1, 0);
				pushUV(i / (real)subdivisionsAroundAxis, /*1 -*/ j / (real)subdivisionsAroundHeight);
			}

			for(int j = 0; j < subdivisionsAroundHeight + subdivisionsOnCaps + 1; j++)
			{
				const int last_index = (i - 1 + subdivisionsAroundAxis) % subdivisionsAroundAxis;

				if(j != 0)
				{
					/****************************************************************************
					*	2   0
					*   |  /
					*	1
					****************************************************************************/
					pushVertexIndex(i * (subdivisionsAroundHeight + subdivisionsOnCaps + 2) + j);
					pushVertexIndex(last_index * (subdivisionsAroundHeight + subdivisionsOnCaps + 2) + j + 1);
					pushVertexIndex(last_index * (subdivisionsAroundHeight + subdivisionsOnCaps + 2) + j);
				}

				if(j != subdivisionsAroundHeight + subdivisionsOnCaps)
				{
					/****************************************************************************
					*	    0
					*       |
					*	2 - 1
					****************************************************************************/
					pushVertexIndex(i * (subdivisionsAroundHeight + subdivisionsOnCaps + 2) + j);
					pushVertexIndex(i * (subdivisionsAroundHeight + subdivisionsOnCaps + 2) + j + 1);
					pushVertexIndex(last_index * (subdivisionsAroundHeight + subdivisionsOnCaps + 2) + j + 1);
				}
			}
		}

#ifdef _DEBUG
		t3d::VertexIndexList::const_iterator i_iter = getVertexIndexListBegin();
		for(; i_iter != getVertexIndexListEnd(); i_iter++)
		{
			_ASSERT(*i_iter < getVertexListSize());
		}
#endif
	}

	IndexConeObject::~IndexConeObject(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// BoneAssignmentIndexObject
	// /////////////////////////////////////////////////////////////////////////////////////

	const t3d::VertexList & BoneAssignmentIndexObject::getOriginalVertexList(void) const
	{
		return m_origVertexList;
	}

	t3d::VertexList & BoneAssignmentIndexObject::getOriginalVertexList(void)
	{
		return m_origVertexList;
	}

	void BoneAssignmentIndexObject::pushOriginalVertex(real x, real y, real z)
	{
		getOriginalVertexList().push_back(my::Vec4<real>(x, y, z));
	}

	void BoneAssignmentIndexObject::pushOriginalVertex(real x, real y, real z, const t3d::Mat4<real> & mmat)
	{
		getOriginalVertexList().push_back(my::Vec4<real>(x, y, z) * mmat);
	}

	void BoneAssignmentIndexObject::pushOriginalVertex(t3d::VertexList::const_reference vver)
	{
		getOriginalVertexList().push_back(vver);
	}

	void BoneAssignmentIndexObject::pushOriginalVertex(t3d::VertexList::const_reference vver, const t3d::Mat4<real> & mmat)
	{
		getOriginalVertexList().push_back(vver * mmat);
	}

	t3d::VertexList::const_iterator BoneAssignmentIndexObject::getOriginalVertexListBegin(void) const
	{
		return getOriginalVertexList().begin();
	}

	t3d::VertexList::const_iterator BoneAssignmentIndexObject::getOriginalVertexListEnd(void) const
	{
		return getOriginalVertexList().end();
	}

	t3d::VertexList::iterator BoneAssignmentIndexObject::getOriginalVertexListBegin(void)
	{
		return getOriginalVertexList().begin();
	}

	t3d::VertexList::iterator BoneAssignmentIndexObject::getOriginalVertexListEnd(void)
	{
		return getOriginalVertexList().end();
	}

	const t3d::NormalList & BoneAssignmentIndexObject::getOriginalNormalList(void) const
	{
		return m_origNormalList;
	}

	t3d::NormalList & BoneAssignmentIndexObject::getOriginalNormalList(void)
	{
		return m_origNormalList;
	}

	void BoneAssignmentIndexObject::pushOriginalNormal(real x, real y, real z)
	{
		getOriginalNormalList().push_back(my::Vec4<real>(x, y, z));
	}

	void BoneAssignmentIndexObject::pushOriginalNormal(real x, real y, real z, const t3d::Mat4<real> & mmat)
	{
		getOriginalNormalList().push_back(my::Vec4<real>(x, y, z) * mmat);
	}

	void BoneAssignmentIndexObject::pushOriginalNormal(t3d::NormalList::const_reference vver)
	{
		getOriginalNormalList().push_back(vver);
	}

	void BoneAssignmentIndexObject::pushOriginalNormal(t3d::NormalList::const_reference vver, const t3d::Mat4<real> & mmat)
	{
		getOriginalNormalList().push_back(vver * mmat);
	}

	t3d::NormalList::const_iterator BoneAssignmentIndexObject::getOriginalNormalListBegin(void) const
	{
		return getOriginalNormalList().begin();
	}

	t3d::NormalList::const_iterator BoneAssignmentIndexObject::getOriginalNormalListEnd(void) const
	{
		return getOriginalNormalList().end();
	}

	t3d::NormalList::iterator BoneAssignmentIndexObject::getOriginalNormalListBegin(void)
	{
		return getOriginalNormalList().begin();
	}

	t3d::NormalList::iterator BoneAssignmentIndexObject::getOriginalNormalListEnd(void)
	{
		return getOriginalNormalList().end();
	}

	const t3d::BoneAssignmentList & BoneAssignmentIndexObject::getBoneAssignmentList(void) const
	{
		return m_boneAssignmentList;
	}

	t3d::BoneAssignmentList & BoneAssignmentIndexObject::getBoneAssignmentList(void)
	{
		return m_boneAssignmentList;
	}

	void BoneAssignmentIndexObject::pushBoneAssignment(size_t vertex_i, size_t bone_i, real weight)
	{
		getBoneAssignmentList().push_back(t3d::BoneAssignment(vertex_i, bone_i, weight));
	}

	void BoneAssignmentIndexObject::pushBoneAssignment(t3d::BoneAssignmentList::const_reference boneAssignment)
	{
		getBoneAssignmentList().push_back(boneAssignment);
	}

	t3d::BoneAssignmentList::const_iterator BoneAssignmentIndexObject::getBoneAssignmentListBegin(void) const
	{
		return getBoneAssignmentList().begin();
	}

	t3d::BoneAssignmentList::const_iterator BoneAssignmentIndexObject::getBoneAssignmentListEnd(void) const
	{
		return getBoneAssignmentList().end();
	}

	t3d::BoneAssignmentList::const_iterator BoneAssignmentIndexObject::getBoneAssignmentListBegin(void)
	{
		return getBoneAssignmentList().begin();
	}

	t3d::BoneAssignmentList::const_iterator BoneAssignmentIndexObject::getBoneAssignmentListEnd(void)
	{
		return getBoneAssignmentList().end();
	}

	BoneAssignmentIndexObject::BoneAssignmentIndexObject(void)
	{
	}

	BoneAssignmentIndexObject::~BoneAssignmentIndexObject(void)
	{
	}

	void BoneAssignmentIndexObject::bindVertexListFromBoneTransformList(
		const t3d::BoneTransformList & boneTransformList)
	{
		t3d::bindVertexListFromBoneTransformList(
			getVertexList(),
			getOriginalVertexList(),
			getBoneAssignmentList(),
			boneTransformList);
	}

	void BoneAssignmentIndexObject::bindVertexListNormalListFromBoneTransformList(
		const t3d::BoneTransformList & boneTransformList)
	{
		t3d::bindVertexListNormalListFromBoneTransformList(
			getVertexList(),
			getNormalList(),
			getOriginalVertexList(),
			getOriginalNormalList(),
			getBoneAssignmentList(),
			boneTransformList);
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// BoneAssignmentIndexObjectFromOgreMesh
	// /////////////////////////////////////////////////////////////////////////////////////

	BoneAssignmentIndexObjectFromOgreMesh::BoneAssignmentIndexObjectFromOgreMesh(
		IOStreamPtr meshStream)
	{
		TiXmlDocument doc;
		doc.LoadFile(static_cast<FILE *>(meshStream->getHandle()), TIXML_DEFAULT_ENCODING);

		DEFINE_XML_ELEMENT_SIMPLE(mesh, (&doc));

		DEFINE_XML_ELEMENT_SIMPLE(sharedgeometry, mesh);

		DEFINE_XML_ATTRIBUTE_INT_SIMPLE(vertexcount, sharedgeometry);

		if(vertexcount < 0)
			T3D_CUSEXCEPT(_T("invalid sharedgeometry.vertexcount"));

		DEFINE_XML_ELEMENT_SIMPLE(vertexbuffer, sharedgeometry);

		DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(positions, vertexbuffer);

		DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(normals, vertexbuffer);

		DEFINE_XML_ATTRIBUTE_INT_SIMPLE(texture_coords, vertexbuffer);

		if(positions)
		{
			TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
			for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
			{
				DEFINE_XML_ELEMENT_SIMPLE(position, vertex);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, position);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, position);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, position);

				pushOriginalVertex((real)x, (real)y, (real)-z); // ***
			}

			if((int)getOriginalVertexList().size() != vertexcount)
				T3D_CUSEXCEPT(_T("cannot match vertex count"));
		}

		if(normals)
		{
			TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
			for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
			{
				DEFINE_XML_ELEMENT_SIMPLE(normal, vertex);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, normal);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, normal);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, normal);

				pushOriginalNormal((real)x, (real)y, (real)-z); // ***
			}

			if((int)getOriginalNormalList().size() != vertexcount)
				T3D_CUSEXCEPT(_T("cannot match normal count"));
		}

		if(texture_coords > 0)
		{
			TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
			for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
			{
				DEFINE_XML_ELEMENT_SIMPLE(texcoord, vertex);

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(u, texcoord);

				if(u < 0)
				{
					if(u > -EPSILON_E6)
						u = 0;
					else
						T3D_CUSEXCEPT(_T("invalid texcoord.u"));
				}
				else if(u > 1)
				{
					if(u < 1 + EPSILON_E6)
						u = 1;
					else
						T3D_CUSEXCEPT(_T("invalid texcoord.u"));
				}

				DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(v, texcoord);

				if(v < 0)
				{
					if(v > -EPSILON_E6)
						v = 0;
					else
						T3D_CUSEXCEPT(_T("invalid texcoord.u"));
				}
				else if(v > 1)
				{
					if(v < 1 + EPSILON_E6)
						v = 1;
					else
						T3D_CUSEXCEPT(_T("invalid texcoord.u"));
				}

				pushUV((real)u, (real)(/*1 -*/ v)); // ***
			}

			if((int)getUVListSize() != vertexcount)
				T3D_CUSEXCEPT(_T("cannot match uv count"));
		}

		DEFINE_XML_ELEMENT_SIMPLE(submeshes, mesh);

		TiXmlElement * submesh = submeshes->FirstChildElement("submesh");
		for(; submesh != NULL; submesh = submesh->NextSiblingElement("submesh"))
		{
			DEFINE_XML_ELEMENT_SIMPLE(faces, submesh);

			DEFINE_XML_ATTRIBUTE_INT(face_count, faces, count);

			if(face_count > 0)
			{
				int prevVertexIndexListSize = (int)getVertexIndexList().size();

				TiXmlElement * face = faces->FirstChildElement("face");
				for(; face != NULL; face = face->NextSiblingElement("face"))
				{
					DEFINE_XML_ATTRIBUTE_INT_SIMPLE(v1, face);

					if(v1 < 0 || v1 >= vertexcount)
						T3D_CUSEXCEPT(_T("invalid face.v1"));

					DEFINE_XML_ATTRIBUTE_INT_SIMPLE(v2, face);

					if(v2 < 0 || v2 >= vertexcount)
						T3D_CUSEXCEPT(_T("invalid face.v2"));

					DEFINE_XML_ATTRIBUTE_INT_SIMPLE(v3, face);

					if(v3 < 0 || v3 >= vertexcount)
						T3D_CUSEXCEPT(_T("invalid face.v3"));

					pushVertexIndex(v1);
					pushVertexIndex(v3); // ***
					pushVertexIndex(v2); // ***
				}

				if((int)getVertexIndexList().size() - prevVertexIndexListSize != face_count * 3)
					T3D_CUSEXCEPT(_T("cannot match face count"));
			}
		}

		DEFINE_XML_ELEMENT_SIMPLE(boneassignments, mesh);

		TiXmlElement * vertexboneassignment = boneassignments->FirstChildElement("vertexboneassignment");
		for(; vertexboneassignment != NULL; vertexboneassignment = vertexboneassignment->NextSiblingElement("vertexboneassignment"))
		{
			DEFINE_XML_ATTRIBUTE_INT_SIMPLE(vertexindex, vertexboneassignment);

			DEFINE_XML_ATTRIBUTE_INT_SIMPLE(boneindex, vertexboneassignment);

			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(weight, vertexboneassignment);

			pushBoneAssignment(vertexindex, boneindex, (real)weight);
		}

		getVertexList() = getOriginalVertexList();

		getNormalList() = getOriginalNormalList();
	}

	BoneAssignmentIndexObjectFromOgreMesh::~BoneAssignmentIndexObjectFromOgreMesh(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// SkeletonAnimationsFromOgreSkeleton
	// /////////////////////////////////////////////////////////////////////////////////////

	void SkeletonAnimationsFromOgreSkeleton::pushOrigBoneNode(t3d::BoneNodeList::const_reference origBoneNode)
	{
		m_origBoneNodeList.push_back(origBoneNode);
	}

	void SkeletonAnimationsFromOgreSkeleton::pushOrigBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end)
	{
		m_origBoneNodeList.insert(m_origBoneNodeList.end(), begin, end);
	}

	t3d::BoneNodeList::const_iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeListBegin(void) const
	{
		return m_origBoneNodeList.begin();
	}

	t3d::BoneNodeList::iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeListBegin(void)
	{
		return m_origBoneNodeList.begin();
	}

	t3d::BoneNodeList::const_iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeListEnd(void) const
	{
		return m_origBoneNodeList.end();
	}

	t3d::BoneNodeList::iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeListEnd(void)
	{
		return m_origBoneNodeList.end();
	}

	t3d::BoneNodeList::size_type SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeListSize(void) const
	{
		return m_origBoneNodeList.size();
	}

	void SkeletonAnimationsFromOgreSkeleton::resizeOrigBoneNodeList(t3d::BoneNodeList::size_type size)
	{
		m_origBoneNodeList.resize(size);
	}

	void SkeletonAnimationsFromOgreSkeleton::clearOrigBoneNodeList(void)
	{
		m_origBoneNodeList.clear();
	}

	t3d::BoneNodeList::reference SkeletonAnimationsFromOgreSkeleton::origBoneNodeAt(t3d::BoneNodeList::size_type i)
	{
		_ASSERT(i < getOrigBoneNodeListSize());

		return m_origBoneNodeList[i];
	}

	t3d::BoneNodeList::const_reference SkeletonAnimationsFromOgreSkeleton::origBoneNodeAt(t3d::BoneNodeList::size_type i) const
	{
		_ASSERT(i < getOrigBoneNodeListSize());

		return m_origBoneNodeList[i];
	}

	t3d::BoneNodeList & SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeList(void)
	{
		return m_origBoneNodeList;
	}

	const t3d::BoneNodeList & SkeletonAnimationsFromOgreSkeleton::getOrigBoneNodeList(void) const
	{
		return m_origBoneNodeList;
	}

	void SkeletonAnimationsFromOgreSkeleton::pushOrigBoneInverseTransform(t3d::BoneTransformList::const_reference origBoneInverseTransform)
	{
		m_origBoneInverseTransformList.push_back(origBoneInverseTransform);
	}

	void SkeletonAnimationsFromOgreSkeleton::pushOrigBoneInverseTransformList(t3d::BoneTransformList::const_iterator begin, t3d::BoneTransformList::const_iterator end)
	{
		m_origBoneInverseTransformList.insert(m_origBoneInverseTransformList.end(), begin, end);
	}

	t3d::BoneTransformList::const_iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformListBegin(void) const
	{
		return m_origBoneInverseTransformList.begin();
	}

	t3d::BoneTransformList::iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformListBegin(void)
	{
		return m_origBoneInverseTransformList.begin();
	}

	t3d::BoneTransformList::const_iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformListEnd(void) const
	{
		return m_origBoneInverseTransformList.end();
	}

	t3d::BoneTransformList::iterator SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformListEnd(void)
	{
		return m_origBoneInverseTransformList.end();
	}

	t3d::BoneTransformList::size_type SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformListSize(void) const
	{
		return m_origBoneInverseTransformList.size();
	}

	void SkeletonAnimationsFromOgreSkeleton::resizeOrigBoneInverseTransformList(t3d::BoneTransformList::size_type size)
	{
		m_origBoneInverseTransformList.resize(size);
	}

	void SkeletonAnimationsFromOgreSkeleton::clearOrigBoneInverseTransformList(void)
	{
		m_origBoneInverseTransformList.clear();
	}

	t3d::BoneTransformList::reference SkeletonAnimationsFromOgreSkeleton::origBoneInverseTransformAt(t3d::BoneTransformList::size_type i)
	{
		_ASSERT(i < getOrigBoneInverseTransformListSize());

		return m_origBoneInverseTransformList[i];
	}

	t3d::BoneTransformList::const_reference SkeletonAnimationsFromOgreSkeleton::origBoneInverseTransformAt(t3d::BoneTransformList::size_type i) const
	{
		_ASSERT(i < getOrigBoneInverseTransformListSize());

		return m_origBoneInverseTransformList[i];
	}

	t3d::BoneTransformList & SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformList(void)
	{
		return m_origBoneInverseTransformList;
	}

	const t3d::BoneTransformList & SkeletonAnimationsFromOgreSkeleton::getOrigBoneInverseTransformList(void) const
	{
		return m_origBoneInverseTransformList;
	}

	void SkeletonAnimationsFromOgreSkeleton::pushRootIndex(t3d::BoneIndexList::const_reference rootIndex)
	{
		m_rootIndexList.push_back(rootIndex);
	}

	void SkeletonAnimationsFromOgreSkeleton::pushRootIndexList(t3d::BoneIndexList::const_iterator begin, t3d::BoneIndexList::const_iterator end)
	{
		m_rootIndexList.insert(m_rootIndexList.end(), begin, end);
	}

	t3d::BoneIndexList::const_iterator SkeletonAnimationsFromOgreSkeleton::getRootIndexListBegin(void) const
	{
		return m_rootIndexList.begin();
	}

	t3d::BoneIndexList::iterator SkeletonAnimationsFromOgreSkeleton::getRootIndexListBegin(void)
	{
		return m_rootIndexList.begin();
	}

	t3d::BoneIndexList::const_iterator SkeletonAnimationsFromOgreSkeleton::getRootIndexListEnd(void) const
	{
		return m_rootIndexList.end();
	}

	t3d::BoneIndexList::iterator SkeletonAnimationsFromOgreSkeleton::getRootIndexListEnd(void)
	{
		return m_rootIndexList.end();
	}

	t3d::BoneIndexList::size_type SkeletonAnimationsFromOgreSkeleton::getRootIndexListSize(void) const
	{
		return m_rootIndexList.size();
	}

	void SkeletonAnimationsFromOgreSkeleton::resizeRootIndexList(t3d::BoneIndexList::size_type size)
	{
		m_rootIndexList.resize(size);
	}

	void SkeletonAnimationsFromOgreSkeleton::clearRootIndexList(void)
	{
		m_rootIndexList.clear();
	}

	t3d::BoneIndexList::reference SkeletonAnimationsFromOgreSkeleton::rootIndexAt(t3d::BoneIndexList::size_type i)
	{
		_ASSERT(i < getRootIndexListSize());

		return m_rootIndexList[i];
	}

	t3d::BoneIndexList::const_reference SkeletonAnimationsFromOgreSkeleton::rootIndexAt(t3d::BoneIndexList::size_type i) const
	{
		_ASSERT(i < getRootIndexListSize());

		return m_rootIndexList[i];
	}

	t3d::BoneIndexList & SkeletonAnimationsFromOgreSkeleton::getRootIndexList(void)
	{
		return m_rootIndexList;
	}

	const t3d::BoneIndexList & SkeletonAnimationsFromOgreSkeleton::getRootIndexList(void) const
	{
		return m_rootIndexList;
	}

	void SkeletonAnimationsFromOgreSkeleton::insertBoneIndex(const std::basic_string<char> & boneName, size_t bone_i)
	{
		_ASSERT(!isBoneIndexExistent(boneName));

		m_boneIndexMap.insert(std::map<std::basic_string<char>, size_t>::value_type(boneName, bone_i));
	}

	bool SkeletonAnimationsFromOgreSkeleton::isBoneIndexExistent(const std::basic_string<char> & boneName) const
	{
		return m_boneIndexMap.end() != m_boneIndexMap.find(boneName);
	}

	size_t SkeletonAnimationsFromOgreSkeleton::getBoneIndex(const std::basic_string<char> & boneName) const
	{
		_ASSERT(isBoneIndexExistent(boneName));

		return m_boneIndexMap.find(boneName)->second;
	}

	SkeletonAnimationsFromOgreSkeleton::SkeletonAnimationsFromOgreSkeleton(
		IOStreamPtr skeletonStream)
	{
		TiXmlDocument doc;
		doc.LoadFile(static_cast<FILE *>(skeletonStream->getHandle()), TIXML_DEFAULT_ENCODING);

		DEFINE_XML_ELEMENT_SIMPLE(skeleton, (&doc));

		DEFINE_XML_ELEMENT_SIMPLE(bones, skeleton);

		TiXmlElement * bone = bones->FirstChildElement("bone");
		for(; bone != NULL; bone = bone->NextSiblingElement("bone"))
		{
			DEFINE_XML_ELEMENT_SIMPLE(position, bone);

			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, position);

			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, position);

			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, position);

			DEFINE_XML_ELEMENT_SIMPLE(rotation, bone);

			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(angle, rotation);

			DEFINE_XML_ELEMENT_SIMPLE(axis, rotation);

			DEFINE_XML_ATTRIBUTE_DOUBLE(axis_x, axis, x);

			DEFINE_XML_ATTRIBUTE_DOUBLE(axis_y, axis, y);

			DEFINE_XML_ATTRIBUTE_DOUBLE(axis_z, axis, z);

			pushOrigBoneNode(t3d::BoneNode(
				my::Vec4<real>((real)x, (real)y, (real)-z),
				t3d::buildQuatFromAngleAxis((real)-angle, t3d::vec3Normalize(my::Vec4<real>((real)axis_x, (real)axis_y, (real)-axis_z))))); // ***

			DEFINE_XML_ATTRIBUTE_CHAR(bone_name, bone, name);

			insertBoneIndex(bone_name, getOrigBoneNodeListSize() - 1);
		}

		DEFINE_XML_ELEMENT_SIMPLE(bonehierarchy, skeleton);

		TiXmlElement * boneparent = bonehierarchy->FirstChildElement("boneparent");
		for(; boneparent != NULL; boneparent = boneparent->NextSiblingElement("boneparent"))
		{
			DEFINE_XML_ATTRIBUTE_CHAR_SIMPLE(bone, boneparent);

			if(1 != m_boneIndexMap.count(bone))
				T3D_CUSEXCEPT(_T("cannot match bone index"));

			DEFINE_XML_ATTRIBUTE_CHAR_SIMPLE(parent, boneparent);

			if(1 != m_boneIndexMap.count(parent))
				T3D_CUSEXCEPT(_T("cannot match parent bone index"));

			if(m_boneIndexMap[bone] > INT_MAX)
				T3D_CUSEXCEPT(_T("bone index overflow"));

			if(m_boneIndexMap[parent] > INT_MAX)
				T3D_CUSEXCEPT(_T("parent bone index overflow"));

			if(!origBoneNodeAt(m_boneIndexMap[bone]).isRoot())
				T3D_CUSEXCEPT(_T("multi parent is not supported"));

			origBoneNodeAt(getBoneIndex(bone)).setParent(getBoneIndex(parent));

			origBoneNodeAt(getBoneIndex(parent)).pushChild(getBoneIndex(bone));
		}

		DEFINE_XML_ELEMENT_SIMPLE(animations, skeleton);

		TiXmlElement * animation = animations->FirstChildElement("animation");
		for(; animation != NULL; animation = animation->NextSiblingElement("animation"))
		{
			DEFINE_XML_ATTRIBUTE_CHAR(animation_name, animation, name);

			if(isSkeletonAnimationExistent(animation_name))
				T3D_CUSEXCEPT(_T("the animation name has already existed"));

			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(length, animation);

			//setSkeletonAnimationNode(animation_name, SkeletonAnimationNode(animation_name, 0, (real)length));
			insertSkeletonAnimation(animation_name, SkeletonAnimation());

			//SkeletonAnimationNode & skeletonAnimationNode = getSkeletonAnimationNode(animation_name);
			SkeletonAnimation & skeletonAnimation = getSkeletonAnimation(animation_name);

			skeletonAnimation.setNextAnimationName(animation_name);

			DEFINE_XML_ELEMENT_SIMPLE(tracks, animation);

			TiXmlElement * track = tracks->FirstChildElement("track");
			for(; track != NULL; track = track->NextSiblingElement("track"))
			{
				DEFINE_XML_ATTRIBUTE_CHAR_SIMPLE(bone, track);

				if(getBoneIndex(bone) != skeletonAnimation.getBoneAnimationNodeListSize())
					T3D_CUSEXCEPT(_T("invalid bone animation track"));

				//skeletonAnimationNode.pushBoneAnimation(BoneAnimation());
				skeletonAnimation.pushBoneAnimationNode(t3d::BoneAnimationNode());

				//BoneAnimation & boneAnimation = skeletonAnimationNode.boneAnimationAt(skeletonAnimationNode.getBoneAnimationListSize() - 1);
				t3d::BoneAnimationNode & boneAnimationNode = skeletonAnimation.getBoneAnimationNodeList().back();

//				boneAnimationNode.setParent(origBoneNodeAt(getBoneIndex(bone)).getParent());

//				boneAnimationNode.getChildList() = origBoneNodeAt(getBoneIndex(bone)).getChildList();

				DEFINE_XML_ELEMENT_SIMPLE(keyframes, track);

				TiXmlElement * keyframe = keyframes->FirstChildElement("keyframe");
				for(; keyframe != NULL; keyframe = keyframe->NextSiblingElement("keyframe"))
				{
					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(time, keyframe);

					DEFINE_XML_ELEMENT_SIMPLE(translate, keyframe);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, translate);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, translate);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, translate);

					DEFINE_XML_ELEMENT_SIMPLE(rotate, keyframe);

					DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(angle, rotate);

					DEFINE_XML_ELEMENT_SIMPLE(axis, rotate);

					DEFINE_XML_ATTRIBUTE_DOUBLE(axis_x, axis, x);

					DEFINE_XML_ATTRIBUTE_DOUBLE(axis_y, axis, y);

					DEFINE_XML_ATTRIBUTE_DOUBLE(axis_z, axis, z);

					//boneAnimation.pushBoneKeyFrame(
					//	t3d::BoneKeyFrame(
					//		my::Vec4<real>((real)x, (real)y, (real)-z),
					//		t3d::buildQuatFromAngleAxis((real)-angle, t3d::vec3Normalize(my::Vec4<real>((real)axis_x, (real)axis_y, (real)-axis_z))), // ***
					//		(real)time));

					boneAnimationNode.pushBoneKeyFrame(
						t3d::BoneKeyFrame(
							my::Vec4<real>((real)x, (real)y, (real)-z),
							t3d::buildQuatFromAngleAxis((real)-angle, t3d::vec3Normalize(my::Vec4<real>((real)axis_x, (real)axis_y, (real)-axis_z))), // ***
							(real)time));
				}
			}

			//if(skeletonAnimationNode.getBoneAnimationListSize() != getOrigBoneNodeListSize())
			if(skeletonAnimation.getBoneAnimationNodeListSize() != getOrigBoneNodeListSize())
				T3D_CUSEXCEPT(_T("cannot match tracks count"));
		}

		//SkeletonAnimationNodeMap::iterator skeleton_animation_iter = m_skeletonAnimationNodeMap.begin();
		//for(; skeleton_animation_iter != m_skeletonAnimationNodeMap.end(); skeleton_animation_iter++)
		//{
		//	size_t i = 0;
		//	for(; i < getOrigBoneNodeListSize(); i++)
		//	{
		//		BoneAnimation & boneAnimation = skeleton_animation_iter->second.boneAnimationAt(i);

		//		t3d::BoneKeyFrameList::iterator bone_key_iter = boneAnimation.getBoneKeyFrameList().begin();
		//		for(; bone_key_iter != boneAnimation.getBoneKeyFrameList().end(); bone_key_iter++)
		//		{
		//			bone_key_iter->setPosition(t3d::vec3Add(origBoneNodeAt(i).getPosition(), bone_key_iter->getPosition()));

		//			bone_key_iter->setOrientation(origBoneNodeAt(i).getOrientation() * bone_key_iter->getOrientation());
		//		}
		//	}
		//}

		//if(getOrigBoneNodeListSize() >= INT_MAX)
		//	T3D_CUSEXCEPT(_T("too large orig bone node list size"));

		resizeOrigBoneInverseTransformList(getOrigBoneNodeListSize());

		getRootIndexList() = t3d::STreeNode::getRootIndexList(getOrigBoneNodeList());

		t3d::updateBoneInverseTransformListFromBoneNodeList(
				getOrigBoneInverseTransformList(),
				getOrigBoneNodeList(),
				my::Mat4<real>::IDENTITY,
				my::Mat4<real>::IDENTITY,
				getRootIndexListBegin(),
				getRootIndexListEnd());

		getBoneNodeList() = getOrigBoneNodeList();

		//resizeBoneTransformList(getOrigBoneNodeListSize());
	}

	SkeletonAnimationsFromOgreSkeleton::~SkeletonAnimationsFromOgreSkeleton(void)
	{
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// DrawnHelper
	// /////////////////////////////////////////////////////////////////////////////////////

	DrawnHelper::DrawnHelper(void)
		: sphere0(1)
		, plane(100, 100)
		, cube(2, 2, 2)
		, cone(1, 1)
	{
	}

	DrawnHelper::~DrawnHelper(void)
	{
	}

	void DrawnHelper::drawLinePointAndPointZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & p0,
		const t3d::Vec4<real> & p1,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		rc->clearVertexList();
		rc->pushVertex(p0, mmat);
		rc->pushVertex(p1, mmat);
		rc->drawLineListZBufferRW(color);
	}

	void DrawnHelper::drawLinePointAndNormalZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & point,
		const t3d::Vec4<real> & normal,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		drawLinePointAndPointZBufferRW(rc, point, t3d::vec3Add(point, normal), color, mmat);
	}

	void DrawnHelper::drawTriangleWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		rc->clearVertexList();
		rc->pushVertex(v0, mmat);
		rc->pushVertex(v1, mmat);
		rc->pushVertex(v2, mmat);
		rc->drawTriangleListWireZBufferRW(color);
	}

	void DrawnHelper::drawTriangleGouraudZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		rc->clearVertexList();
		rc->pushVertex(v0, mmat);
		rc->pushVertex(v1, mmat);
		rc->pushVertex(v2, mmat);

		t3d::Vec4<real> normal = calculateTriangleNormal(v0, v1, v2) * mrot;
		rc->clearNormalList();
		rc->pushNormal(normal);
		rc->pushNormal(normal);
		rc->pushNormal(normal);

		rc->drawTriangleListGouraudZBufferRW();
	}

	void DrawnHelper::drawTriangleGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		rc->clearVertexList();
		rc->pushVertex(v0, mmat);
		rc->pushVertex(v1, mmat);
		rc->pushVertex(v2, mmat);

		t3d::Vec4<real> normal = calculateTriangleNormal(v0, v1, v2) * mrot;
		rc->clearNormalList();
		rc->pushNormal(normal);
		rc->pushNormal(normal);
		rc->pushNormal(normal);

		rc->clearUVList();
		rc->pushUV(t0);
		rc->pushUV(t1);
		rc->pushUV(t2);

		rc->drawTriangleListGouraudTextureZBufferRW();
	}

	void DrawnHelper::drawTriangleGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		rc->clearVertexList();
		rc->pushVertex(v0, mmat);
		rc->pushVertex(v1, mmat);
		rc->pushVertex(v2, mmat);

		t3d::Vec4<real> normal = calculateTriangleNormal(v0, v1, v2) * mrot;
		rc->clearNormalList();
		rc->pushNormal(normal);
		rc->pushNormal(normal);
		rc->pushNormal(normal);

		rc->clearUVList();
		rc->pushUV(t0);
		rc->pushUV(t1);
		rc->pushUV(t2);

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRW();
	}

	void DrawnHelper::drawSphereWireZBufferRW(
		t3d::RenderContext * rc,
		real radius,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(radius, radius, radius));

		sphere0.drawWireZBufferRW(rc, color, mScaler * mmat);
	}

	void DrawnHelper::drawSphereGouraudZBufferRW(
		t3d::RenderContext * rc,
		real radius,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(radius, radius, radius));

		sphere0.drawGouraudZBufferRW(rc, mScaler * mmat, mrot);
	}

	void DrawnHelper::drawSphereGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		real radius,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(radius, radius, radius));

		sphere0.drawGouraudTextureZBufferRW(rc, mScaler * mmat, mrot);
	}

	void DrawnHelper::drawCubeWireZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> halfSize,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(halfSize.x, halfSize.y, halfSize.z));

		cube.drawWireZBufferRW(rc, color, mScaler * mmat);
	}

	void DrawnHelper::drawCubeGouraudZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> halfSize,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(halfSize.x, halfSize.y, halfSize.z));

		cube.drawGouraudZBufferRW(rc, mScaler * mmat, mrot);
	}

	void DrawnHelper::drawCubeGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> halfSize,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(halfSize.x, halfSize.y, halfSize.z));

		cube.drawGouraudTextureZBufferRW(rc, mScaler * mmat, mrot);
	}

	void DrawnHelper::drawPlaneWireZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> direction,
		real distance,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		real cosTheta = t3d::vec3CosTheta(my::Vec4<real>::UNIT_Y, direction);

		t3d::Mat4<real> mRotation;

		if(cosTheta > 0 && IS_ZERO_FLOAT(cosTheta - 1))
		{
			mRotation = my::Mat4<real>::IDENTITY;
		}
		else if(cosTheta < 0 && IS_ZERO_FLOAT(cosTheta + 1))
		{
			mRotation = t3d::mat3RotX(DEG_TO_RAD(180));
		}
		else
		{
			mRotation = t3d::buildRotationMatrixFromQuatLH(
				t3d::buildQuatFromAngleAxis(acos(cosTheta), t3d::vec3Normalize(t3d::vec3Cross(my::Vec4<real>::UNIT_Y, direction))));
		}

		t3d::Mat4<real> mTransform = t3d::mat3Mov(my::Vec4<real>(0, distance, 0));

		plane.drawWireZBufferRW(rc, color, mTransform * mRotation * mmat);
	}

	void DrawnHelper::drawPlaneGouraudZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> direction,
		real distance,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		real cosTheta = t3d::vec3CosTheta(my::Vec4<real>::UNIT_Y, direction);

		t3d::Mat4<real> mRotation;

		if(cosTheta > 0 && IS_ZERO_FLOAT(cosTheta - 1))
		{
			mRotation = my::Mat4<real>::IDENTITY;
		}
		else if(cosTheta < 0 && IS_ZERO_FLOAT(cosTheta + 1))
		{
			mRotation = t3d::mat3RotX(DEG_TO_RAD(180));
		}
		else
		{
			mRotation = t3d::buildRotationMatrixFromQuatLH(
				t3d::buildQuatFromAngleAxis(acos(cosTheta), t3d::vec3Normalize(t3d::vec3Cross(my::Vec4<real>::UNIT_Y, direction))));
		}

		t3d::Mat4<real> mTransform = t3d::mat3Mov(my::Vec4<real>(0, distance, 0));

		plane.drawGouraudZBufferRW(rc, mTransform * mRotation * mmat, mRotation * mrot);
	}

	void DrawnHelper::drawPlaneGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> direction,
		real distance,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		real cosTheta = t3d::vec3CosTheta(my::Vec4<real>::UNIT_Y, direction);

		t3d::Mat4<real> mRotation;

		if(cosTheta > 0 && IS_ZERO_FLOAT(cosTheta - 1))
		{
			mRotation = my::Mat4<real>::IDENTITY;
		}
		else if(cosTheta < 0 && IS_ZERO_FLOAT(cosTheta + 1))
		{
			mRotation = t3d::mat3RotX(DEG_TO_RAD(180));
		}
		else
		{
			mRotation = t3d::buildRotationMatrixFromQuatLH(
				t3d::buildQuatFromAngleAxis(acos(cosTheta), t3d::vec3Normalize(t3d::vec3Cross(my::Vec4<real>::UNIT_Y, direction))));
		}

		t3d::Mat4<real> mTransform = t3d::mat3Mov(my::Vec4<real>(0, distance, 0));

		plane.drawGouraudTextureZBufferRW(rc, mTransform * mRotation * mmat, mRotation * mrot);
	}

	void DrawnHelper::drawPlaneGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		t3d::Vec4<real> direction,
		real distance,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		real cosTheta = t3d::vec3CosTheta(my::Vec4<real>::UNIT_Y, direction);

		t3d::Mat4<real> mRotation;

		if(cosTheta > 0 && IS_ZERO_FLOAT(cosTheta - 1))
		{
			mRotation = my::Mat4<real>::IDENTITY;
		}
		else if(cosTheta < 0 && IS_ZERO_FLOAT(cosTheta + 1))
		{
			mRotation = t3d::mat3RotX(DEG_TO_RAD(180));
		}
		else
		{
			mRotation = t3d::buildRotationMatrixFromQuatLH(
				t3d::buildQuatFromAngleAxis(acos(cosTheta), t3d::vec3Normalize(t3d::vec3Cross(my::Vec4<real>::UNIT_Y, direction))));
		}

		t3d::Mat4<real> mTransform = t3d::mat3Mov(my::Vec4<real>(0, distance, 0));

		plane.drawGouraudTexturePerspectiveLPZBufferRW(rc, mTransform * mRotation * mmat, mRotation * mrot);
	}

	void DrawnHelper::drawConeWireZBufferRW(
		t3d::RenderContext * rc,
		real radius,
		real height,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(radius, height, radius));

		cone.drawWireZBufferRW(rc, color, mScaler * mmat);
	}

	void DrawnHelper::drawConeGouraudZBufferRW(
		t3d::RenderContext * rc,
		real radius,
		real height,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(radius, height, radius));

		cone.drawGouraudZBufferRW(rc, mScaler * mmat, mrot);
	}

	void DrawnHelper::drawConeGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		real radius,
		real height,
		const t3d::Mat4<real> & mmat /*= my::Mat4<real>::IDENTITY*/,
		const t3d::Mat4<real> & mrot /*= my::Mat4<real>::IDENTITY*/)
	{
		t3d::Mat4<real> mScaler = t3d::mat3Scale(my::Vec4<real>(radius, height, radius));

		cone.drawGouraudTextureZBufferRW(rc, mScaler * mmat, mrot);
	}
}
