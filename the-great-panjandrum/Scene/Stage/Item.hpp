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

	const RectF m_region;

	const ItemType m_type;

public:
	
	Item(const RectF region, const ItemType type)
		: m_region(region),
		  m_type(type)
	{

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

		switch (m_type)
		{
			default: break;
		}

	}

};

