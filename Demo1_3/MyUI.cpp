
#include "StdAfx.h"
#include "MyUI.h"

MyUIElement::MyUIElement(const CRect & rect)
	: m_rect(rect)
{
}

MyUIElement::~MyUIElement(void)
{
}

MyUIRectangle::MyUIRectangle(const CRect & rect, const my::Color & color)
	: MyUIElement(rect)
	, m_color(color)
{
}

MyUIRectangle::~MyUIRectangle(void)
{
}

void MyUIRectangle::draw(t3d::RenderContext * rc)
{
	LONG y = m_rect.top;
	for(; y < m_rect.bottom; y++)
	{
		rc->drawHorizonLine(m_rect.left, y, m_rect.Width(), m_color);
	}
}

MyUIProgressBar::MyUIProgressBar(const CRect & rect, const my::Color & color)
	: MyUIElement(rect)
	, m_color(color)
	, m_percent(0)
{
}

MyUIProgressBar::~MyUIProgressBar(void)
{
}

void MyUIProgressBar::draw(t3d::RenderContext * rc)
{
	_ASSERT(m_percent >= 0 && m_percent <= 1);

	LONG y = m_rect.top;
	for(; y < m_rect.bottom; y++)
	{
		rc->drawHorizonLine(m_rect.left, y, t3d::real_to_int(m_rect.Width() * m_percent), m_color);
	}
}

MyUIProgressBarBox::MyUIProgressBarBox(const CRect & rect)
	: MyUIElement(rect)
	, m_rectangle(rect, my::Color(0.3f, 0.3f, 0.3f))
	, m_progressBar(CRect(0, 0, 0, 0), my::Color(0.7f, 0.7f, 0.5f))
{
	m_progressBar.m_rect.left = m_rectangle.m_rect.left + SIDE_BORDER;
	m_progressBar.m_rect.right = m_rectangle.m_rect.right - SIDE_BORDER;
	m_progressBar.m_rect.top = m_rectangle.m_rect.top + TITLE_HEIGHT + (m_rectangle.m_rect.Height() - TITLE_HEIGHT - BAR_HEIGHT) / 2;
	m_progressBar.m_rect.bottom = m_progressBar.m_rect.top + BAR_HEIGHT;
}

MyUIProgressBarBox::~MyUIProgressBarBox(void)
{
}

void MyUIProgressBarBox::setPercent(t3d::real percent)
{
	_ASSERT(percent >= 0 && percent <= 1);

	m_progressBar.m_percent = percent;
}

void MyUIProgressBarBox::draw(t3d::RenderContext * rc)
{
	m_rectangle.draw(rc);

	m_progressBar.draw(rc);
}
