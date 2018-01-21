#pragma once

#include "../GameData.hpp"
#include "Player.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

class StageStory : public MyApp::Scene
{
private:
	
	Player player;

	Array<Block> blocks;

public:

	void init() override
	{
		player.setBottom(700);

		// add blocks
		blocks.push_back(Block({ -400, 400, 1000, 200 }));
		blocks.push_back(Block({ 150, 250, 250, 200 }));
		blocks.push_back(Block({ 800, 400, 400, 200 }));
		blocks.push_back(Block({ 1300, 200, 400, 200 }));

	}

	void update() override
	{
		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].setPlayerPos(player.getPos());
			blocks[i].update();
		}

		player.checkGround(blocks);
		player.update();

		if (!player.isAlive())
		{
			changeScene(L"Title");
		}

	}

	void draw() const override
	{
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].draw(m_data->debugMode);
		}

		player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			Line({ player.getPos().x - Window::BaseWidth() / 2, 600 }, { player.getPos().x + Window::BaseWidth() / 2, 600 }).moveBy(-player.getPos() + Vec2(0, 150) + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

	}

};

