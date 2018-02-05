#pragma once

#include "../GameData.hpp"
#include "Editor.hpp"
#include "Block.hpp"
#include "Item.hpp"

#include <Siv3D.hpp>

/// <summary>
/// プレイヤー(パンジャンドラム)
/// </summary>
class Player
{
private:

	Vec2 m_pos;

	bool m_isGrounded;
	int m_intersectsBlock; // -1: 左, 0: 無し, 1: 右

	int m_jumpFrame;
	double m_jumpedY;

	double m_bottom;

	bool m_isAlive;

	int m_tp; // TeaPoint

public:

	Player() :
		m_pos(0, 0),
		m_isGrounded(false),
		m_intersectsBlock(0),
		m_jumpFrame(0),
		m_isAlive(true),
		m_tp(50)
	{}

	Vec2 getPos() const
	{
		return m_pos;
	}

	bool checkGoal(const Vec2& goal)
	{
		const RectF player(m_pos + Vec2(-100, -200), Vec2(200, 200));
		return player.intersects(goal);
	}

	void checkGround(const Array<std::shared_ptr<Block>>& blocks)
	{
		m_isGrounded = false;
		m_intersectsBlock = 0;

		const Line top(m_pos + Vec2(-90, 0), m_pos + Vec2(90, 0));
		const RectF player(m_pos + Vec2(-100, -200), Vec2(200, 200));

		for (const auto& block : blocks)
		{
			const RectF region = block.get()->getRect();

			// Top
			if (top.intersects(RectF(region.pos, Vec2(region.w, 20))))
			{
				m_isGrounded = true;
			}

			// Right
			if (player.intersects(region.center + Vec2(-region.w / 2, 0)))
			{
				m_intersectsBlock = 1;
			}

			// Left
			if (player.intersects(region.center + Vec2(region.w / 2, 0)))
			{
				m_intersectsBlock = -1;
			}

		}
	}

	void checkItem(Array<std::shared_ptr<Item>>& items)
	{
		const RectF player(m_pos + Vec2(-100, -200), Vec2(200, 200));

		auto it = items.begin();
		while (it != items.end())
		{
			if (it->get()->intersects(player))
			{
				m_tp += static_cast<int>(it->get()->getType());

				it = items.erase(it);
			}
			else
			{
				it++;
			}
		}

	}

	void checkEnemy(Array<std::shared_ptr<Enemy>>& enemies)
	{
		const RectF player(m_pos + Vec2(-100, -200), Vec2(200, 200));

		auto it = enemies.begin();
		while (it != enemies.end())
		{
			if (it->get()->intersects(player))
			{
				m_tp -= it->get()->getDamage(true);

				it = enemies.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void setPos(const Vec2& pos)
	{
		m_pos = pos;
	}

	void setBottom(double value)
	{
		m_bottom = value;
	}

	bool isAlive()
	{
		return m_pos.y < m_bottom;
	}

	int getTP() const
	{
		return m_tp;
	}

	void update()
	{
		if (m_isGrounded)
		{
			m_jumpFrame = 0;

			if (Input::KeySpace.clicked && m_jumpFrame <= 0)
			{
				m_jumpFrame = 48;
				m_jumpedY = m_pos.y;
			}
		}
		else if (m_jumpFrame == 0)
		{
			m_pos.y += 16.0;
		}

		if (m_jumpFrame > 0)
		{
			m_pos.y = m_jumpedY + 2 * (12 - 0.5 * (m_jumpFrame - 1)) * (12 - 0.5 * (m_jumpFrame - 1)) - 288;
			m_jumpFrame--;
		}

		if (Input::KeyRight.pressed && m_intersectsBlock != 1)
		{
			m_pos.x += 7.5;
		}

		if (Input::KeyLeft.pressed && m_intersectsBlock != -1)
		{
			m_pos.x -= 7.5;
		}

	}

	void draw(const bool debugMode) const
	{
		RectF(Vec2(-100, GameInfo::playerPosOffset - 200) + Window::BaseCenter(), 200, 200)(TextureAsset(L"panjandrum")).draw();

		if (debugMode)
		{
			RectF(Vec2(-100, GameInfo::playerPosOffset - 200) + Window::BaseCenter(), 200, 200).drawFrame(1.0, 0.0, Palette::Red);
		}
			
	}

};