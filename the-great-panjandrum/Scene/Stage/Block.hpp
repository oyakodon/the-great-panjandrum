#pragma once

#include "../GameData.hpp"

#include <Siv3D.hpp>

enum class MoveType
{
	Vertical,
	Horizontal
};

class Block
{
protected:

	RectF m_region;

	Vec2 m_playerPos;

	const int edgeWidth = 60;

public:

	Block(const RectF& region)
		: m_region(region)
	{
		if (m_region.size.x < edgeWidth * 2)
		{
			LOG_ERROR(L"Blockのサイズが最低サイズ以下です。表示が乱れる可能性があります。");
		}

	}

	void setPlayerPos(const Vec2& pos)
	{
		m_playerPos = pos;
	}

	virtual void update() = 0;

	RectF getRect() const
	{
		return m_region;
	}

	virtual void draw(const bool debugMode) const = 0;

};

class NormalBlock : public Block
{
public:

	NormalBlock(const RectF& region)
		: Block(region)
	{
		
	}

	void update()
	{

	}

	void draw(const bool debugMode) const
	{
		const Vec2 pos = -m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset) + m_region.pos;
		const RectF edge(pos, edgeWidth, m_region.h);
		// 黒い線がでないように真ん中をちょっと左右に被せる
		const RectF region = RectF(pos + Vec2(edgeWidth - 10, 0), Max(0.0, m_region.w - edgeWidth * 2) + 20, m_region.h);

		// 端っこは黒い線が出るのでちょっとテクスチャをトリミング
		edge(TextureAsset(L"table_white_left")(2, 0, 183, 550)).draw();
		edge.movedBy(m_region.w - edgeWidth, 0)(TextureAsset(L"table_white_right")(0, 0, 180, 550)).draw();
		region(TextureAsset(L"table_white_center")).draw();

		if (debugMode)
		{
			m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).drawFrame(1.0, 0.0, Palette::Red);
		}
	}

};

class MovingBlock : public Block
{
private:

	const MoveType m_moveType;
	const int m_range;
	const int m_speed;

	Vec2 m_origCenter;

public:

	MovingBlock(const RectF& region, MoveType moveType, int range, int speed)
		: Block(region),
		  m_moveType(moveType),
		  m_range(range),
		  m_speed(speed)
	{
		m_origCenter = region.center;
	}

	void update()
	{
		if (m_moveType == MoveType::Vertical)
		{
			m_region.y += m_speed;
			if (m_region.y > m_origCenter.y + m_range)
			{
				m_region.y = m_origCenter.y - m_range;
			}
		}
		else
		{
			m_region.x += m_speed;
			if (m_region.x > m_origCenter.x + m_range)
			{
				m_region.x = m_origCenter.x - m_range;
			}
		}
	}

	void draw(const bool debugMode) const
	{
		const Vec2 pos = -m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset) + m_region.pos;
		const RectF edge(pos, edgeWidth, m_region.h);
		// 黒い線がでないように真ん中をちょっと左右に被せる
		const RectF region = RectF(pos + Vec2(edgeWidth - 10, 0), Max(0.0, m_region.w - edgeWidth * 2) + 20, m_region.h);

		// 端っこは黒い線が出るのでちょっとテクスチャをトリミング
		edge(TextureAsset(L"table_white_left")(2, 0, 183, 550)).draw();
		edge.movedBy(m_region.w - edgeWidth, 0)(TextureAsset(L"table_white_right")(0, 0, 180, 550)).draw();
		region(TextureAsset(L"table_white_center")).draw();

		if (debugMode)
		{
			m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).drawFrame(1.0, 0.0, Palette::Red);
		}
	}
};
