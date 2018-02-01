#pragma once

#include <Siv3D.hpp>

/// <summary>
/// �G�̎��
/// </summary>
enum class EnemyType
{
	Immovable,
	Totter,
	Barrage
};

/// <summary>
/// �G
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
/// Immovable, �����Ȃ����Ǔ�����ƒɂ�
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
/// Totter, �悿�悿�u���b�N�̏�����E�ɓ����B������ƒɂ��B
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
/// Barrage, ��ɕ����тȂ���e��ł��Ă���B�e�����Ăقǂł��Ȃ��B
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
