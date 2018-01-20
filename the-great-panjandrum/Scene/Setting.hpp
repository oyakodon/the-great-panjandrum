#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class ToggleSwitch
{
private:

	const Point m_pos;
	RoundRect m_background;
	Circle m_knob;
	Color m_bg_color;
	Color m_bg_color_on;
	Color m_knob_color;

	Size m_size;

	Optional<String> m_leftText;
	Optional<String> m_rightText;

	bool m_value = false;
	bool m_changed = false;
	bool m_mouseOver = false;

public:

	ToggleSwitch(const Point& p, const int h, const bool value)
		: m_pos(p)
	{
		const double r = h / 2;
		m_size = Size(h * 1.75, h);
		m_knob = Circle(p + Vec2(-m_size.x / 2 + r, 0), r - 2);
		m_background = RoundRect(p + Vec2(-m_size.x / 2, -r), m_size, r);
		setColor(Palette::Gray, Palette::Lime, Palette::White);
		m_value = value;
	}

	void setText(const String& left, const String& right)
	{
		m_leftText = left;
		m_rightText = right;
	}

	void setColor(const Color& bg_col, const Color& bg_col_on, const Color& knob_col)
	{
		m_bg_color = bg_col;
		m_bg_color_on = bg_col_on;
		m_knob_color = knob_col;
	}

	void setValue(bool value)
	{
		m_value = value;
	}

	bool getValue() const
	{
		return m_value;
	}

	bool isChanged() const
	{
		return m_changed;
	}

	bool mouseOver() const
	{
		return m_mouseOver;
	}

	void update()
	{
		m_changed = false;

		m_mouseOver = m_background.mouseOver | m_knob.mouseOver;

		if (m_background.leftClicked | m_knob.leftClicked)
		{
			m_value = !m_value;
			m_changed = true;
		}

		const double r = m_size.y / 2;
		m_knob.setPos(m_pos + Vec2(m_value ? m_size.x / 2 - r : -m_size.x / 2 + r, 0));
	}

	void draw() const
	{
		m_background.draw(m_value ? m_bg_color_on : m_bg_color);
		m_knob.draw(m_knob_color);

		if (m_leftText.has_value() && !m_leftText.value().isEmpty)
		{
			const Rect region = FontAsset(L"UI")(m_leftText.value()).region();
			FontAsset(L"UI")(m_leftText.value()).drawCenter(m_pos.x - (m_size.x / 2) - (region.w / 2) - 10, m_pos.y);
		}

		if (m_rightText.has_value() && !m_rightText.value().isEmpty)
		{
			const Rect region = FontAsset(L"UI")(m_rightText.value()).region();
			FontAsset(L"UI")(m_rightText.value()).drawCenter(m_pos.x + (m_size.x / 2) + (region.w / 2) + 10, m_pos.y);
		}
	}

};

class Button
{
private:

	RoundRect m_rect;

	Color m_bgColor;
	Color m_textColor = Palette::Black;

	String m_text;

	bool m_clicked = false;
	bool m_mouseOver = false;

public:

	Button(const Rect& rect, const String& text, const Color& background)
	{
		m_rect = RoundRect(rect, 5);
		m_text = text;
		m_bgColor = background;
	}

	void setText(const String& text)
	{
		m_text = text;
	}

	void setColor(const Color& bg_col, const Color& text_col)
	{
		m_bgColor = bg_col;
		m_textColor = text_col;
	}

	bool mouseOver() const
	{
		return m_mouseOver;
	}

	bool isClicked() const
	{
		return m_clicked;
	}

	void update()
	{
		m_clicked = false;

		m_mouseOver = m_rect.mouseOver;

		if (m_rect.leftClicked)
		{
			m_clicked = true;
		}

	}

	void draw() const
	{
		m_rect.draw(m_bgColor).drawFrame(1.0, 0.0, Palette::Black);
		FontAsset(L"UI")(m_text).drawCenter(m_rect.center, m_textColor);
	}

};

class Setting : public MyApp::Scene
{
private:

	ToggleSwitch toggleDebug = ToggleSwitch(Window::BaseCenter().moveBy(150, 170), 40, false);
	Button buttonBack = Button(Rect(150, 600, 240, 60), L"< タイトルに戻る", Palette::White);

public:

	~Setting()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		toggleDebug.setText(L"無効", L"有効");
		toggleDebug.setValue(m_data->debugMode);

	}

	void update() override
	{
		toggleDebug.update();
		buttonBack.update();

		if (toggleDebug.isChanged())
		{
			m_data->debugMode = toggleDebug.getValue();
		}

		if (buttonBack.isClicked() | Input::KeyEscape.clicked)
		{
			changeScene(L"Title");
		}

		if (toggleDebug.mouseOver() | buttonBack.mouseOver())
		{
			Cursor::SetStyle(CursorStyle::Hand);
		}
		else
		{
			Cursor::SetStyle(CursorStyle::Default);
		}

	}

	void draw() const override
	{
		FontAsset(L"UI_Large")(L"ゲーム設定").drawCenter(Window::BaseCenter().x, 75);

		FontAsset(L"Menu")(L"デバッグモード").drawCenter(Window::BaseCenter() + Vec2(-150, 170));
		toggleDebug.draw();

		buttonBack.draw();

	}

};
