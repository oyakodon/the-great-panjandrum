#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  ハイスコア一覧
//
class Score : public MyApp::Scene
{
private:

	std::array<ScoreData, 10> m_highScores;
	String m_SaveFilePath = L"Save/Story.dat";
	String m_modeString = L"ノーマル";
	int m_selected = 0;

	tgpUI::Button m_buttonBack = tgpUI::Button(Rect(50, 30, 120, 50), L"< 戻る", Palette::White);
	tgpUI::Button m_buttonPrev = tgpUI::Button(Rect(400, 30, 50, 50), L"<", Palette::White);
	tgpUI::Button m_buttonNext = tgpUI::Button(Rect(850, 30, 50, 50), L">", Palette::White);

	void changeMode(const PlayMode& mode)
	{
		switch (mode)
		{
			case PlayMode::Story:	m_SaveFilePath = L"Save/Story.dat";		m_modeString = L"ノーマル"; break;
			case PlayMode::VS:		m_SaveFilePath = L"Save/VS.dat";		m_modeString = L"VS"; break;
			case PlayMode::Endless: m_SaveFilePath = L"Save/Endless.dat";	m_modeString = L"エンドレス"; break;
			default: break;
		}

		if (FileSystem::Exists(m_SaveFilePath))
		{
			Deserializer<BinaryReader>{m_SaveFilePath}(m_highScores);
		}
		else
		{
			for (const int i : step(10))
			{
				m_highScores[i] = { mode == PlayMode::Endless ? 30'000 : 300'000, DateTime(2011, 5, 31, 12, 0, 0, 0) };
			}

			Serializer<BinaryWriter>{m_SaveFilePath}(m_highScores);
		}

	}

	const String ToStringFromClearTime(long long time) const
	{
		const int min = static_cast<int>(time / 60'000); time %= 60'000;
		const int sec = static_cast<int>(time / 1'000); time %= 1'000;
		const int ms = static_cast<int>(time);
		return Format(min, L" 分 ", sec, L" 秒 ", ms);
	}

public:

	void init() override
	{
		changeMode(PlayMode::Story);
	}

	void update() override
	{
		if (m_data->wii[0].isConnected()) m_data->wii[0].update();
		if (m_data->wii[1].isConnected()) m_data->wii[1].update();

		m_buttonBack.update();
		m_buttonNext.update();
		m_buttonPrev.update();

		if (m_buttonBack.isClicked() | Input::KeyEscape.clicked |
			(m_data->wii[0].isConnected() && m_data->wii[0].buttonTwo.clicked) |
			(m_data->wii[1].isConnected() && m_data->wii[1].buttonTwo.clicked))
		{
			SoundAsset(L"decision4").play();
			changeScene(L"Title");
		}

		if (m_buttonNext.isClicked() |
			(m_data->wii[0].isConnected() && m_data->wii[0].buttonDown.clicked) |
			(m_data->wii[1].isConnected() && m_data->wii[1].buttonDown.clicked))
		{
			SoundAsset(L"cancel1").playMulti();
			m_selected = Min(2, m_selected + 1);
			changeMode(static_cast<PlayMode>(m_selected));
		}

		if (m_buttonPrev.isClicked() |
			(m_data->wii[0].isConnected() && m_data->wii[0].buttonUp.clicked) |
			(m_data->wii[1].isConnected() && m_data->wii[1].buttonUp.clicked))
		{
			SoundAsset(L"cancel1").playMulti();
			m_selected = Max(0, m_selected - 1);
			changeMode(static_cast<PlayMode>(m_selected));
		}

		bool mouseOver = m_buttonBack.mouseOver() | m_buttonNext.mouseOver() | m_buttonPrev.mouseOver();
		Cursor::SetStyle(mouseOver ? CursorStyle::Hand : CursorStyle::Default);

	}

	void draw() const override
	{
		// 背景
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		FontAsset(L"UI_Large")(L"スコア (", m_modeString, L")").drawCenter(Window::BaseCenter().x, 50);

		const int32 h = FontAsset(L"UI_Large").height;

		for (auto i : step(m_highScores.size()))
		{
			const Rect rect = Rect(500, 100).setCenter(370 + (i % 2) * 540, 180 + (i / 2) * 110);

			rect.draw(ColorF(1.0, 0.2));

			FontAsset(L"UI_Large")((i + 1), L":").draw(rect.pos + Point(30, (rect.h - h) / 2 - 20), Palette::Darkorange);

			FontAsset(L"UI_Large")(ToStringFromClearTime(m_highScores[i].clearTime)).draw(rect.pos + Point(120, (rect.h - h) / 2 - 15), Palette::Gray);

			FontAsset(L"UI_Large")(ToStringFromClearTime(m_highScores[i].clearTime)).draw(rect.pos + Point(115, (rect.h - h) / 2 - 20));

			const Size dateSize = FontAsset(L"UI_Small")(m_highScores[i].date).region().size;

			FontAsset(L"UI_Small")(m_highScores[i].date).draw(rect.br.x - dateSize.x - 40, rect.center.y - dateSize.y / 2 + 20);
		}

		m_buttonBack.draw();
		m_buttonNext.draw();
		m_buttonPrev.draw();

	}
};

