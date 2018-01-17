#pragma once

#include "../GameData.hpp"

#include <Siv3D.hpp>

class Block
{
private:

	// �u���b�N�̗̈�
	RectF m_region;

	// �u���b�N�̃e�L�X�`���i�摜�j
	const Texture m_texture;

	// �v���C���[�̌��݂̈ʒu
	Vec2 m_playerPosition;

public:

	Block() {}

	Block(const RectF& region) :
		m_region(region),
		m_texture(L"Example/Brick.jpg") {}

	// �v���C���[�̌��݈ʒu���X�V����֐�
	void setPlayerPos(const Vec2& pos)
	{
		m_playerPosition = pos;
	}

	// �`��ȊO�̑��������֐�
	void update() {}

	// �_�Ƃ̓����蔻������֐�
	bool intersects(const Vec2 &shape) const
	{
		return m_region.intersects(shape);
	}

	// �`�������֐��i�`�摀��ȊO�s��Ȃ�����.�j
	void draw() const
	{
		m_region.movedBy(-m_playerPosition + Window::BaseCenter())(m_texture).draw();
	}

};