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

	Player m_player;

	StageData m_stage;

	tgpUI::Meter m_tpMeter = tgpUI::Meter({ 315, 20 }, 600, 20);

public:

	void init() override
	{
		StageEditor::LoadStage(L"Stage/stage_1.csv", m_stage);
		m_player.setBottom(m_stage.deadLine);
	}

	void update() override
	{
		for (size_t i = 0; i < m_stage.blocks.size(); i++)
		{
			m_stage.blocks[i].get()->setPlayerPos(m_player.getPos());
			m_stage.blocks[i].get()->update();
		}

		for (size_t i = 0; i < m_stage.items.size(); i++)
		{
			m_stage.items[i].get()->setPlayerPos(m_player.getPos());
			m_stage.items[i].get()->update();
		}

		m_player.checkGround(m_stage.blocks);
		m_player.checkItem(m_stage.items);
		m_player.update();

		if (!m_player.isAlive())
		{
			changeScene(L"Title");
		}

		m_tpMeter.setValue(m_player.getTP() / 100.0);

	}

	void draw() const override
	{
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		for (size_t i = 0; i < m_stage.blocks.size(); i++)
		{
			m_stage.blocks[i].get()->draw(m_data->debugMode);
		}

		for (size_t i = 0; i < m_stage.items.size(); i++)
		{
			m_stage.items[i].get()->draw();
		}

		m_player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			const Vec2 p = { m_player.getPos().x, m_stage.deadLine };
			const Vec2 w_half = { Window::BaseWidth() / 2, 0 };
			Line(p.movedBy(-w_half), p.movedBy(w_half)).moveBy(-m_player.getPos() + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

		m_tpMeter.draw();

	}

};

