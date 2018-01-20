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

	const Texture m_background;

public:

	StageStory()
		: m_background(L"Example/Windmill.png") {}

	void init() override
	{
		player.setBottom(600);

		// add blocks
		blocks.push_back(Block({ -400, 400, 200, 200 }));
		blocks.push_back(Block({ -200, 400, 200, 200 }));
		blocks.push_back(Block({ 0, 400, 200, 200 }));
		blocks.push_back(Block({ 200, 400, 200, 200 }));
		blocks.push_back(Block({ 200, 200, 200, 200 }));
		blocks.push_back(Block({ 400, 400, 200, 200 }));
		blocks.push_back(Block({ 800, 400, 200, 200 }));
		blocks.push_back(Block({ 1000, 400, 200, 200 }));
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
		m_background.resize(Window::BaseWidth(), Window::BaseHeight()).draw();;

		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].draw(m_data->debugMode);
		}

		player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			Line({ player.getPos().x - Window::BaseWidth() / 2, 600 }, { player.getPos().x + Window::BaseWidth() / 2, 600 }).moveBy(-player.getPos() + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

		// デバッグモード表示
		if (m_data->debugMode)
		{
			const Size debugSize = FontAsset(L"Debug")(L"DEBUGMODE").region().size;
			FontAsset(L"Debug")(L"DEBUGMODE").drawAt(Window::BaseSize().moveBy(-debugSize), Palette::Orange);
		}

	}

};

