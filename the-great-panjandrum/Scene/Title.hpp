#pragma once

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
		L"ノーマルモード",
		L"エンドレスモード",
		L"VSモード",
		L"スコア",
		L"設定",
		L"終了"
	};

public:

	~Title()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		m_menuBoxes.resize(m_menuTexts.size());

		int32 boxWidth = 0;

		for (const auto& text : m_menuTexts)
		{
			boxWidth = Max(boxWidth, FontAsset(L"Menu")(text).region().w);
		}

		for (auto i : step(m_menuBoxes.size()))
		{
			m_menuBoxes[i].set(240, 280 + i * 80, boxWidth + 80, 60);
		}
	}

	void update() override
	{
		bool handCursor = false;

		for (auto i : step(m_menuBoxes.size()))
		{
			const Quad item = m_menuBoxes[i].shearedX(20);

			handCursor |= item.mouseOver;

			if (item.leftClicked)
			{
				switch (i)
				{
					case 0: changeScene(L"StageNormal"); break;
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
		const double titleHeight = FontAsset(L"Title")(GameInfo::Title).region().h;

		FontAsset(L"Title")(GameInfo::Title).drawAt(Window::BaseCenter().x, titleHeight);

		for (auto i : step(m_menuBoxes.size()))
		{
			m_menuBoxes[i].shearedX(20).draw();

			FontAsset(L"Menu")(m_menuTexts[i]).drawAt(m_menuBoxes[i].center, Color(40));
		}

		const Size versionSize = FontAsset(L"Version")(GameInfo::Version).region().size;

		FontAsset(L"Version")(GameInfo::Version).drawAt(Window::BaseSize().moveBy(-versionSize));
	}
};
