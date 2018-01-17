#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  �^�C�g�����
//
class Title : public MyApp::Scene
{
private:

	Array<Rect> m_menuBoxes;

	Array<String> m_menuTexts =
	{
		L"�m�[�}��",
		L"�G���h���X",
		L"VS",
		L"�X�R�A",
		L"�ݒ�",
		L"�I��"
	};

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
		bool handCursor = false;

		for (auto i : step(m_menuBoxes.size()))
		{
			const Quad item = m_menuBoxes[i].shearedX(20);

			handCursor |= item.mouseOver;

			if (item.leftClicked)
			{
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
