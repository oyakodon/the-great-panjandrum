#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  ƒ^ƒCƒgƒ‹‰æ–Ê
//
class Title : public MyApp::Scene
{
private:

	Effect m_effect;

	Stopwatch m_effectBackgroundStopwatch{ true };

	Stopwatch m_effectMenuItemStopwatch{ true };

	Array<Rect> m_menuBoxes;

	Array<String> m_menuTexts =
	{
		GameInfo::MenuGameStart,
		GameInfo::MenuScore,
		GameInfo::MenuExit
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
				if (i == 0)
				{
					changeScene(L"Game");
				}
				else if (i == 1)
				{
					changeScene(L"Score");
				}
				else
				{
					System::Exit();
				}

				break;
			}
		}

		Cursor::SetStyle(handCursor ? CursorStyle::Hand : CursorStyle::Default);
	}

	void draw() const override
	{
		Graphics2D::SetBlendState(BlendState::Additive);

		m_effect.update();

		Graphics2D::SetBlendState(BlendState::Default);

		const double titleHeight = FontAsset(L"Title")(GameInfo::Title).region().h;

		FontAsset(L"Title")(GameInfo::Title).drawAt(Window::Center().x, titleHeight);

		for (auto i : step(m_menuBoxes.size()))
		{
			m_menuBoxes[i].shearedX(20).draw();

			FontAsset(L"Menu")(m_menuTexts[i]).drawAt(m_menuBoxes[i].center, Color(40));
		}

		const Size versionSize = FontAsset(L"Version")(GameInfo::Version).region().size;

		FontAsset(L"Version")(GameInfo::Version).drawAt(Window::Size().moveBy(-versionSize));
	}
};
