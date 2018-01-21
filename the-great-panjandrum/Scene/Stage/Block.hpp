#pragma once

#include "../GameData.hpp"

#include <Siv3D.hpp>

class Block
{
private:

	RectF m_region;

	Vec2 m_playerPosition;

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
		m_playerPosition = pos;
	}

	void update() {}

	bool intersects(const Vec2& pos) const
	{
		return m_region.intersects(pos);
	}

	void draw(const bool debugMode) const
	{
		const Vec2 pos = -m_playerPosition + Window::BaseCenter() + m_region.pos;
		const RectF edge(pos, edgeWidth, m_region.h);
		// 黒い線がでないように真ん中をちょっと左右に被せる
		const RectF region = RectF(pos + Vec2(edgeWidth - 10, 0), Max(0.0, m_region.w - edgeWidth) * 2 + 20, m_region.h);

		// 端っこは黒い線が出るのでちょっとテクスチャをトリミング
		edge(TextureAsset(L"table_white_left")(2, 0, 183, 550)).draw();
		edge.movedBy(m_region.w - edgeWidth, 0)(TextureAsset(L"table_white_right")(0, 0, 180, 550)).draw();
		region(TextureAsset(L"table_white_center")).draw();

		if (debugMode)
		{
			m_region.movedBy(-m_playerPosition + Window::BaseCenter()).drawFrame(1.0, 0.0, Palette::Red);
		}

	}

};