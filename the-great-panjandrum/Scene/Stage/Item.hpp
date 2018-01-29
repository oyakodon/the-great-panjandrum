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

public:
	
	Item(const Vec2& pos, const ItemType& type)
		: m_type(type)
	{
		m_region = RectF(
			pos.x - 15,
			pos.y - 15,
			30,
			30
		);

	}

	void update()
	{
		
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
		m_region.draw(Palette::Yellow);

		/*switch (m_type)
		{
			default: break;
		}*/

	}

};

