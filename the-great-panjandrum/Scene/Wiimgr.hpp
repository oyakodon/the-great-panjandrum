#pragma once

#include "GameData.hpp"
#include "UI.hpp"

#include "../Wiimote/wm4s3d.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Wiimgr : public MyApp::Scene
{
private:
	
	tgpUI::Button buttonCancel = tgpUI::Button(Rect(150, 600, 350, 60), L"Wiiリモコンを使用しない", Palette::White);

	tgpUI::Dialog dialog = tgpUI::Dialog(Window::BaseCenter(), {700, 250}, L"Wiiリモコンを使用するには、Bluetoothをオンにしてください。");

public:

	~Wiimgr()
	{
		Wiimote::stopScan();
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		if (Wiimote::isBluetoothActive())
		{
			Wiimote::startScan();
		}
		else
		{
			dialog.setTitle(L"エラー");
			dialog.show();
		}

	}

	void update() override
	{
		dialog.update();

		if (!dialog.isShown())
		{

			buttonCancel.update();

			if (buttonCancel.isClicked() | Input::KeyEscape.clicked)
			{
				changeScene(L"Title");
			}

		}

		if (dialog.isClosed())
		{
			changeScene(L"Title");
		}

		Cursor::SetStyle(dialog.mouseOver() ? CursorStyle::Hand : CursorStyle::Default);

	}

	void draw() const override
	{
		// FontAsset(L"UI")(L"[ Wiimote Manager ]").drawCenter(Window::BaseCenter());

		dialog.draw();

		// 右下のくるくる
		Circle(Window::BaseSize() - Vec2(75, 75), 25).drawArc(Time::GetMillisec() * 0.0005, 4.5, 2.0, 2.0);

		buttonCancel.draw();

	}
};

