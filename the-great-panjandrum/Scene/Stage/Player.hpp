﻿#pragma once

#include "../GameData.hpp"
#include "Editor.hpp"
#include "Block.hpp"
#include "Item.hpp"

#include <Siv3D.hpp>

// 左右のブロックとの接触パターン
enum class BlockIntersectType
{
	Left,
	None,
	Right
};

/// <summary>
/// プレイヤー(パンジャンドラム)
/// </summary>
class Player
{
private:

	Vec2 m_pos;

	bool m_isGrounded;
	BlockIntersectType m_intersects;

	PlayMode m_mode;

	double m_speed;

	int m_jumpFrame;
	double m_jumpedY;

	double m_bottom;

	bool m_isAlive;

	double m_TP; // TeaPoint
	double m_earnedTP; // 累計獲得TP

	bool m_isDamaged;

	static constexpr double STEP_TP_DEC = 0.075; // update毎のTPの減少量
	static constexpr double STEP_SPEED = 0.3; // update毎のキーボード左右入力に対する速度の増加/減少量
	static constexpr double MAX_SPEED = 15; // プレイヤーの最大速度

public:

	Player(const PlayMode mode) :
		m_pos(0, 0),
		m_isGrounded(false),
		m_speed(0),
		m_intersects(BlockIntersectType::None),
		m_jumpFrame(0),
		m_isAlive(true),
		m_isDamaged(false),
		m_mode(mode),
		m_TP(TPMAX)
	{}

	static constexpr double TPMAX = 200;

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
		m_intersects = BlockIntersectType::None;

		const Line top(m_pos + Vec2(-90, 0), m_pos + Vec2(90, 0));
		const RectF player(m_pos + Vec2(-100, -200), Vec2(200, 200));

		for (const auto& block : blocks)
		{
			const RectF region = block.get()->getRect();

			// Top
			m_isGrounded |= top.intersects(RectF(region.pos, Vec2(region.w, 20)));

			// Right
			if (player.intersects(region.center + Vec2(-region.w / 2, 0)))
			{
				m_intersects = BlockIntersectType::Right;
			}

			// Left
			if (player.intersects(region.center + Vec2(region.w / 2, 0)))
			{
				m_intersects = BlockIntersectType::Left;
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
				const int tp = static_cast<int>(it->get()->getType());
				m_TP += tp;
				m_earnedTP += tp;

				SoundAsset(L"status03").playMulti();

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
		m_isDamaged = false;
		const RectF player(m_pos + Vec2(-100, -200), Vec2(200, 200));

		auto it = enemies.begin();
		while (it != enemies.end())
		{
			if (it->get()->getDamage(false) != 0)
			{
				m_TP -= it->get()->getDamage(false);

				m_isDamaged = true;

				SoundAsset(L"hit02").playMulti();
			}

			if (it->get()->intersects(player))
			{
				m_TP -= it->get()->getDamage(true);

				m_isDamaged = true;

				SoundAsset(L"hit02").playMulti();

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
		return m_pos.y < m_bottom && m_TP >= 0;
	}

	double getTP() const
	{
		return m_TP;
	}

	double getEarnedTP() const
	{
		return m_earnedTP;
	}

	void update(Wii& wii)
	{
		if (wii.isConnected())
		{
			wii.update();
		}

		if (m_isGrounded)
		{
			m_jumpFrame = 0;

			if ((Input::KeySpace.clicked || (wii.isConnected() && wii.buttonTwo.clicked)) && m_jumpFrame <= 0)
			{
				SoundAsset(L"jump").playMulti();
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

		bool pressed = false;

		if (Input::KeyRight.pressed)
		{
			if (m_speed < 0) m_speed = 0;
			m_speed = Min(MAX_SPEED, m_speed + STEP_SPEED);
			pressed = true;
		}

		if (Input::KeyLeft.pressed)
		{
			if (m_speed > 0) m_speed = 0;
			m_speed = Max(-MAX_SPEED, m_speed - STEP_SPEED);
			pressed = true;
		}

		if (!wii.isConnected() && !pressed)
		{
			if (Abs(m_speed) > 0.75)
			{
				m_speed += m_speed > 0 ? -0.5 : 0.5;
			}
			else
			{
				m_speed = 0;
			}
		}

		if (wii.isConnected())
		{
			if (m_isDamaged)
			{
				wii.rumble(200);
			}

			if (abs(wii.acc().y) >= 0.1)
			{
				m_speed = -wii.acc().y * 2 * MAX_SPEED;
				m_speed = Max(-MAX_SPEED, m_speed - STEP_SPEED);
				m_speed = Min(MAX_SPEED, m_speed + STEP_SPEED);
			}
		}

		bool intersects = m_speed >= 0 ? m_intersects == BlockIntersectType::Right : m_intersects == BlockIntersectType::Left;
		m_pos.x += intersects ? 0 : m_speed;

		m_TP -= STEP_TP_DEC + (abs(m_speed) / MAX_SPEED * STEP_TP_DEC);
	}

	void draw(const bool debugMode) const
	{
		RectF(Vec2(-100, GameInfo::playerPosOffset - 200) + Window::BaseCenter(), 200, 200)(TextureAsset(L"panjandrum")).draw();

		if (m_speed > 0)
		{
			RectF(Vec2(-50, GameInfo::playerPosOffset - 380) + Window::BaseCenter(), 100, 250)(TextureAsset(L"akane01").mirror()).draw();
		}
		else
		{
			RectF(Vec2(-50, GameInfo::playerPosOffset - 380) + Window::BaseCenter(), 100, 250)(TextureAsset(L"akane01")).draw();
		}

		if (debugMode)
		{
			RectF(Vec2(-100, GameInfo::playerPosOffset - 200) + Window::BaseCenter(), 200, 200).drawFrame(1.0, 0.0, Palette::Red);
		}

	}

};