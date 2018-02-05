#pragma once

#include <Siv3D.hpp>

/// <summary>
/// 敵の種類　(衝突した時のダメージ)
/// </summary>
enum class EnemyType : int
{
	Immovable = 10,
	Totter = 15,
	Barrage = 20
};

/// <summary>
/// 敵
/// </summary>
class Enemy
{
protected:

	RectF m_region;

	Vec2 m_playerPos;

public:

	Enemy(const Vec2& pos)
	{
		m_region = RectF(120).setCenter(pos);
	}

	virtual ~Enemy() {}

	virtual int getDamage(bool intersects) = 0;

	void setPlayerPos(const Vec2& pos)
	{
		m_playerPos = pos;
	}

	bool intersects(const RectF& region)
	{
		return region.intersects(m_region);
	}

	virtual void update() = 0;

	virtual void draw() const = 0;

};

/// <summary>
/// Immovable, 動かないけど当たると痛い
/// </summary>
class EnemyImmovable : public Enemy
{
public:

	EnemyImmovable(const Vec2& pos)
		: Enemy(pos)
	{
		
	}

	void update()
	{

	}

	int getDamage(bool intersects)
	{
		return intersects ? static_cast<int>(EnemyType::Immovable) : 0;
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);
	}

};

/// <summary>
/// Totter, よちよちブロックの上を左右に動く。当たると痛い。
/// </summary>
class EnemyTotter : public Enemy
{
private:

	const int m_range; // +/- どのくらい移動するか (座標)

public:

	EnemyTotter(const Vec2& pos, const int range)
		: Enemy(pos),
		  m_range(range)
	{

	}

	void update()
	{

	}

	int getDamage(bool intersects)
	{
		return intersects ? static_cast<int>(EnemyType::Totter) : 0;
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);
	}

};

/// <summary>
/// Barrage, 空に浮かびながら弾を打ってくる。弾幕ってほどでもない。
/// </summary>
class EnemyBarrage : public Enemy
{

public:

	EnemyBarrage(const Vec2& pos)
		: Enemy(pos)
	{

	}

	void update()
	{

	}

	int getDamage(bool intersects)
	{
		return intersects ? static_cast<int>(EnemyType::Barrage) : 0;
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);
	}

};
