#pragma once

#include "../GameData.hpp"
#include "Block.hpp"

#include <Siv3D.hpp>

class Player
{
private:

	Vec2 m_position;

	bool m_isGrounded;

	int m_jumpFrame;

	int m_bottom;

	double m_jumpedY;

	bool m_isAlive;

public:

	Player() :
		m_position(100, 200),
		m_isGrounded(false),
		m_jumpFrame(0),
		m_isAlive(true) {}

	Vec2 getPos() const
	{
		return m_position;
	}

	void checkGround(const Array<Block>& blocks)
	{
		m_isGrounded = false;

		for (size_t i = 0; i < blocks.size(); i++)
		{
			if (blocks[i].intersects(m_position))
			{
				m_isGrounded = true;
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

		if (Input::KeyRight.pressed)
		{
			m_position.x += 7.5;
		}

		if (Input::KeyLeft.pressed)
		{
			m_position.x -= 7.5;
		}

	}

	void draw(const bool debugMode) const
	{
		RectF(Vec2(-100, -200) + Window::BaseCenter(), 200, 200)(TextureAsset(L"panjandrum")).draw();

		if (debugMode)
		{
			RectF(Vec2(-100, -200) + Window::BaseCenter(), 200, 200).drawFrame(1.0, 0.0, Palette::Red);
		}
			
	}

};