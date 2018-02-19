#pragma once

#include "GameData.hpp"
#include "UI.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class UITest : public MyApp::Scene
{
private:

	tgpUI::TextBox m_tb = tgpUI::TextBox(Window::BaseCenter(), 100, 30);

public:

	~UITest()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		
	}

	void update() override
	{
		m_tb.update();

		bool mouseOver = m_tb.mouseOver();
		Cursor::SetStyle(mouseOver ? CursorStyle::Hand : CursorStyle::Default);

	}

	void draw() const override
	{
		FontAsset(L"UI_Large")(L"UI Test").drawCenter(Window::BaseCenter().x, 75);

		m_tb.draw();

	}

};
