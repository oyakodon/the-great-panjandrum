#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  結果画面
//
class Result : public MyApp::Scene
{
private:

	std::array<ScoreData, 10> m_highScores;
	bool m_updated;

	tgpUI::Button m_buttonBack = tgpUI::Button(Rect(150, 600, 240, 60), L"< タイトルに戻る", Palette::White);

	const String ToStringFromClearTime(long long time) const
	{
		const int min = static_cast<int>(time / 60'000); time %= 60'000;
		const int sec = static_cast<int>(time / 1'000); time %= 1'000;
		const int ms = static_cast<int>(time);
		return Format(min, L" 分 ", sec, L" 秒 ", ms);
	}

public:

	~Result()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		String SaveFilePath = L"Save/Story.dat";

		if (m_data->lastMode == PlayMode::Endless)
		{
			SaveFilePath = L"Save/Endless.dat";
		}
		else if (m_data->lastMode == PlayMode::VS)
		{
			SaveFilePath = L"Save/VS.dat";
		}

		if (FileSystem::Exists(SaveFilePath))
		{
			Deserializer<BinaryReader>{SaveFilePath}(m_highScores);
		}
		else
		{
			for (const int i : step(10))
			{
				m_highScores[i] = { m_data->lastMode ==  PlayMode::Endless ? 30'000 : 300'000, DateTime(2011, 5, 31, 12, 0, 0, 0) };
			}

			Serializer<BinaryWriter>{SaveFilePath}(m_highScores);
		}

		m_updated = m_data->lastMode == PlayMode::Endless ? m_highScores.back().clearTime <= m_data->lastClearTime : m_highScores.back().clearTime >= m_data->lastClearTime;
		if (!m_data->lastStageFailed && m_updated)
		{
			m_highScores.back() = { m_data->lastClearTime, DateTime::Now() };

			std::sort(m_highScores.begin(), m_highScores.end(), [&](const ScoreData& a, const ScoreData& b)
			{
				return (m_data->lastMode == PlayMode::Endless ? a.clearTime > b.clearTime : a.clearTime < b.clearTime) ? true : a.clearTime == b.clearTime ? a.date > b.date : false;
			});

			Serializer<BinaryWriter>{SaveFilePath}(m_highScores);

			std::cout << "SaveData updated." << std::endl;
		}

		SoundAsset(L"decision24").play();

	}

	void update() override
	{
		if (m_data->wii[0].isConnected()) m_data->wii[0].update();
		if (m_data->wii[1].isConnected()) m_data->wii[1].update();

		m_buttonBack.update();

		if (m_buttonBack.isClicked() | Input::KeyEscape.clicked |
			(m_data->wii[0].isConnected() && m_data->wii[0].buttonTwo.clicked) |
			(m_data->wii[1].isConnected() && m_data->wii[1].buttonTwo.clicked))
		{
			SoundAsset(L"decision4").play();
			changeScene(L"Title");
		}

		bool mouseOver = m_buttonBack.mouseOver();
		Cursor::SetStyle(mouseOver ? CursorStyle::Hand : CursorStyle::Default);

	}

	void draw() const override
	{
		// 背景
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		FontAsset(L"UI_Large")(L"リザルト").draw({100, 100});

		FontAsset(L"UI_OutLine")(m_data->lastStageFailed ? L"Stage Failed..." : L"Stage Cleared!").drawCenter(Window::BaseCenter().movedBy(-200, -100), m_data->lastStageFailed ? Palette::Red : Palette::Orange);
		FontAsset(L"UI_Large")(L"クリア時間: ", ToStringFromClearTime(m_data->lastClearTime)).drawCenter(Window::BaseCenter().movedBy(-200, 0));

		m_buttonBack.draw();

	}
};

