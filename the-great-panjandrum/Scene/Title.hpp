﻿#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  タイトル画面
//
class Title : public MyApp::Scene
{
private:

	Array<Rect> m_menuBoxes;

	Array<String> m_menuTexts =
	{
		L"ノーマル",
		L"エンドレス",
		L"VS",
		L"スコア",
		L"設定",
		L"終了"
	};

	int m_cursor = 0;

public:

	~Title()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		m_menuBoxes.resize(m_menuTexts.size());
		
		int box_width = 250;
		for (auto i : step(3))
		{
			m_menuBoxes[i].set(Window::BaseCenter().x + (i - 1) * (box_width + 40) - box_width / 2, 280, box_width, 120);
		}

		box_width = 280;
		for (auto i : step(3))
		{
			m_menuBoxes[3 + i].set(Window::BaseCenter().x - box_width / 2, 450 + i * 80, box_width, 60);
		}
	}

	void update() override
	{
		if (m_data->wii[0].isConnected()) m_data->wii[0].update();
		if (m_data->wii[1].isConnected()) m_data->wii[1].update();

		bool handCursor = false;
		
		if ((Input::KeyDown | Input::KeyRight).clicked |
			(m_data->wii[0].isConnected() && (m_data->wii[0].buttonLeft.clicked | m_data->wii[0].buttonDown.clicked)) |
			(m_data->wii[1].isConnected() && (m_data->wii[1].buttonLeft.clicked | m_data->wii[1].buttonDown.clicked)))
		{
			SoundAsset(L"cancel1").playMulti();
			m_cursor = m_cursor < 5 ? m_cursor + 1 : 0;
		}

		if ((Input::KeyUp | Input::KeyLeft).clicked |
			(m_data->wii[0].isConnected() && (m_data->wii[0].buttonRight.clicked | m_data->wii[0].buttonUp.clicked)) |
			(m_data->wii[1].isConnected() && (m_data->wii[1].buttonRight.clicked | m_data->wii[1].buttonUp.clicked)))
		{
			SoundAsset(L"cancel1").playMulti();
			m_cursor = m_cursor > 0 ? m_cursor - 1 : 5;
		}

		if (Input::KeyEnter.clicked | 
				(m_data->wii[0].isConnected() && m_data->wii[0].buttonTwo.clicked) |
				(m_data->wii[1].isConnected() && m_data->wii[1].buttonTwo.clicked))
		{
			SoundAsset(L"decision4").play();

			switch (m_cursor)
			{
				case 0: changeScene(L"StageStory"); break;
				case 1: changeScene(L"StageEndless"); break;
				case 2: changeScene(L"StageVS"); break;
				case 3: changeScene(L"Score"); break;
				case 4: changeScene(L"Setting"); break;
				default: System::Exit(); break;
			}
		}

		for (auto i : step(m_menuBoxes.size()))
		{
			const Quad item = m_menuBoxes[i].shearedX(20);

			handCursor |= item.mouseOver;

			if (item.leftClicked)
			{
				SoundAsset(L"decision4").play();

				switch (i)
				{
					case 0: changeScene(L"StageStory"); break;
					case 1: changeScene(L"StageEndless"); break;
					case 2: changeScene(L"StageVS"); break;
					case 3: changeScene(L"Score"); break;
					case 4: changeScene(L"Setting"); break;
					default: System::Exit(); break;
				}

				break;
			}
		}

		Cursor::SetStyle(handCursor ? CursorStyle::Hand : CursorStyle::Default);
	}

	void draw() const override
	{
		// 背景
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		const double titleHeight = FontAsset(L"Title")(GameInfo::Title).region().h;

		FontAsset(L"Title")(GameInfo::Title).drawAt(Window::BaseCenter().x, titleHeight);

		for (auto i : step(m_menuBoxes.size()))
		{
			m_menuBoxes[i].shearedX(20).draw();

			if (m_cursor == i)
			{
				m_menuBoxes[i].shearedX(20).drawFrame(3.0, Palette::Red);
			}

			FontAsset(L"Menu")(m_menuTexts[i]).drawAt(m_menuBoxes[i].center, Color(40));
		}

		const Size versionSize = FontAsset(L"Version")(GameInfo::Version).region().size;

		FontAsset(L"Version")(GameInfo::Version).drawAt(Window::BaseSize().moveBy(-versionSize));
	}
};
