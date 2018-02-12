#pragma once

#include <Siv3D.hpp>

/// <summary>
/// アイテムの種類
/// </summary>
enum class ItemType : int
{
	Tea = 10,
	Marmite = 20
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
		switch (m_type)
		{
			case ItemType::Marmite: m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset))(TextureAsset(L"cooking_marmite")).draw(); break;
			case ItemType::Tea: m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset))(TextureAsset(L"tea_straight")).draw(); break;
			default: break;
		}
	}

};

