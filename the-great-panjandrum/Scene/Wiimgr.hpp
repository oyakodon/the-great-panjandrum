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

		if (dialog.isShown())
		{
			if (Input::KeyEnter.clicked)
			{
				changeScene(L"Title");
			}
		}
		else
		{

			buttonCancel.update();

			if (buttonCancel.isClicked())
			{
				changeScene(L"Title");
			}

			for (int i = 0; i < 2; i++)
			{
				if (m_data->wii[i].hasConnected())
				{
					std::thread([&]
					{
						int num = i;
						System::Sleep(100);
						m_data->wii[num].setLED(num, true);
						System::Sleep(500);
						m_data->wii[num].controller.playSound("wii_sound.raw", 65);
					}).detach();
				}

				if (m_data->wii[i].isConnected())
				{
					m_data->wii[i].update();

					if (m_data->wii[i].buttonA.pressed & m_data->wii[i].buttonB.pressed)
					{
						changeScene(L"Title");
					}
				}

			}

		}

		if (dialog.isClosed() | Input::KeyEscape.clicked)
		{
			changeScene(L"Title");
		}

		Cursor::SetStyle(dialog.mouseOver() | buttonCancel.mouseOver() ? CursorStyle::Hand : CursorStyle::Default);

	}
	
	void draw() const override
	{
		// Background
		RoundRect(100, 100, Window::BaseWidth() - 200, 400, 15).draw(Palette::Lightgrey).drawFrame(0.0, 2.0, Palette::Darkgray);

		// 1P
		RoundRect(150, 150, Window::BaseWidth() - 300, 75, 10).draw(Palette::Gray).drawFrame(0.0, 2.0, Palette::White);
		FontAsset(L"UI_Large")(L"1P").drawCenter({350, 182.5}, Palette::Cyan);
		FontAsset(L"UI")(L"A+Bボタンでスタート").drawCenter({640, 182.5}, Palette::Black);
		FontAsset(L"UI_Large")(m_data->wii[0].isConnected() ? L"OK" : L"検索中...").drawCenter({ 930, 182.5 }, m_data->wii[0].isConnected() ? Palette::Lime : Palette::Yellow);

		// 2P
		RoundRect(150, 265, Window::BaseWidth() - 300, 75, 10).draw(Palette::Gray).drawFrame(0.0, 2.0, Palette::White);
		FontAsset(L"UI_Large")(L"2P").drawCenter({ 350, 297.5 }, Palette::Red);
		FontAsset(L"UI")(L"A+Bボタンでスタート").drawCenter({ 640, 297.5 }, Palette::Black);
		FontAsset(L"UI_Large")(m_data->wii[1].isConnected() ? L"OK" : L"検索中...").drawCenter({ 930, 297.5 }, m_data->wii[1].isConnected() ? Palette::Lime : Palette::Yellow);

		// 説明
		FontAsset(L"UI_Large")(L"①+②ボタンを押してください。").drawCenter(Window::BaseCenter() + Vec2(0, 50), Palette::Black);

		dialog.draw();

		// 右下のくるくる
		Circle(Window::BaseSize() - Vec2(75, 75), 25).drawArc(Time::GetMillisec() * 0.0005, 4.5, 2.0, 2.0);

		buttonCancel.draw();

	}
};

