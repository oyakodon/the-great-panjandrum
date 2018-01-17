#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Setting : public MyApp::Scene
{
private:


public:

	void update() override
	{
		if (Input::MouseL.clicked)
		{
			changeScene(L"Title");
		}

	}

	void draw() const override
	{
		FontAsset(L"Title")(L"Setting").drawCenter(Window::BaseCenter());

	}
};
