#pragma once

#include <Siv3D.hpp>

/// <summary>
/// 敵の種類　(衝突した時のダメージ)
/// </summary>
enum class EnemyType : int
{
	Bunchin = 10,
	Yotiyoti = 15,
	Danmaku = 20
};

/// <summary>
/// 敵
/// </summary>
class Enemy
{
protected:

	RectF m_region;

	PlayMode m_mode;

	Vec2 m_playerPos;

public:

	Enemy(const Vec2& pos)
	{
		m_region = RectF(180).setCenter(pos);
	}

	virtual ~Enemy() {}

	virtual int getDamage(bool intersects) = 0;

	void setPlayerPos(const Vec2& pos)
	{
		m_playerPos = pos;
	}

	void setPlayMode(const PlayMode mode)
	{
		m_mode = mode;
	}

	bool intersects(const RectF& region)
	{
		return region.intersects(m_region);
	}

	virtual void update() = 0;

	virtual void draw() const = 0;

};

/// <summary>
/// Bunchin, 動かないけど当たると痛い
/// </summary>
class EnemyBunchin : public Enemy
{
public:

	EnemyBunchin(const Vec2& pos)
		: Enemy(pos)
	{
		
	}

	void update()
	{

	}

	int getDamage(bool intersects)
	{
		return intersects ? static_cast<int>(EnemyType::Bunchin) : 0;
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset))(TextureAsset(L"juujigun")).draw();
	}

};

/// <summary>
/// Yotiyoti, よちよちブロックの上を左右に動く。当たると痛い。
/// </summary>
class EnemyYotiyoti : public Enemy
{
private:

	const int m_range; // +/- どのくらい移動するか (座標)

	const int m_speed = 3; // 移動速度

	int m_relative; // 相対座標
	bool m_faceRight;

public:

	EnemyYotiyoti(const Vec2& pos, const int range)
		: Enemy(pos),
		  m_range(range),
		  m_relative(0),
		  m_faceRight(true)
	{

	}

	void update()
	{
		if (Abs(m_relative) >= m_range)
		{
			m_faceRight = !m_faceRight;
		}

		m_relative += (m_faceRight ? 1 : -1) * m_speed;
		m_region.moveBy((m_faceRight ? 1 : -1) * m_speed, 0);
	}

	int getDamage(bool intersects)
	{
		return intersects ? static_cast<int>(EnemyType::Yotiyoti) : 0;
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset))(TextureAsset(L"chusei_heishi_tetsukabuto")).draw();
	}

};

/// <summary>
/// Danmaku, 空に浮かびながら弾を打ってくる。弾幕ってほどでもない。
/// </summary>
class EnemyDanmaku : public Enemy
{
private:

	static constexpr int BULLET_DAMAGE = 10;

	Array<std::pair<Vec2, Vec2>> m_bullets;
	Stopwatch m_swInterval;

	static constexpr int BULLET_SPEED = 3;

public:

	EnemyDanmaku(const Vec2& pos)
		: Enemy(pos)
	{
		
	}

	void update()
	{
		if (m_swInterval.ms() >= 300)
		{
			m_swInterval.reset();
		}

		if (!m_swInterval.isActive() && m_region.center.distanceFrom(m_playerPos + Vec2(0, -100)) <= 500)
		{
			m_bullets.emplace_back(std::make_pair(m_region.center, m_playerPos + Vec2(0, -100)));
			m_swInterval.start();
		}

		auto it = m_bullets.begin();
		while (it != m_bullets.end())
		{
			double dx = it->second.x - it->first.x;
			double dy = it->second.y - it->first.y;

			double prevDist = it->first.distanceFrom(it->second);
			it->first.moveBy(BULLET_SPEED * Cos(Atan2(dy, dx)), BULLET_SPEED * Sin(Atan2(dy, dx)));

			if (prevDist <= it->first.distanceFrom(it->second))
			{
				it = m_bullets.erase(it);
			}
			else
			{
				it++;
			}
		}

	}

	int getDamage(bool intersects)
	{
		if (intersects)
		{
			return static_cast<int>(EnemyType::Danmaku);
		}

		const RectF player(m_playerPos + Vec2(-100, -200), Vec2(200, 200));

		int damage = 0;

		auto it = m_bullets.begin();
		while (it != m_bullets.end())
		{
			if (Circle(it->first, 10).intersects(player))
			{
				damage += BULLET_DAMAGE;
				it = m_bullets.erase(it);
			}
			else
			{
				it++;
			}
		}

		return damage;
	}

	void draw() const
	{
		// 敵
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset))(TextureAsset(L"war_sensya_noman")).draw();

		// 弾
		for (const auto p : m_bullets)
		{
			Circle(p.first, 10).movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Red);
		}

	}

};
