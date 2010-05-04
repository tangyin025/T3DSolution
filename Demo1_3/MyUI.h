
#pragma once

class MyUIElement
{
public:
	CRect m_rect;

public:
	void setRect(const CRect & rect)
	{
		m_rect = rect;
	}

	const CRect & getRect(void) const
	{
		return m_rect;
	}

public:
	MyUIElement(const CRect & rect);

	virtual ~MyUIElement(void);

public:
	virtual void draw(t3d::RenderContext * rc) = 0;
};

class MyUIRectangle
	: public MyUIElement
{
public:
	my::Color m_color;

public:
	MyUIRectangle(const CRect & rect, const my::Color & color);

	~MyUIRectangle(void);

public:
	void draw(t3d::RenderContext * rc);
};

class MyUIProgressBar
	: public MyUIElement
{
public:
	my::Color m_color;

	t3d::real m_percent;

public:
	MyUIProgressBar(const CRect & rect, const my::Color & color);

	~MyUIProgressBar(void);

public:
	void draw(t3d::RenderContext * rc);
};

class MyUIProgressBarBox
	: public MyUIElement
{
public:
	static const DWORD SIDE_BORDER = 5;

	static const DWORD BAR_HEIGHT = 20;

	static const DWORD TITLE_HEIGHT = 20;

public:
	MyUIRectangle m_rectangle;

	CRect m_titleRect;

	MyUIProgressBar m_progressBar;

public:
	MyUIProgressBarBox(const CRect & rect);

	~MyUIProgressBarBox(void);

public:
	void setRect(const CRect & rect);

	void setPercent(t3d::real percent);

	void draw(t3d::RenderContext * rc);
};

typedef boost::shared_ptr<MyUIProgressBarBox> MyUIProgressBarBoxPtr;
