#pragma once

#include "../GameData.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Stage.hpp" 

#include <Siv3D.hpp>
#include <HamFramework.hpp>

enum class EntityType
{
	Block,
	Item,
	Enemy
};

/// <summary>
/// ステージエディター
/// </summary>
class StageEditor : public MyApp::Scene
{
private:

	StageData m_stage;

	Vec2 m_sightPos;

	bool m_dragging = false;
	int m_draggingItem = 0;
	EntityType m_draggingType;

public:

	void init() override
	{
		StageData::LoadStage(L"Stage/stage_1.csv", m_stage);
		m_sightPos = { 0, 400 };
	}

	void update() override
	{
		{
			const Transformer2D transformer(Mat3x2::Scale(0.75, Window::Center() + Vec2(0, -250)), true);

			// ブロック
			for (size_t i = 0; i < m_stage.blocks.size(); i++)
			{
				m_stage.blocks[i].get()->setPlayerPos(m_sightPos);
				if (!m_dragging && Input::MouseL.pressed && m_stage.blocks[i]->getRect().movedBy(-m_sightPos + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).intersects(Mouse::PosF()))
				{
					m_dragging = true;
					m_draggingItem = i;
					m_draggingType = EntityType::Block;
				}
			}

			// アイテム
			for (size_t i = 0; i < m_stage.items.size(); i++)
			{
				m_stage.items[i].get()->setPlayerPos(m_sightPos);
				if (!m_dragging && Input::MouseL.pressed && m_stage.items[i]->getRect().movedBy(-m_sightPos + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).intersects(Mouse::PosF()))
				{
					m_dragging = true;
					m_draggingItem = i;
					m_draggingType = EntityType::Item;
				}
			}

			// 敵
			for (size_t i = 0; i < m_stage.enemies.size(); i++)
			{
				m_stage.enemies[i].get()->setPlayerPos(m_sightPos);
				if (!m_dragging && Input::MouseL.pressed && m_stage.enemies[i]->getRect().movedBy(-m_sightPos + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).intersects(Mouse::PosF()))
				{
					m_dragging = true;
					m_draggingItem = i;
					m_draggingType = EntityType::Enemy;
				}
			}

			if (m_dragging && Input::MouseL.pressed)
			{
				switch (m_draggingType)
				{
					case EntityType::Block: m_stage.blocks[m_draggingItem].get()->setRect(m_stage.blocks[m_draggingItem].get()->getRect().movedBy(Mouse::DeltaF())); break;
					case EntityType::Item: m_stage.items[m_draggingItem].get()->setRect(m_stage.items[m_draggingItem].get()->getRect().movedBy(Mouse::DeltaF())); break;
					case EntityType::Enemy: m_stage.enemies[m_draggingItem].get()->setRect(m_stage.enemies[m_draggingItem].get()->getRect().movedBy(Mouse::DeltaF())); break;
					default: break;
				}
			}

			if (m_dragging && Input::MouseL.released)
			{
				m_dragging = false;
			}

		}

		if (Input::KeyEscape.clicked)
		{
			changeScene(L"Setting");
		}

		if (Input::KeyRight.pressed)
		{
			m_sightPos.x += 10;
		}

		if (Input::KeyLeft.pressed)
		{
			m_sightPos.x -= 10;
		}

		if (Input::KeyUp.pressed)
		{
			m_sightPos.y -= 10;
		}

		if (Input::KeyDown.pressed)
		{
			m_sightPos.y += 10;
		}

		m_sightPos.x += Mouse::Wheel() * 100;


	}

	void draw() const override
	{
		{
			const Transformer2D transformer(Mat3x2::Scale(0.75, Window::Center() + Vec2(0, -250)), true);

			// 背景
			Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

			// ブロック
			for (size_t i = 0; i < m_stage.blocks.size(); i++)
			{
				m_stage.blocks[i].get()->draw(m_data->debugMode);
			}

			// アイテム
			for (size_t i = 0; i < m_stage.items.size(); i++)
			{
				m_stage.items[i].get()->draw();
			}

			// 敵
			for (size_t i = 0; i < m_stage.enemies.size(); i++)
			{
				m_stage.enemies[i].get()->draw();
			}

			// ゴールの旗
			RectF(m_stage.goalPos.movedBy(-m_sightPos + Vec2(-50, GameInfo::playerPosOffset - 50) + Window::BaseCenter()), 100, 100)(TextureAsset(L"hata")).draw();
		}

		RectF(0, 595, Window::BaseWidth(), 125).draw(Palette::Green);

	}

};
