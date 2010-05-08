
#include "StdAfx.h"
#include "MyUI.h"

MyUIElement::MyUIElement(void)
{
}

MyUIElement::MyUIElement(const CRect & rect)
	: m_rect(rect)
{
}

MyUIElement::~MyUIElement(void)
{
}

MyUIProgressBar::MyUIProgressBar(void)
{
}

MyUIProgressBar::MyUIProgressBar(const CRect & rect, const my::Color & color)
	: MyUIElement()
	, m_color(color)
	, m_percent(0)
{
	setRect(rect);
}

MyUIProgressBar::~MyUIProgressBar(void)
{
}

void MyUIProgressBar::draw(t3d::RenderContext * rc)
{
	_ASSERT(m_percent >= 0 && m_percent <= 1);

	LONG x = m_rect.left + SIDE_BORDER;
	LONG xEnd = x + t3d::real_to_int(m_percent * (m_rect.Width() - SIDE_BORDER * 2) + 0.5f);
	for(; x < xEnd; x += BLOCK_WIDTH + BLOCK_INTERVAL)
	{
		rc->fillSurface(
			CRect(CPoint(x, m_rect.top + SIDE_BORDER), CSize(std::min<LONG>(m_rect.right - SIDE_BORDER - x, BLOCK_WIDTH), m_rect.Height() - SIDE_BORDER * 2)), getColor());
	}
}

MyUIProgressBarBox::MyUIProgressBarBox(
		const CRect & rect,
		const my::Color & color /*= my::Color(0.3f, 0.3f, 0.3f)*/,
		const my::Color & barColor /*= my::Color(0.7f, 0.7f, 0.5f)*/)
	: MyUIElement(rect)
	, m_titleRect(CRect())
	, m_color(color)
	, m_progressBar()
{
	setRect(rect);
	m_progressBar.setColor(barColor);
	m_progressBar.setPercent(0);
}

MyUIProgressBarBox::~MyUIProgressBarBox(void)
{
}

void MyUIProgressBarBox::setRect(const CRect & rect)
{
	MyUIElement::setRect(rect);

	m_titleRect.left = m_rect.left + SIDE_BORDER;
	m_titleRect.right = m_rect.right - SIDE_BORDER;
	m_titleRect.top = m_rect.top + SIDE_BORDER;
	m_titleRect.bottom = m_titleRect.top + TITLE_HEIGHT;

	CRect progressBarRect;
	progressBarRect.left = m_rect.left + SIDE_BORDER;
	progressBarRect.right = m_rect.right - SIDE_BORDER;
	progressBarRect.top = m_titleRect.bottom + (m_rect.bottom - m_titleRect.bottom - BAR_HEIGHT) / 2;
	progressBarRect.bottom = progressBarRect.top + BAR_HEIGHT;

	m_progressBar.setRect(progressBarRect);
}

void MyUIProgressBarBox::draw(t3d::RenderContext * rc)
{
	rc->fillSurface(getRect(), getColor());

	m_progressBar.draw(rc);
}
