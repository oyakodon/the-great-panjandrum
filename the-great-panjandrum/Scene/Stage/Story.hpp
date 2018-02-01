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

	~StageStory()
	{
		ClearPrint();
	}

	void init() override
	{
		StageEditor::LoadStage(L"Stage/stage_1.csv", stage);
		player.setBottom(stage.deadLine);
	}

	void update() override
	{
		for (size_t i = 0; i < stage.blocks.size(); i++)
		{
			stage.blocks[i].get()->setPlayerPos(player.getPos());
			stage.blocks[i].get()->update();
		}

		for (size_t i = 0; i < stage.items.size(); i++)
		{
			stage.items[i].get()->setPlayerPos(player.getPos());
			stage.items[i].get()->update();
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
			stage.blocks[i].get()->draw(m_data->debugMode);
		}

		for (size_t i = 0; i < stage.items.size(); i++)
		{
			stage.items[i].get()->draw();
		}

		player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			ClearPrint();
			Println(L"Tea Point: ", player.getTP());
			const Vec2 p = { player.getPos().x, stage.deadLine };
			const Vec2 w_half = { Window::BaseWidth() / 2, 0 };
			Line(p.movedBy(-w_half), p.movedBy(w_half)).moveBy(-player.getPos() + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

	}

};

