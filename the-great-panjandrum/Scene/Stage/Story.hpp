#pragma once

#include "../GameData.hpp"
#include "Player.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

/// <summary>
/// ノーマルステージ(ストーリーモード)
/// </summary>
class StageStory : public MyApp::Scene
{
private:
	
	Player player;

	StageData stage;

public:

	void init() override
	{
		// add blocks
		StageEditor::LoadStage(L"Stage/stage_1.csv", stage);

		//blocks.emplace_back(NormalBlock({ -400, 400, 1000, 200 }));
		//blocks.emplace_back(NormalBlock({ 150, 250, 250, 200 }));
		//blocks.emplace_back(NormalBlock({ 800, 400, 400, 200 }));
		//blocks.emplace_back(NormalBlock({ 1300, 200, 400, 200 }));

		player.setBottom(700);

	}

	void update() override
	{
		for (size_t i = 0; i < stage.blocks.size(); i++)
		{
			stage.blocks[i].setPlayerPos(player.getPos());
			stage.blocks[i].update();
		}

		player.checkGround(stage.blocks);
		player.checkItem(stage.items);
		player.update();

		if (!player.isAlive())
		{
			changeScene(L"Title");
		}

	}

	void draw() const override
	{
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		for (size_t i = 0; i < stage.blocks.size(); i++)
		{
			stage.blocks[i].draw(m_data->debugMode);
		}

		for (size_t i = 0; i < stage.items.size(); i++)
		{
			stage.items[i]draw();
		}

		player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			Line({ player.getPos().x - Window::BaseWidth() / 2, 600 }, { player.getPos().x + Window::BaseWidth() / 2, 600 }).moveBy(-player.getPos() + Vec2(0, 150) + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

	}

};

