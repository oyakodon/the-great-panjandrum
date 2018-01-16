#pragma once

#include "GameData.hpp"

#include "../Wiimote/wm4s3d.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Wiimgr : public MyApp::Scene
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
		FontAsset(L"Title")(L"Wiimote Manager").drawCenter(Window::BaseCenter());

	}
};

