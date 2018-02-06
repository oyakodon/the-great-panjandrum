#pragma once

#include <Siv3D.hpp>

/// <summary>
/// �G�̎�ށ@(�Փ˂������̃_���[�W)
/// </summary>
enum class EnemyType : int
{
	Bunchin = 10,
	Yotiyoti = 15,
	Danmaku = 20
};

/// <summary>
/// �G
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
/// Bunchin, �����Ȃ����Ǔ�����ƒɂ�
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
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);
	}

};

/// <summary>
/// Yotiyoti, �悿�悿�u���b�N�̏�����E�ɓ����B������ƒɂ��B
/// </summary>
class EnemyYotiyoti : public Enemy
{
private:

	const int m_range; // +/- �ǂ̂��炢�ړ����邩 (���W)

	const int m_speed = 3; // �ړ����x

	int m_relative; // ���΍��W
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
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);
	}

};

/// <summary>
/// Danmaku, ��ɕ����тȂ���e��ł��Ă���B�e�����Ăقǂł��Ȃ��B
/// </summary>
class EnemyDanmaku : public Enemy
{

public:

	EnemyDanmaku(const Vec2& pos)
		: Enemy(pos)
	{

	}

	void update()
	{

	}

	int getDamage(bool intersects)
	{
		return intersects ? static_cast<int>(EnemyType::Danmaku) : 0;
	}

	void draw() const
	{
		m_region.movedBy(-m_playerPos + Window::BaseCenter() + Vec2(0, GameInfo::playerPosOffset)).draw(Palette::Yellow).drawFrame(1.0, 0.0, Palette::Red);
	}

};
