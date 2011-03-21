
#include "StdAfx.h"
#include "MyUI.h"

MyUIElement::MyUIElement(const CRect & rect)
	: m_rect(rect)
{
}

MyUIElement::~MyUIElement(void)
{
}

MyUIBox::MyUIBox(const CRect & rect, const my::Color & color /*= my::Color(0.3f, 0.3f, 0.3f)*/)
	: MyUIElement(rect)
	, m_color(color)
{
}

void MyUIBox::draw(t3d::RenderContext * rc)
{
	rc->fillSurface(getRect(), getColor());
}

MyUIText::MyUIText(const CRect & rect, const std::basic_string<t3d::charT> & text /*= _T("")*/, const my::Color & color /*= my::Color::WHITE*/)
	: MyUIElement(rect)
	, m_text(text)
	, m_color(color)
{
}

void MyUIText::draw(t3d::RenderContext * rc)
{
	my::Vec4<int> vc = t3d::real_to_int(t3d::rgbaSaturate(m_color * 255, real(255)));
	COLORREF color = RGB(vc.x, vc.y, vc.z);

	HDC hdc = my::Game::getSingleton().m_backSurface->getDC();
	COLORREF oldColor = ::SetTextColor(hdc, color);
	int oldMode = ::SetBkMode(hdc, TRANSPARENT);
	::DrawText(hdc, m_text.c_str(), m_text.length(), &m_rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	::SetTextColor(hdc, oldColor);
	::SetBkMode(hdc, oldMode);
	my::Game::getSingleton().m_backSurface->releaseDC(hdc);

	UNREFERENCED_PARAMETER(rc);
}

MyUIProgressBar::MyUIProgressBar(const CRect & rect, const my::Color & color /*= my::Color(0.7f, 0.7f, 0.5f))*/)
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

	LONG x = m_rect.left + SIDE_BORDER;
	LONG xEnd = x + t3d::real_to_int(m_percent * (m_rect.Width() - SIDE_BORDER * 2) + 0.5f);
	for(; x < xEnd; x += BLOCK_WIDTH + BLOCK_INTERVAL)
	{
		rc->fillSurface(
			CRect(CPoint(x, m_rect.top + SIDE_BORDER), CSize(std::min<LONG>(m_rect.right - SIDE_BORDER - x, BLOCK_WIDTH), m_rect.Height() - SIDE_BORDER * 2)), getColor());
	}
}

MyUIProgressBarBox::MyUIProgressBarBox(const CRect & rect)
	: MyUIBox(rect)
	, m_title(CRect())
	, m_progressBar(CRect())
{
	setRect(rect);
}

MyUIProgressBarBox::~MyUIProgressBarBox(void)
{
}

void MyUIProgressBarBox::setRect(const CRect & rect)
{
	MyUIBox::setRect(rect);

	m_title.setRect(CRect(
		m_rect.left + SIDE_BORDER,
		m_rect.top + SIDE_BORDER,
		m_rect.right - SIDE_BORDER,
		m_rect.top + SIDE_BORDER + TITLE_HEIGHT));

	const CRect & titleRect = m_title.getRect();

	CRect progressBarRect;
	progressBarRect.left = m_rect.left + SIDE_BORDER;
	progressBarRect.right = m_rect.right - SIDE_BORDER;
	progressBarRect.top = titleRect.bottom + (m_rect.bottom - titleRect.bottom - BAR_HEIGHT) / 2;
	progressBarRect.bottom = progressBarRect.top + BAR_HEIGHT;

	m_progressBar.setRect(progressBarRect);
}

void MyUIProgressBarBox::draw(t3d::RenderContext * rc)
{
	MyUIBox::draw(rc);

	m_title.draw(rc);

	m_progressBar.draw(rc);
}
