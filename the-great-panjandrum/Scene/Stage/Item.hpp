#pragma once

#include <Siv3D.hpp>

/// <summary>
/// アイテムの種類
/// </summary>
enum class ItemType : int
{
	Tea = 5,
	Marmite = 10
};

/// <summary>
/// アイテム
/// </summary>
class Item
{
private:

	const ItemType m_type;

	RectF m_region;

	Vec2 m_playerPos;

public:
	
	Item(const Vec2& pos, const ItemType& type)
		: m_type(type)
	{
		m_region = RectF(75).setCenter(pos);
	}

	void update()
	{
		
	}

	void setPlayerPos(const Vec2& pos)
	{
		m_playerPos = pos;
	}

	bool intersects(const RectF& region)
	{
		return m_region.intersects(region);
	}

	ItemType getType() const
	{
		return m_type;
	}

	void draw() const
	{
		// 確認用
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);

		/*switch (m_type)
		{
			default: break;
		}*/

	}

};

