#pragma once

#include "GameData.hpp"
#include "UI.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Setting : public MyApp::Scene
{
private:

	tgpUI::ToggleSwitch toggleDebug = tgpUI::ToggleSwitch(Window::BaseCenter().movedBy(150, 140), 40, false);
	tgpUI::Button buttonBack = tgpUI::Button(Rect(150, 600, 240, 60), L"< �^�C�g���ɖ߂�", Palette::White);
	tgpUI::Slider sliderVol = tgpUI::Slider(Window::BaseCenter().movedBy(150, -150), 300, 15, 0, 100);
	tgpUI::Meter meter = tgpUI::Meter(Window::BaseCenter(), 300, 15);

public:

	~Setting()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		toggleDebug.setText(L"����", L"�L��");
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

		if (Input::KeyUp.clicked)
		{
			meter.setValue(meter.getValue() + 0.01);
		}

		if (Input::KeyDown.clicked)
		{
			meter.setValue(meter.getValue() - 0.01);
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
		FontAsset(L"UI_Large")(L"�Q�[���ݒ�").drawCenter(Window::BaseCenter().x, 75);

		FontAsset(L"Menu")(L"����").drawCenter(Window::BaseCenter().movedBy(-150, -150));
		sliderVol.draw();

		FontAsset(L"Menu")(L"�f�o�b�O���[�h").drawCenter(Window::BaseCenter().movedBy(-150, 140));
		toggleDebug.draw();

		meter.draw();

		buttonBack.draw();

	}

};
