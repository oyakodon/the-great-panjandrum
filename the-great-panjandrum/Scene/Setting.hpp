#pragma once

#include "GameData.hpp"
#include "UI.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Setting : public MyApp::Scene
{
private:

	tgpUI::Slider m_sliderVol = tgpUI::Slider(Window::BaseCenter().movedBy(150, -150), 300, 15, 0, 100);
	tgpUI::ToggleSwitch m_toggleDebug = tgpUI::ToggleSwitch(Window::BaseCenter().movedBy(150, 85), 40, false);
	tgpUI::Button m_buttonEdit = tgpUI::Button(Rect(Window::BaseCenter().movedBy(50, 140), 240, 60), L"ステージエディター", Palette::White);
	tgpUI::Button m_buttonBack = tgpUI::Button(Rect(150, 600, 240, 60), L"< タイトルに戻る", Palette::White);

public:

	~Setting()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		m_toggleDebug.setText(L"無効", L"有効");
		m_toggleDebug.setValue(m_data->debugMode);
		m_sliderVol.setValue(static_cast<int>(MasterVoice::GetVolume() * 100));
	}

	void update() override
	{
		m_toggleDebug.update();
		m_buttonEdit.update();
		m_buttonBack.update();
		m_sliderVol.update();

		if (m_toggleDebug.isChanged())
		{
			m_data->debugMode = m_toggleDebug.getValue();

			if (m_data->debugMode)
			{
				Console::Open();
			}
			else
			{
				Console::Close();
			}

		}

		if (m_buttonEdit.isClicked())
		{
			changeScene(L"StageEditor");
		}

		if (m_sliderVol.isChanged())
		{
			MasterVoice::SetVolume(m_sliderVol.getValue() / 100.0);
		}

		if (m_sliderVol.isReleased())
		{
			SoundAsset(L"one01").playMulti();
		}

		if (m_buttonBack.isClicked() | Input::KeyEscape.clicked)
		{
			changeScene(L"Title");
		}

		bool mouseOver = m_toggleDebug.mouseOver() | m_buttonBack.mouseOver() | m_sliderVol.mouseOver() | m_buttonEdit.mouseOver();
		Cursor::SetStyle(mouseOver ? CursorStyle::Hand : CursorStyle::Default);

	}

	void draw() const override
	{
		// 背景
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		FontAsset(L"UI_Large")(L"ゲーム設定").drawCenter(Window::BaseCenter().x, 75);

		FontAsset(L"Menu")(L"音量").drawCenter(Window::BaseCenter().movedBy(-150, -150));
		m_sliderVol.draw();

		FontAsset(L"Menu")(L"デバッグモード").drawCenter(Window::BaseCenter().movedBy(-150, 85));
		m_toggleDebug.draw();

		FontAsset(L"Menu")(L"ステージの編集").drawCenter(Window::BaseCenter().movedBy(-150, 170));
		m_buttonEdit.draw();

		m_buttonBack.draw();

	}

};
