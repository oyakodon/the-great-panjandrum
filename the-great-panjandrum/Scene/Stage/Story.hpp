#pragma once

#include "../GameData.hpp"
#include "Player.hpp"
#include "Stage.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

/// <summary>
/// ノーマルステージ(ストーリーモード)
/// </summary>
class StageStory : public MyApp::Scene
{
private:

	Player m_player;

	StageData m_stage;

	// プレー時間
	Stopwatch m_sw;

	tgpUI::Meter m_tpMeter = tgpUI::Meter({ 315, 20 }, 600, 20);

	const ColorF FadeOutColor = Palette::Black;
	Stopwatch m_swTransition;

public:

	void init() override
	{
		StageData::LoadStage(L"Stage/stage_1.csv", m_stage);
		m_player.setBottom(m_stage.deadLine);
		m_player.setPos(m_stage.initPlayerPos);

		m_sw.start();
	}

	void update() override
	{
		if (Input::KeyEscape.pressedDuration >= 3000)
		{
			changeScene(L"Title");
		}

		// トランジション処理 (フェードアウト)
		if (m_swTransition.isActive())
		{
			if (m_swTransition.ms() >= 1000)
			{
				m_swTransition.reset();
				StageData stage;
				StageData::LoadStage(m_stage.nextStage, stage);
				m_stage = stage;
				m_player.setBottom(m_stage.deadLine);
				m_player.setPos(m_stage.initPlayerPos);

				SoundAsset(L"decision4").playMulti();
				m_sw.start();
			}
			return;
		}

		// ブロック
		for (size_t i = 0; i < m_stage.blocks.size(); i++)
		{
			m_stage.blocks[i].get()->setPlayerPos(m_player.getPos());
			m_stage.blocks[i].get()->update();
		}

		// アイテム
		for (size_t i = 0; i < m_stage.items.size(); i++)
		{
			m_stage.items[i].get()->setPlayerPos(m_player.getPos());
			m_stage.items[i].get()->update();
		}

		// 敵
		for (size_t i = 0; i < m_stage.enemies.size(); i++)
		{
			m_stage.enemies[i].get()->setPlayerPos(m_player.getPos());
			m_stage.enemies[i].get()->update();
		}

		// プレイヤー
		m_player.checkGround(m_stage.blocks);
		m_player.checkItem(m_stage.items);
		m_player.checkEnemy(m_stage.enemies);
		m_player.update(m_data->wii[0]);

		if (m_player.checkGoal(m_stage.goalPos))
		{
			m_sw.pause();

			if (m_stage.nextStage == L"RESULT")
			{
				m_data->lastMode = PlayMode::Story;
				m_data->lastClearTime = m_sw.elapsed().count();
				m_data->lastStageFailed = false;
				changeScene(L"Result");
			}
			else
			{
				m_swTransition.start();
			}
		}

		if (!m_player.isAlive())
		{
			// 最初に戻る
			if (m_player.getTP() < 0)
			{
				m_data->lastMode = PlayMode::Story;
				m_data->lastClearTime = m_sw.elapsed().count();
				m_data->lastStageFailed = true;
				changeScene(L"Result");
			}

			m_stage.nextStage = L"Stage/stage_1.csv";
			m_swTransition.start();
		}

		// TPメーター更新
		m_tpMeter.setValue(m_player.getTP() / Player::TPMAX);

	}

	void draw() const override
	{
		// 背景
		Window::BaseClientRect()(TextureAsset(L"bg_natural_umi")).draw(ColorF(0.5));

		// ブロック
		for (size_t i = 0; i < m_stage.blocks.size(); i++)
		{
			m_stage.blocks[i].get()->draw(m_data->debugMode);
		}

		// アイテム
		for (size_t i = 0; i < m_stage.items.size(); i++)
		{
			m_stage.items[i].get()->draw();
		}

		// 敵
		for (size_t i = 0; i < m_stage.enemies.size(); i++)
		{
			m_stage.enemies[i].get()->draw();
		}

		// ゴールの旗
		RectF(m_stage.goalPos.movedBy(-m_player.getPos() + Vec2(-50, GameInfo::playerPosOffset - 50) + Window::BaseCenter()), 100, 100)(TextureAsset(L"hata")).draw();

		// プレイヤー
		m_player.draw(m_data->debugMode);

		if (m_data->debugMode)
		{
			// 死亡判定ライン描画
			const Vec2 p = { m_player.getPos().x, m_stage.deadLine };
			const Vec2 w_half = { Window::BaseWidth() / 2, 0 };
			Line(p.movedBy(-w_half), p.movedBy(w_half)).moveBy(-m_player.getPos() + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).draw(2.0, Palette::Orange);
		}

		// TPメーター
		m_tpMeter.draw();

		// ステージ名
		const int nameWidth = FontAsset(L"UI")(m_stage.stageName).region().w;
		FontAsset(L"UI")(m_stage.stageName).draw({ Window::BaseWidth() - nameWidth - 15, 5 });

		// 累計獲得TP
		const int earnedTPWidth = FontAsset(L"UI")(L"獲得TP:", m_player.getEarnedTP()).region().w;
		FontAsset(L"UI")(L"獲得TP:", m_player.getEarnedTP()).draw({ Window::BaseWidth() - earnedTPWidth - 15, 35 });

		// プレー時間
		const int swWidth = FontAsset(L"UI_Large")(L"00:00:000").region().w;
		FontAsset(L"UI_Large")(
			Pad(m_sw.min(),		{ 2, L'0' }), L":",
			Pad(m_sw.s() % 60,	{ 2, L'0' }), L":",
			Pad(m_sw.ms() % 1000,{ 2, L'0' })
		).draw({ Window::BaseCenter().x - swWidth / 2, 30 });
		
		// フェードアウト
		if (m_swTransition.isActive())
		{
			ColorF fadeColor = FadeOutColor;
			Window::ClientRect().draw(fadeColor.setAlpha(m_swTransition.ms() / 1000.0));
		}

	}

};

