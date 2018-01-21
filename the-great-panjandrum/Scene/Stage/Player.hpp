#pragma once

#include "../GameData.hpp"
#include "Block.hpp"

#include <Siv3D.hpp>

class Player
{
private:

	Vec2 m_position;

	bool m_isGrounded;
	int m_intersectsBlock; // -1: ç∂, 0: ñ≥Çµ, 1: âE

	int m_jumpFrame;
	double m_jumpedY;

	int m_bottom;

	bool m_isAlive;

public:

	Player() :
		m_position(100, 200),
		m_isGrounded(false),
		m_intersectsBlock(0),
		m_jumpFrame(0),
		m_isAlive(true) {}

	Vec2 getPos() const
	{
		return m_position;
	}

	void checkGround(const Array<Block>& blocks)
	{
		m_isGrounded = false;
		m_intersectsBlock = 0;

		const Line top(m_position + Vec2(-90, 0), m_position + Vec2(90, 0));
		const RectF player(m_position + Vec2(-100, -200), Vec2(200, 200));

		for (const auto block : blocks)
		{
			const RectF region = block.getRect();

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

	void setBottom(int value)
	{
		m_bottom = value;
	}

	bool isAlive()
	{
		return m_position.y < m_bottom;
	}

	void update()
	{
		if (m_isGrounded)
		{
			m_jumpFrame = 0;

			if (Input::KeySpace.clicked && m_jumpFrame <= 0)
			{
				m_jumpFrame = 48;
				m_jumpedY = m_position.y;
			}
		}
		else if (m_jumpFrame == 0)
		{
			m_position.y += 16.0;
		}

		if (m_jumpFrame > 0)
		{
			m_position.y = m_jumpedY + 2 * (12 - 0.5 * (m_jumpFrame - 1)) * (12 - 0.5 * (m_jumpFrame - 1)) - 288;
			m_jumpFrame--;
		}

		if (Input::KeyRight.pressed && m_intersectsBlock != 1)
		{
			m_position.x += 7.5;
		}

		if (Input::KeyLeft.pressed && m_intersectsBlock != -1)
		{
			m_position.x -= 7.5;
		}

	}

	void draw(const bool debugMode) const
	{
		RectF(Vec2(-100, -50) + Window::BaseCenter(), 200, 200)(TextureAsset(L"panjandrum")).draw();

		if (debugMode)
		{
			RectF(Vec2(-100, -50) + Window::BaseCenter(), 200, 200).drawFrame(1.0, 0.0, Palette::Red);
		}
			
	}

};