#pragma once

#include "../GameData.hpp"

#include <Siv3D.hpp>

class Block
{
private:

	// ブロックの領域
	RectF m_region;

	// ブロックのテキスチャ（画像）
	const Texture m_texture;

	// プレイヤーの現在の位置
	Vec2 m_playerPosition;

public:

	Block() {}

	Block(const RectF& region) :
		m_region(region),
		m_texture(L"Example/Brick.jpg") {}

	// プレイヤーの現在位置を更新する関数
	void setPlayerPos(const Vec2& pos)
	{
		m_playerPosition = pos;
	}

	// 描画以外の操作をする関数
	void update() {}

	// 点との当たり判定を取る関数
	bool intersects(const Vec2 &shape) const
	{
		return m_region.intersects(shape);
	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw() const
	{
		m_region.movedBy(-m_playerPosition + Window::BaseCenter())(m_texture).draw();
	}

};