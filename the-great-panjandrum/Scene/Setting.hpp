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
		const double r = m_size.y / 2;
		m_knob.setPos(m_pos + Vec2(m_value ? m_size.x / 2 - r : -m_size.x / 2 + r, 0));
	}

	bool getValue()
	{
		return m_value;
	}

	bool isChanged()
	{
		return m_changed;
	}

	bool mouseOver()
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

	bool mouseOver()
	{
		return m_mouseOver;
	}

	bool isClicked()
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

class Slider
{
private:
	const Point m_pos;
	const int m_width;

	RoundRect m_gauge;
	Circle m_knob;

	Color m_gaugeColor;
	Color m_knobColor;

	const int m_min;
	const int m_max;

	int m_value;
	bool m_changed = false;
	bool m_mouseOver = false;
	bool m_pressing = false;
	bool m_released = false;

public:

	Slider(const Point& pos, const int w, const int h, const int min, const int max)
		: m_pos(pos), m_width(w), m_min(min), m_max(max)
	{
		m_value = min;

		m_gauge = RoundRect(pos.x - w / 2, pos.y - h / 2, w, h, 15);
		m_knob = Circle(pos.x - w / 2, pos.y, h / 2 + 3);

		m_gaugeColor = Palette::Gray;
		m_knobColor = Palette::White;
	}

	void setColor(const Color& gauge, const Color& knob)
	{
		m_gaugeColor = gauge;
		m_knobColor = knob;
	}

	void setValue(const int value)
	{
		m_value = value;
		m_knob.setPos(m_pos.x - m_width / 2 + m_width * m_value / (m_max - m_min), m_knob.y);
	}

	int getValue()
	{
		return m_value;
	}

	bool isChanged()
	{
		return m_changed;
	}

	bool mouseOver()
	{
		return m_mouseOver;
	}

	bool isReleased()
	{
		return m_released;
	}

	void update()
	{
		m_changed = false;
		m_released = false;
		m_mouseOver = m_knob.mouseOver;

		if (m_knob.leftPressed | m_pressing)
		{
			m_pressing = true;

			const int oldval = m_value;
			double x = Mouse::PosF().x;

			if (x < m_pos.x - m_width / 2)
			{
				x = m_pos.x - m_width / 2;
			}

			if (x > m_pos.x + m_width / 2)
			{
				x = m_pos.x + m_width / 2;
			}

			m_knob.setPos(x, m_knob.y);
			m_value = static_cast<int>((m_knob.x - m_pos.x + m_width / 2) / m_width * (m_max - m_min));

			if (oldval != m_value)
			{
				m_changed = true;
			}
		}

		if (m_pressing & Input::MouseL.released)
		{
			m_released = true;
			m_pressing = false;
		}

	}

	void draw() const
	{
		m_gauge.draw(m_gaugeColor);
		m_knob.draw(m_knobColor);

		const RectF region = FontAsset(L"UI_Small")(m_value).region();
		FontAsset(L"UI_Small")(m_value).drawCenter(m_pos.x - m_width / 2 - region.w / 2 - 5 - m_knob.r, m_pos.y);

	}

};

class Setting : public MyApp::Scene
{
private:

	ToggleSwitch toggleDebug = ToggleSwitch(Window::BaseCenter().moveBy(150, 140), 40, false);
	Button buttonBack = Button(Rect(150, 600, 240, 60), L"< �^�C�g���ɖ߂�", Palette::White);
	Slider sliderVol = Slider(Window::BaseCenter().moveBy(150, -150), 300, 15, 0, 100);

public:

	~Setting()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		toggleDebug.setText(L"����", L"�L��");
		toggleDebug.setValue(m_data->debugMode);
		sliderVol.setValue(static_cast<int>(MasterVoice::GetVolume() * 100));
	}

	void update() override
	{
		toggleDebug.update();
		buttonBack.update();
		sliderVol.update();

		if (toggleDebug.isChanged())
		{
			m_data->debugMode = toggleDebug.getValue();
		}

		if (sliderVol.isChanged())
		{
			MasterVoice::SetVolume(sliderVol.getValue() / 100.0);
		}

		if (sliderVol.isReleased())
		{
			SoundAsset(L"one01").playMulti();
		}

		if (buttonBack.isClicked() | Input::KeyEscape.clicked)
		{
			changeScene(L"Title");
		}

		if (toggleDebug.mouseOver() | buttonBack.mouseOver() | sliderVol.mouseOver())
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
		FontAsset(L"UI_Large")(L"�Q�[���ݒ�").drawCenter(Window::BaseCenter().x, 75);

		FontAsset(L"Menu")(L"����").drawCenter(Window::BaseCenter() + Vec2(-150, -150));
		sliderVol.draw();

		FontAsset(L"Menu")(L"�f�o�b�O���[�h").drawCenter(Window::BaseCenter() + Vec2(-150, 140));
		toggleDebug.draw();

		buttonBack.draw();

	}

};
