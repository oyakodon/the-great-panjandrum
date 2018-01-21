#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Logo : public MyApp::Scene
{
private:

	const Texture siv3dLogo = Texture(L"Engine/Splash.png");

public:

	~Logo()
	{
		SoundAsset(L"one01").stop();
		SoundAsset(L"one01").setVolume(1.0);
	}

	void init() override
	{
		SoundAsset(L"one01").setVolume(0.1);
		SoundAsset(L"one01").play();
	}

	void update() override
	{
		if ((Input::MouseL | Input::KeyEnter | Input::KeyEscape).clicked)
		{
			changeScene(L"Wiimgr");
		}

	}

	void draw() const override
	{
		siv3dLogo.drawAt(Window::BaseCenter() + Vec2(0, -100));

		for (size_t i : step(GameInfo::Descriptions.size()))
		{
			FontAsset(L"Menu")(GameInfo::Descriptions[i]).drawCenter(Window::BaseCenter() + Vec2(0, 100 + i * 75));
		}

	}
};
