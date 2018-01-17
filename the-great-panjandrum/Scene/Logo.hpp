#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Logo : public MyApp::Scene
{
private:

	const Texture siv3dLogo = Texture(L"Engine/Splash.png");

public:

	void update() override
	{
		if (Input::MouseL.clicked || Input::KeyEnter.clicked)
		{
			changeScene(L"Wiimgr");
		}

	}

	void draw() const override
	{
		siv3dLogo.drawAt(Window::BaseCenter());



	}
};
