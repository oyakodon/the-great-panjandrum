#pragma once

#include "../GameData.hpp"
#include "Block.hpp"

#include <Siv3D.hpp>

class Player
{
private:

	// �v���C���[�̍��W
	Vec2 m_position;

	// �v���C���[�̃e�N�X�`���i�摜�j
	const Texture m_texture;

	// �n�ʂɐڂ��Ă��邩�ۂ�
	bool m_isGrounded;

	// �c��̃W�����v����
	int m_jumpFrame;

	// �Œፂ�x
	int m_bottom;

	// �����Ă��邩�ǂ���
	bool m_isAlive;

public:

	Player() :
		m_position(100, 200),
		m_texture(L"Asset/panjandrum.png"),
		m_isGrounded(false),
		m_jumpFrame(0),
		m_isAlive(true) {}

	// �ʒu���擾����֐�
	Vec2 getPos() const
	{
		return m_position;
	}

	// �n�ʂɐڂ��Ă��邩���X�V����֐�
	void checkGround(const Array<Block>& blocks)
	{
		m_isGrounded = false;

		for (size_t i = 0; i < blocks.size(); i++)
		{
			if (blocks[i].intersects(m_position))
			{
				m_isGrounded = true;
			}
		}
	}

	void setBottom(int value)
	{
		m_bottom = value;
	}

	// �����Ă��邩�ǂ�����Ԃ��֐�
	bool isAlive()
	{
		return m_isAlive;
	}

	// �`��ȊO�̑��������֐�
	void update()
	{
		if (m_isGrounded)
		{
			if (Input::KeySpace.clicked && m_jumpFrame <= 0)
			{
				m_jumpFrame = 30;
			}
		}
		else
		{
			m_position.y += 10.0;
		}

		if (m_jumpFrame > 0)
		{
			m_position.y -= 20.0;
			m_jumpFrame--;
		}
		if (Input::KeyRight.pressed)
		{
			m_position.x += 5.0;
		}
		if (Input::KeyLeft.pressed)
		{
			m_position.x -= 5.0;
		}

		if (m_isAlive && m_position.y >= m_bottom)
		{
			m_isAlive = false;
		}

	}

	// �`�������֐��i�`�摀��ȊO�s��Ȃ�����.�j
	void draw() const
	{
		RectF(Vec2(-100, -200) + Window::BaseCenter(), 200, 200)(m_texture).draw();
	}

};