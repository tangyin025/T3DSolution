
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

public:
	MyUIElement(const CRect & rect);

	virtual ~MyUIElement(void);

public:
	virtual void draw(t3d::RenderContext * rc) = 0;
};

typedef boost::shared_ptr<MyUIElement> MyUIElementPtr;

class MyUIBox
	: public MyUIElement
{
protected:
	my::Color m_color;

public:
	void setColor(const my::Color & color)
	{
		m_color = color;
	}

	const my::Color & getColor(void) const
	{
		return m_color;
	}

public:
	MyUIBox(const CRect & rect, const my::Color & color = my::Color(0.3f, 0.3f, 0.3f));

	void draw(t3d::RenderContext * rc);
};

class MyUIText
	: public MyUIElement
{
protected:
	std::basic_string<t3d::charT> m_text;

	my::Color m_color;

public:
	void setText(const std::basic_string<t3d::charT> text)
	{
		m_text = text;
	}

	const std::basic_string<t3d::charT> & getText(void) const
	{
		return m_text;
	}

	void setColor(const my::Color & color)
	{
		m_color = color;
	}

	const my::Color & getColor(void) const
	{
		return m_color;
	}

public:
	MyUIText(const CRect & rect, const std::basic_string<t3d::charT> text = _T(""), const my::Color & color = my::Color::WHITE);

	void draw(t3d::RenderContext * rc);
};

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

public:
	MyUIProgressBar(const CRect & rect, const my::Color & color = my::Color(0.7f, 0.7f, 0.5f));

	~MyUIProgressBar(void);

public:
	void draw(t3d::RenderContext * rc);
};

typedef boost::shared_ptr<MyUIProgressBar> MyUIProgressBarPtr;

class MyUIProgressBarBox
	: public MyUIBox
{
public:
	static const DWORD SIDE_BORDER = 5;

	static const DWORD BAR_HEIGHT = 20;

	static const DWORD TITLE_HEIGHT = 20;

public:
	MyUIText m_title;

	MyUIProgressBar m_progressBar;

public:
	void setPercent(real percent)
	{
		m_progressBar.setPercent(percent);
	}

	real getPercent(void) const
	{
		return m_progressBar.getPercent();
	}

public:
	MyUIProgressBarBox(const CRect & rect);

	~MyUIProgressBarBox(void);

public:
	void setRect(const CRect & rect);

	void draw(t3d::RenderContext * rc);
};

typedef boost::shared_ptr<MyUIProgressBarBox> MyUIProgressBarBoxPtr;
