#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  ÉQÅ[ÉÄ
//
class Game : public MyApp::Scene
{
private:

	static constexpr int32 gameTimeMillisec = 20 * 1000;

	Stopwatch m_countDownTimer;

	Stopwatch m_gameTimer;

	int32 m_score = 0;

	bool onCountDown() const
	{
		return m_countDownTimer.isActive() && m_countDownTimer.ms() < 4000;
	}

	bool onGame() const
	{
		return m_gameTimer.isActive();
	}

public:

	~Game()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		
	}

	void update() override
	{
		if (!onGame() && !m_countDownTimer.isActive())
		{
			m_countDownTimer.start();
		}

		if (!onGame() && m_countDownTimer.ms() >= 3000)
		{
			m_gameTimer.start();
		}

		if (!onGame())
		{
			return;
		}

		if (m_gameTimer.ms() >= gameTimeMillisec)
		{
			changeScene(L"Result", 2000);
		}
		
	}

	void draw() const override
	{
		if (onCountDown())
		{
			const int32 timeMillisec = Max((3999 - m_countDownTimer.ms()), 0);
			const int32 countDown = timeMillisec / 1000;
			const double e = EaseIn<Easing::Expo>((timeMillisec % 1000) / 1000.0);

			if (countDown > 0)
			{
				Transformer2D t(Mat3x2::Scale(1.0 + e * 2, Window::Center()));
				FontAsset(L"CountDown")(countDown).drawAt(Window::Center());
			}
			else
			{
				Transformer2D t(Mat3x2::Scale(1.0 + (1.0 - e) * 2, Window::Center()));
				FontAsset(L"CountDown")(L"START").drawAt(Window::Center(), AlphaF(e));
			}
		}

		if (!onGame())
		{
			return;
		}

		const int32 timeLeftMillisec = Max(gameTimeMillisec - m_gameTimer.ms(), 0);

		FontAsset(L"GameTime")(L"TIME: {:0>2}'{:0>2}"_fmt, timeLeftMillisec / 1000, timeLeftMillisec % 1000 / 10).draw(60, 60);
	}
};
