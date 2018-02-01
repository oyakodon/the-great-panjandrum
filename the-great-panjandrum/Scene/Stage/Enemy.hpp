#pragma once

#include <Siv3D.hpp>

/// <summary>
/// 敵の種類
/// </summary>
enum class EnemyType
{
	Immovable,
	Totter,
	Barrage
};

/// <summary>
/// 敵
/// </summary>
class Enemy
{
protected:

	const Vec2 m_pos;

	Vec2 m_playerPos;

public:

	Enemy(const Vec2& pos)
		: m_pos(pos)
	{ }

	virtual ~Enemy() {}

	virtual int getDamage() = 0;

	void setPlayerPos(const Vec2& pos)
	{
		m_playerPos = pos;
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

	int getDamage()
	{
		return 0;
	}

	void draw() const
	{
		
	}

};

/// <summary>
/// Totter, よちよちブロックの上を左右に動く。当たると痛い。
/// </summary>
class EnemyTotter : public Enemy
{

public:

	EnemyTotter(const Vec2& pos)
		: Enemy(pos)
	{

	}

	void update()
	{

	}

	int getDamage()
	{
		return 0;
	}

	void draw() const
	{

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

	int getDamage()
	{
		return 0;
	}

	void draw() const
	{

	}

};
