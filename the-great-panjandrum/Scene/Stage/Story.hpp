#pragma once

#include "../GameData.hpp"
#include "Player.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

/// <summary>
/// �m�[�}���X�e�[�W(�X�g�[���[���[�h)
/// </summary>
class StageStory : public MyApp::Scene
{
private:

	Player m_player;

	StageData m_stage;

	tgpUI::Meter m_tpMeter = tgpUI::Meter({ 315, 20 }, 600, 20);

	const ColorF FadeOutColor = Palette::Black;
	Stopwatch m_swTransition;

public:

	void init() override
	{
		StageEditor::LoadStage(L"Stage/stage_1.csv", m_stage);
		m_player.setBottom(m_stage.deadLine);
		m_player.setPos(m_stage.initPlayerPos);
	}

	void update() override
	{
		// �g�����W�V�������� (�t�F�[�h�A�E�g)
		if (m_swTransition.isActive())
		{
			if (m_swTransition.ms() >= 1000)
			{
				m_swTransition.reset();
				StageData stage;
				StageEditor::LoadStage(m_stage.nextStage, stage);
				m_stage = stage;
				m_player.setBottom(m_stage.deadLine);
				m_player.setPos(m_stage.initPlayerPos);
			}
			return;
		}

		// �u���b�N
		for (size_t i = 0; i < m_stage.blocks.size(); i++)
		{
			m_stage.blocks[i].get()->setPlayerPos(m_player.getPos());
			m_stage.blocks[i].get()->update();
		}

		// �A�C�e��
		for (size_t i = 0; i < m_stage.items.size(); i++)
		{
			m_stage.items[i].get()->setPlayerPos(m_player.getPos());
			m_stage.items[i].get()->update();
		}

		// �G
		for (size_t i = 0; i < m_stage.enemies.size(); i++)
		{
			m_stage.enemies[i].get()->setPlayerPos(m_player.getPos());
			m_stage.enemies[i].get()->update();
		}

		// �v���C���[
		m_player.checkGround(m_stage.blocks);
		m_player.checkItem(m_stage.items);
		m_player.checkEnemy(m_stage.enemies);
		m_player.update();

		if (m_player.checkGoal(m_stage.goalPos))
		{
			if (m_stage.nextStage == L"RESULT")
			{
				changeScene(L"Title");
			}
			else
			{
				m_swTransition.start();
			}
		}

		if (!m_player.isAlive())
		{
			changeScene(L"Title");
		}

		// TP���[�^�[�X�V
		m_tpMeter.setValue(m_player.getTP() / 100.0);

	}

	void draw() const override
	{
		// �w�i
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		// �u���b�N
		for (size_t i = 0; i < m_stage.blocks.size(); i++)
		{
			m_stage.blocks[i].get()->draw(m_data->debugMode);
		}

		// �A�C�e��
		for (size_t i = 0; i < m_stage.items.size(); i++)
		{
			m_stage.items[i].get()->draw();
		}

		// �G
		for (size_t i = 0; i < m_stage.enemies.size(); i++)
		{
			m_stage.enemies[i].get()->draw();
		}

		// �S�[���̊�
		RectF(m_stage.goalPos.movedBy(-m_player.getPos() + Vec2(-50, GameInfo::playerPosOffset - 50) + Window::BaseCenter()), 100, 100)(TextureAsset(L"hata")).draw();

		// �v���C���[
		m_player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			// ���S���胉�C���`��
			const Vec2 p = { m_player.getPos().x, m_stage.deadLine };
			const Vec2 w_half = { Window::BaseWidth() / 2, 0 };
			Line(p.movedBy(-w_half), p.movedBy(w_half)).moveBy(-m_player.getPos() + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

		// TP���[�^�[
		m_tpMeter.draw();

		// �X�e�[�W��
		const int nameWidth = FontAsset(L"UI")(m_stage.stageName).region().w;
		FontAsset(L"UI")(m_stage.stageName).draw({ Window::BaseWidth() - nameWidth - 15, 5 });

		if (m_swTransition.isActive())
		{
			ColorF fadeColor = FadeOutColor;
			Window::ClientRect().draw(fadeColor.setAlpha(m_swTransition.ms() / 1000.0));
		}

	}

};

