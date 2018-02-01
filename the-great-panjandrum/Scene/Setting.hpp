#pragma once

#include "GameData.hpp"
#include "UI.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Setting : public MyApp::Scene
{
private:

	tgpUI::ToggleSwitch toggleDebug = tgpUI::ToggleSwitch(Window::BaseCenter().moveBy(150, 140), 40, false);
	tgpUI::Button buttonBack = tgpUI::Button(Rect(150, 600, 240, 60), L"< タイトルに戻る", Palette::White);
	tgpUI::Slider sliderVol = tgpUI::Slider(Window::BaseCenter().moveBy(150, -150), 300, 15, 0, 100);

public:

	~Setting()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		toggleDebug.setText(L"無効", L"有効");
		toggleDebug.setValue(m_data->debugMode);
		sliderVol.setValue(static_cast<int>(MasterVoice::GetVolume() * 100));
	}

	void update() override
	{
		toggleDebug.update();
		buttonBack.update();
		sliderVol.update();

		if (toggleDebug.isChanged())
		{
			m_data->debugMode = toggleDebug.getValue();

			if (m_data->debugMode)
			{
				Console::Open();
			}
			else
			{
				Console::Close();
			}

		}

		if (sliderVol.isChanged())
		{
			MasterVoice::SetVolume(sliderVol.getValue() / 100.0);
		}

		if (sliderVol.isReleased())
		{
			SoundAsset(L"one01").playMulti();
		}

		if (buttonBack.isClicked() | Input::KeyEscape.clicked)
		{
			changeScene(L"Title");
		}

		if (toggleDebug.mouseOver() | buttonBack.mouseOver() | sliderVol.mouseOver())
		{
			Cursor::SetStyle(CursorStyle::Hand);
		}
		else
		{
			Cursor::SetStyle(CursorStyle::Default);
		}

	}

	void draw() const override
	{
		FontAsset(L"UI_Large")(L"ゲーム設定").drawCenter(Window::BaseCenter().x, 75);

		FontAsset(L"Menu")(L"音量").drawCenter(Window::BaseCenter() + Vec2(-150, -150));
		sliderVol.draw();

		FontAsset(L"Menu")(L"デバッグモード").drawCenter(Window::BaseCenter() + Vec2(-150, 140));
		toggleDebug.draw();

		buttonBack.draw();

	}

};
