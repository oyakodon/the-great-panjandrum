#pragma once

#include <Siv3D.hpp>

namespace tgpUI
{

	/// <summary>
	/// トグルスイッチ(ON/OFF)
	/// </summary>
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

	/// <summary>
	/// ボタン
	/// </summary>
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

	/// <summary>
	///  ダイアログ
	/// </summary>
	class Dialog
	{
	private:

		const Point m_centerPos;
		const Size m_size;
		const String m_text;
		Optional<String> m_title;

		Button m_closeButton;

		bool m_shown;
		bool m_closed;

	public:

		Dialog(const Point& pos, const Size& size, const String& text)
			: m_centerPos(pos),
			m_size(size),
			m_text(text),
			m_shown(false),
			m_closed(false),
			m_closeButton(Rect(pos + size / 2 - Point(120, 70), { 100, 50 }), L"閉じる", Palette::White)
		{

		}

		void show()
		{
			m_shown = true;
		}

		void setTitle(const String& text)
		{
			m_title = text;
		}

		bool isShown()
		{
			return m_shown;
		}

		bool isClosed()
		{
			return m_closed;
		}

		bool mouseOver()
		{
			return m_shown && m_closeButton.mouseOver();
		}

		void update()
		{
			m_closed = false;

			if (m_shown)
			{
				m_closeButton.update();

				if (m_closeButton.isClicked())
				{
					m_shown = false;
					m_closed = true;
				}

			}

		}

		void draw() const
		{
			if (m_shown)
			{
				RoundRect(m_centerPos - m_size / 2, m_size, 10).draw(Palette::White).drawFrame(0.0, 2.0, Palette::Gray);

				if (m_title.has_value())
				{
					const RectF region = FontAsset(L"UI_Large")(m_title.value()).region();
					FontAsset(L"UI_Large")(m_title.value()).drawCenter(m_centerPos + Vec2(0, -m_size.y / 2 + region.h / 2 + 10), Palette::Black);
				}

				FontAsset(L"UI")(m_text).drawCenter(m_centerPos, Palette::Black);

				m_closeButton.draw();
			}
		}


	};

	/// <summary>
	/// メーター
	/// </summary>
	class Meter
	{
	private:

		const Vec2 m_pos;
		const int m_width;
		const int m_height;

		double m_value;

	public:

		Meter(const Vec2& pos, const int w, const int h)
			: m_pos(pos),
			m_width(w),
			m_height(h)
		{
			m_value = 0;
		}

		/// <summary>
		/// メーターの値を設定します。
		/// </summary>
		/// <param name="value">値(0.0-1.0)</param>
		void setValue(const double value)
		{
			m_value = Max(Min(value, 1.0), 0.0);
		}

		/// <summary>
		/// メーターの値を返します。
		/// </summary>
		/// <returns>メーターの値</returns>
		double getValue()
		{
			return m_value;
		}

		void update()
		{

		}

		void draw() const
		{
			const double R = m_height / 2;

			// 背景
			RoundRect(m_pos.x - m_width / 2, m_pos.y - R, m_width, m_height, R).draw(Palette::Gray);

			// メーター
			if (0.0 < m_value)
			{
				// 左端
				Circle({ m_pos.x - m_width / 2 + R, m_pos.y }, R).draw(Palette::Lime);
				// 半円にする
				RectF(m_pos.x - m_width / 2 + R, m_pos.y - R, R, m_height).draw(Palette::Gray);
				// メーター埋める
				RectF(m_pos.x - m_width / 2 + R / 2, m_pos.y - R, Min(m_width * m_value, m_width - R), m_height).draw(Palette::Lime);
				// 右端
				if (m_value * m_width >= m_width - R)
				{
					Circle({ m_pos.x + m_width / 2 - R, m_pos.y }, R).draw(Palette::Lime);
				}
			}

			// 枠
			RoundRect(m_pos.x - m_width / 2, m_pos.y - R, m_width, m_height, R).drawFrame(2.0, 1.0, Palette::Black);
		}

	};

	/// <summary>
	/// スライダー
	/// </summary>
	class Slider
	{
	private:

		const Point m_pos;
		const int m_width;

		Circle m_knob;

		const int m_min;
		const int m_max;

		double m_value;
		bool m_changed = false;
		bool m_mouseOver = false;
		bool m_pressing = false;
		bool m_released = false;

		std::shared_ptr<Meter> p_meter;

	public:

		Slider(const Point& pos, const int w, const int h, const int min, const int max)
			: m_pos(pos), m_width(w), m_min(min), m_max(max)
		{
			m_value = 0.0;

			m_knob = Circle(pos.x - w / 2, pos.y, h / 2 + 3);
			p_meter = std::shared_ptr<Meter>(new Meter({ pos.x , pos.y }, w, h));
		}

		void setValue(const int value)
		{
			m_value = (double)value / (m_max - m_min);
			p_meter.get()->setValue(m_value);
			m_knob.setPos(m_pos.x - m_width / 2 + m_width * m_value, m_knob.y);
		}

		void setValue(const double value)
		{
			m_value = value;
			p_meter.get()->setValue(m_value);
			m_knob.setPos(m_pos.x - m_width / 2 + m_width * m_value, m_knob.y);
		}

		int getValue()
		{
			return static_cast<int>(m_value * (m_max - m_min));
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

				const double oldval = m_value;
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
				m_value = (m_knob.x - m_pos.x + m_width / 2) / m_width;
				p_meter.get()->setValue(m_value);

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
			p_meter.get()->draw();
			m_knob.draw(Palette::White);

			const RectF region = FontAsset(L"UI_Small")(static_cast<int>(m_value * (m_max - m_min))).region();
			FontAsset(L"UI_Small")(static_cast<int>(m_value * (m_max - m_min))).drawCenter(m_pos.x - m_width / 2 - region.w / 2 - 5 - m_knob.r, m_pos.y);

		}

	};

}