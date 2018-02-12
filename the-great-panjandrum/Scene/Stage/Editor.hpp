#pragma once

#include "../GameData.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Stage.hpp" 

#include <Siv3D.hpp>
#include <HamFramework.hpp>


/// <summary>
/// ステージエディター
/// </summary>
class StageEditor : public MyApp::Scene
{
private:


public:

	void update() override
	{
		if (Input::AnyKeyClicked())
		{
			changeScene(L"Title");
		}

	}

	void draw() const override
	{
		FontAsset(L"UI")(L"StageEditor").drawCenter(Window::BaseCenter());

	}
	
};
