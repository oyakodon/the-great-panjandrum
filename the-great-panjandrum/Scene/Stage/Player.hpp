#pragma once

#include "../GameData.hpp"
#include "Block.hpp"

#include <Siv3D.hpp>

class Player
{
private:

	// プレイヤーの座標
	Vec2 m_position;

	// プレイヤーのテクスチャ（画像）
	const Texture m_texture;

	// 地面に接しているか否か
	bool m_isGrounded;

	// 残りのジャンプ時間
	int m_jumpFrame;

	// 最低高度
	int m_bottom;

	// 生きているかどうか
	bool m_isAlive;

public:

	Player() :
		m_position(100, 200),
		m_texture(L"Asset/panjandrum.png"),
		m_isGrounded(false),
		m_jumpFrame(0),
		m_isAlive(true) {}

	// 位置を取得する関数
	Vec2 getPos() const
	{
		return m_position;
	}

	// 地面に接しているかを更新する関数
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

	// 生きているかどうかを返す関数
	bool isAlive()
	{
		return m_isAlive;
	}

	// 描画以外の操作をする関数
	void update()
	{
		if (m_isGrounded)
		{
			if (Input::KeySpace.clicked && m_jumpFrame <= 0)
			{
				m_jumpFrame = 30;
			}
		}
		else
		{
			m_position.y += 10.0;
		}

		if (m_jumpFrame > 0)
		{
			m_position.y -= 20.0;
			m_jumpFrame--;
		}
		if (Input::KeyRight.pressed)
		{
			m_position.x += 5.0;
		}
		if (Input::KeyLeft.pressed)
		{
			m_position.x -= 5.0;
		}

		if (m_isAlive && m_position.y >= m_bottom)
		{
			m_isAlive = false;
		}

	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw() const
	{
		RectF(Vec2(-100, -200) + Window::BaseCenter(), 200, 200)(m_texture).draw();
	}

};