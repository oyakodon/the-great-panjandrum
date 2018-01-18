#pragma once

#include "../GameData.hpp"

#include <Siv3D.hpp>

class Block
{
private:

	RectF m_region;

	const Texture m_texture;

	Vec2 m_playerPosition;

public:

	Block() {}

	Block(const RectF& region) :
		m_region(region),
		m_texture(L"Asset/table_white.png") {}

	void setPlayerPos(const Vec2& pos)
	{
		m_playerPosition = pos;
	}

	void update() {}

	bool intersects(const Vec2& pos) const
	{
		return m_region.intersects(pos);
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPosition + Window::BaseCenter())(m_texture).draw();
	}

};