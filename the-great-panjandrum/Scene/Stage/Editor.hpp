#pragma once

#include "../GameData.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Stage.hpp" 

#include <Siv3D.hpp>
#include <HamFramework.hpp>

enum class EntityCategory
{
	Block,
	Item,
	Enemy
};

enum class EntityType : int
{
	NormalBlock = 0,
	MovingBlock,
	Tea,
	Marmite,
	EnemyBunchin,
	EnemyYotiyoti,
	EnemyDanmaku
};

/// <summary>
/// ステージエディター
/// </summary>
class StageEditor : public MyApp::Scene
{
private:

	StageData m_stage;

	Vec2 m_sightPos;

	bool m_dragging = false;
	int m_draggingItem = 0;
	EntityCategory m_draggingType;

	bool m_createMode = false;
	int m_createType;

	GUI gui;
	GUI gui_stage_prop;

	std::map<EntityType, String> m_entityTypeNames;

public:

	void init() override
	{
		m_sightPos = { 0, 0 };

		// Inititalize m_entityTypeNames
		m_entityTypeNames[EntityType::NormalBlock] = L"ブロック(通常)";
		m_entityTypeNames[EntityType::MovingBlock] = L"ブロック(移動)";
		m_entityTypeNames[EntityType::Tea] = L"アイテム(紅茶)";
		m_entityTypeNames[EntityType::Marmite] = L"アイテム(マーマイト)";
		m_entityTypeNames[EntityType::EnemyBunchin] = L"敵(Bunchin)";
		m_entityTypeNames[EntityType::EnemyYotiyoti] = L"敵(Yotiyoti)";
		m_entityTypeNames[EntityType::EnemyDanmaku] = L"敵(Danamku)";

		// Create GUI
		gui_stage_prop = GUI(GUIStyle::Default);
		gui.setTitle(L"ステージ");

		gui_stage_prop.add(L"bt_open", GUIButton::Create(L"開く"));
		gui_stage_prop.addln(L"bt_save", GUIButton::Create(L"保存"));

		gui_stage_prop.add(GUIText::Create(L"Name: "));
		gui_stage_prop.addln(L"tf_name", GUITextField::Create(none));
		gui_stage_prop.textField(L"tf_name").setText(L"ステージ");

		gui_stage_prop.add(GUIText::Create(L"初期位置 X: "));
		gui_stage_prop.add(L"tf_init_x", GUITextField::Create(none));
		gui_stage_prop.textField(L"tf_init_x").setText(L"0");
		gui_stage_prop.add(GUIText::Create(L"Y: "));
		gui_stage_prop.addln(L"tf_init_y", GUITextField::Create(none));
		gui_stage_prop.textField(L"tf_init_y").setText(L"0");

		gui_stage_prop.add(GUIText::Create(L"ゴール X: "));
		gui_stage_prop.add(L"tf_goal_x", GUITextField::Create(none));
		gui_stage_prop.textField(L"tf_goal_x").setText(L"200");
		gui_stage_prop.add(GUIText::Create(L"Y: "));
		gui_stage_prop.addln(L"tf_goal_y", GUITextField::Create(none));
		gui_stage_prop.textField(L"tf_goal_y").setText(L"200");

		gui = GUI(GUIStyle::Default);
		gui.setTitle(L"プロパティ");

		gui.add(L"bt_select", GUIButton::Create(L"選択"));
		gui.add(L"bt_create", GUIButton::Create(L"追加"));
		gui.addln(L"bt_delete", GUIButton::Create(L"削除"));
		
		gui.add(L"bt_prev", GUIButton::Create(L"<"));
		gui.add(L"tf_type", GUITextField::Create(none));
		gui.textField(L"tf_type").setText(m_entityTypeNames[EntityType::NormalBlock]);
		gui.addln(L"bt_next", GUIButton::Create(L">"));

		gui.add(GUIText::Create(L"W: "));
		gui.add(L"tf_w", GUITextField::Create(none));
		gui.textField(L"tf_w").setText(L"200");
		gui.add(GUIText::Create(L"H: "));
		gui.addln(L"tf_h", GUITextField::Create(none));
		gui.textField(L"tf_h").setText(L"200");

		gui.add(GUIText::Create(L"V/H: "));
		gui.add(L"tf_vh", GUITextField::Create(none));
		gui.textField(L"tf_vh").setText(L"V");
		gui.add(GUIText::Create(L"Range: "));
		gui.add(L"tf_range", GUITextField::Create(none));
		gui.textField(L"tf_range").setText(L"500");
		gui.add(GUIText::Create(L"Speed: "));
		gui.addln(L"tf_speed", GUITextField::Create(none));
		gui.textField(L"tf_speed").setText(L"3");

		gui.setPos(Window::BaseWidth() - gui.getRect().w, Window::BaseHeight() - gui.getRect().h);

	}

	void update() override
	{
		bool guiMouseOver = gui.getRect().intersects(Mouse::PosF()) | gui_stage_prop.getRect().intersects(Mouse::PosF());

		{
			const Transformer2D transformer(Mat3x2::Scale(0.75, Window::Center() + Vec2(0, -250)), true);

			// ブロック
			for (size_t i = 0; i < m_stage.blocks.size(); i++)
			{
				m_stage.blocks[i].get()->setPlayerPos(m_sightPos);
				if (!m_createMode && !m_dragging && Input::MouseL.pressed && m_stage.blocks[i]->getRect().movedBy(-m_sightPos + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).intersects(Mouse::PosF()))
				{
					m_dragging = true;
					m_draggingItem = i;
					m_draggingType = EntityCategory::Block;
				}
			}

			// アイテム
			for (size_t i = 0; i < m_stage.items.size(); i++)
			{
				m_stage.items[i].get()->setPlayerPos(m_sightPos);
				if (!m_createMode && !m_dragging && Input::MouseL.pressed && m_stage.items[i]->getRect().movedBy(-m_sightPos + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).intersects(Mouse::PosF()))
				{
					m_dragging = true;
					m_draggingItem = i;
					m_draggingType = EntityCategory::Item;
				}
			}

			// 敵
			for (size_t i = 0; i < m_stage.enemies.size(); i++)
			{
				m_stage.enemies[i].get()->setPlayerPos(m_sightPos);
				if (!m_createMode && !m_dragging && Input::MouseL.pressed && m_stage.enemies[i]->getRect().movedBy(-m_sightPos + Vec2(0, GameInfo::playerPosOffset) + Window::BaseCenter()).intersects(Mouse::PosF()))
				{
					m_dragging = true;
					m_draggingItem = i;
					m_draggingType = EntityCategory::Enemy;
				}
			}

			if (m_createMode && Input::MouseL.clicked && !guiMouseOver)
			{
				switch (static_cast<EntityType>(m_createType))
				{
					case EntityType::NormalBlock:
						m_stage.blocks.emplace_back(std::shared_ptr<Block>(new NormalBlock({ Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter()), FromString<double>(gui.textField(L"tf_w").text), FromString<double>(gui.textField(L"tf_h").text) }))); break;
					case EntityType::MovingBlock:
						m_stage.blocks.emplace_back(std::shared_ptr<Block>(new MovingBlock({ Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter()), FromString<double>(gui.textField(L"tf_w").text), FromString<double>(gui.textField(L"tf_h").text) }, gui.textField(L"tf_vh").text == L"V" ? MoveType::Vertical : MoveType::Horizontal, FromString<int>(gui.textField(L"tf_range").text), FromString<int>(gui.textField(L"tf_speed").text)))); break;
					case EntityType::Tea:
						m_stage.items.emplace_back(std::shared_ptr<Item>(new Item(Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter()), ItemType::Tea))); break;
					case EntityType::Marmite:
						m_stage.items.emplace_back(std::shared_ptr<Item>(new Item(Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter()), ItemType::Marmite))); break;
					case EntityType::EnemyBunchin:
						m_stage.enemies.emplace_back(std::shared_ptr<Enemy>(new EnemyBunchin(Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter())))); break;
					case EntityType::EnemyYotiyoti:
						m_stage.enemies.emplace_back(std::shared_ptr<Enemy>(new EnemyYotiyoti(Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter()), FromString<int>(gui.textField(L"tf_range").text)))); break;
					case EntityType::EnemyDanmaku:
						m_stage.enemies.emplace_back(std::shared_ptr<Enemy>(new EnemyDanmaku(Mouse::PosF().movedBy(m_sightPos + Vec2(0, -GameInfo::playerPosOffset) - Window::BaseCenter())))); break;
					default: break;
				}
				m_createMode = false;
			}

		}

		if (!m_createMode && m_dragging && Input::MouseL.pressed)
		{
			switch (m_draggingType)
			{
				case EntityCategory::Block:m_stage.blocks[m_draggingItem].get()->setRect(m_stage.blocks[m_draggingItem].get()->getRect().movedBy(Mouse::DeltaF())); break;
				case EntityCategory::Item: m_stage.items[m_draggingItem].get()->setRect(m_stage.items[m_draggingItem].get()->getRect().movedBy(Mouse::DeltaF())); break;
				case EntityCategory::Enemy: m_stage.enemies[m_draggingItem].get()->setRect(m_stage.enemies[m_draggingItem].get()->getRect().movedBy(Mouse::DeltaF())); break;
				default: break;
			}
		}

		if (!m_createMode && m_dragging && Input::MouseL.released)
		{
			m_dragging = false;
		}

		if (Input::KeyEscape.clicked)
		{
			changeScene(L"Setting");
		}

		if (Input::KeyRight.pressed)
		{
			m_sightPos.x += 10;
		}

		if (Input::KeyLeft.pressed)
		{
			m_sightPos.x -= 10;
		}

		if (Input::KeyUp.pressed)
		{
			m_sightPos.y -= 10;
		}

		if (Input::KeyDown.pressed)
		{
			m_sightPos.y += 10;
		}

		m_sightPos.x += Mouse::Wheel() * 100;

		if (Input::MouseR.clicked)
		{
			m_createMode = !m_createMode;
		}

		if (gui.button(L"bt_select").pushed)
		{
			m_createMode = false;
		}

		if (gui.button(L"bt_create").pushed)
		{
			m_createMode = true;
		}

		if (gui.button(L"bt_delete").pushed)
		{
			switch (m_draggingType)
			{
				case EntityCategory::Block:
				{
					auto it = m_stage.blocks.begin();
					int i = 0;
					while (it != m_stage.blocks.end())
					{
						if (i == m_draggingItem)
						{
							m_stage.blocks.erase(it);
							break;
						}
						it++;
						i++;
					}
					m_draggingItem = 0;
				}
				break;
				case EntityCategory::Item:
				{
					auto it = m_stage.items.begin();
					int i = 0;
					while (it != m_stage.items.end())
					{
						if (i == m_draggingItem)
						{
							m_stage.items.erase(it);
							break;
						}
						it++;
						i++;
					}
					m_draggingItem = 0;
				}
				break;
				case EntityCategory::Enemy:
				{
					auto it = m_stage.enemies.begin();
					int i = 0;
					while (it != m_stage.enemies.end())
					{
						if (i == m_draggingItem)
						{
							m_stage.enemies.erase(it);
							break;
						}
						it++;
						i++;
					}
					m_draggingItem = 0;
				}
				break;
				default: break;
			}
			MessageBox::Show(L"削除しました。");

		}

		if (gui_stage_prop.textField(L"tf_init_x").hasChanged)
		{
			m_stage.initPlayerPos.x = FromString<int>(gui_stage_prop.textField(L"tf_init_x").text);
		}

		if (gui_stage_prop.textField(L"tf_init_y").hasChanged)
		{
			m_stage.initPlayerPos.y = FromString<int>(gui_stage_prop.textField(L"tf_init_y").text);
		}

		if (gui_stage_prop.textField(L"tf_goal_x").hasChanged)
		{
			m_stage.goalPos.x = FromString<int>(gui_stage_prop.textField(L"tf_goal_x").text);
		}

		if (gui_stage_prop.textField(L"tf_goal_y").hasChanged)
		{
			m_stage.goalPos.y = FromString<int>(gui_stage_prop.textField(L"tf_goal_y").text);
		}

		if (gui.button(L"bt_prev").pushed)
		{
			m_createMode = true;
			m_createType = Max(0, m_createType - 1);
			gui.textField(L"tf_type").setText(m_entityTypeNames[static_cast<EntityType>(m_createType)]);
		}

		if (gui.button(L"bt_next").pushed)
		{
			m_createMode = true;
			m_createType = Min(6, m_createType + 1);
			gui.textField(L"tf_type").setText(m_entityTypeNames[static_cast<EntityType>(m_createType)]);
		}

		if (gui_stage_prop.button(L"bt_save").pushed)
		{
			// 保存
			Optional<String> filePath = Dialog::GetSave({ ExtensionFilter::CSV });
			if (filePath.has_value())
			{
				m_stage.stageName = gui_stage_prop.textField(L"tf_name").text;
				m_stage.initPlayerPos = { FromString<int>(gui_stage_prop.textField(L"tf_init_x").text), FromString<int>(gui_stage_prop.textField(L"tf_init_y").text) };
				m_stage.goalPos = { FromString<int>(gui_stage_prop.textField(L"tf_goal_x").text), FromString<int>(gui_stage_prop.textField(L"tf_goal_y").text) };
				
				StageData::SaveStage(filePath.value(), m_stage);
				MessageBox::Show(L"\"" + filePath.value() + L"\"にステージデータを保存しました。");
			}
			else
			{
				MessageBox::Show(L"ステージデータの保存がキャンセルされました。");
			}
		}

		if (gui_stage_prop.button(L"bt_open").pushed)
		{
			// 開く
			Optional<String> filePath = Dialog::GetOpen({ ExtensionFilter::CSV });
			if (filePath.has_value())
			{
				StageData::LoadStage(filePath.value(), m_stage);

				gui_stage_prop.textField(L"tf_name").setText(m_stage.stageName);
				gui_stage_prop.textField(L"tf_init_x").setText(ToString(m_stage.initPlayerPos.x));
				gui_stage_prop.textField(L"tf_init_y").setText(ToString(m_stage.initPlayerPos.y));
				gui_stage_prop.textField(L"tf_goal_x").setText(ToString(m_stage.goalPos.x));
				gui_stage_prop.textField(L"tf_goal_y").setText(ToString(m_stage.goalPos.y));
			}
			else
			{
				MessageBox::Show(L"ステージデータの読込がキャンセルされました。");
			}

		}

	}

	void draw() const override
	{
		{
			const Transformer2D transformer(Mat3x2::Scale(0.75, Window::Center() + Vec2(0, -250)), true);

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
			RectF(m_stage.goalPos.movedBy(-m_sightPos + Vec2(-50, GameInfo::playerPosOffset - 50) + Window::BaseCenter()), 100, 100)(TextureAsset(L"hata")).draw();

			// プレイヤー
			RectF(m_stage.initPlayerPos.movedBy(-m_sightPos + Vec2(-100, GameInfo::playerPosOffset - 200) + Window::BaseCenter()), 200, 200)(TextureAsset(L"panjandrum")).draw();
			RectF(m_stage.initPlayerPos.movedBy(-m_sightPos + Vec2(-50, GameInfo::playerPosOffset - 380) + Window::BaseCenter()), 100, 250)(TextureAsset(L"akane01")).draw();

		}

		RectF(0, 595, Window::BaseWidth(), 125).draw(Palette::Green);

		FontAsset(L"UI_Large")(m_createMode ? L"追加モード" : L"選択モード").draw();

	}

};
