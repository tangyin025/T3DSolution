
#pragma once

class MyUIElement
{
protected:
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

protected:
	MyUIElement(void);

public:
	MyUIElement(const CRect & rect);

	virtual ~MyUIElement(void);

public:
	virtual void draw(t3d::RenderContext * rc) = 0;
};

typedef std::tr1::shared_ptr<MyUIElement> MyUIElementPtr;

class MyUIProgressBar
	: public MyUIElement
{
	friend class MyUIProgressBarBox;

public:
	static const DWORD SIDE_BORDER = 3;

	static const DWORD BLOCK_WIDTH = 10;

	static const DWORD BLOCK_INTERVAL = 3;

	my::Color m_color;

	t3d::real m_percent;

public:
	void setColor(const my::Color & color)
	{
		m_color = color;
	}

	const my::Color & getColor(void) const
	{
		return m_color;
	}

	void setPercent(real percent)
	{
		_ASSERT(0 <= percent && percent <= 1);

		m_percent = percent;
	}

	real getPercent(void) const
	{
		return m_percent;
	}

protected:
	MyUIProgressBar(void);

public:
	MyUIProgressBar(const CRect & rect, const my::Color & color);

	~MyUIProgressBar(void);

public:
	void draw(t3d::RenderContext * rc);
};

typedef std::tr1::shared_ptr<MyUIProgressBar> MyUIProgressBarPtr;

class MyUIProgressBarBox
	: public MyUIElement
{
public:
	static const DWORD SIDE_BORDER = 5;

	static const DWORD BAR_HEIGHT = 20;

	static const DWORD TITLE_HEIGHT = 20;

	CRect m_titleRect;

	my::Color m_color;

	MyUIProgressBar m_progressBar;

public:
	void setColor(const my::Color & color)
	{
		m_color = color;
	}

	const my::Color & getColor(void) const
	{
		return m_color;
	}

	void setPercent(real percent)
	{
		m_progressBar.setPercent(percent);
	}

	real getPercent(void) const
	{
		return m_progressBar.getPercent();
	}

public:
	MyUIProgressBarBox(
		const CRect & rect,
		const my::Color & color = my::Color(0.3f, 0.3f, 0.3f),
		const my::Color & barColor = my::Color(0.7f, 0.7f, 0.5f));

	~MyUIProgressBarBox(void);

public:
	void setRect(const CRect & rect);

	void draw(t3d::RenderContext * rc);
};

typedef std::tr1::shared_ptr<MyUIProgressBarBox> MyUIProgressBarBoxPtr;
