#pragma once

#include "../GameData.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

/// <summary>
/// ステージ情報
/// </summary>
struct StageData
{
	/// <summary>
	/// ステージ名
	/// </summary>
	String stageName;

	/// <summary>
	/// ブロック
	/// </summary>
	Array<std::shared_ptr<Block>> blocks;

	/// <summary>
	/// アイテム
	/// </summary>
	Array<std::shared_ptr<Item>> items;

	/// <summary>
	/// 敵
	/// </summary>
	Array<std::shared_ptr<Enemy>> enemies;

	/// <summary>
	/// プレイヤーの初期位置
	/// </summary>
	Vec2 initPlayerPos;

	/// <summary>
	/// ゴール地点
	/// </summary>
	Vec2 goalPos;

	/// <summary>
	/// 次のステージのCSVファイルパス
	/// </summary>
	String nextStage;

	/// <summary>
	/// 死亡判定ライン
	/// </summary>
	double deadLine;

	static constexpr double DEADLINE_MARGIN = 200;

	/// <summary>
	/// CSVファイルからステージ情報を読み込みます。
	/// </summary>
	/// <param name="filepath">CSVファイルへのパス</param>
	/// <param name="stage">ステージデータ</param>
	static void LoadStage(const String& filepath, StageData& stage)
	{
		const CSVReader csv(filepath);

		if (!csv)
		{
			throw "Cannot load csv file!";
		}

		// 最下点, y反対なので注意
		double lowest = 0;

		for (const auto i : step(csv.rows))
		{
			const String cmd = csv.get<String>(i, 0);

			if (cmd == L"CREATEBLOCK")
			{
				const String btype = csv.get<String>(i, 1);
				const double x = csv.get<double>(i, 2);
				const double y = csv.get<double>(i, 3);
				const double w = csv.get<double>(i, 4);
				const double h = csv.get<double>(i, 5);

				if (btype == L"BLOCK")
				{
					// 通常ブロック
					stage.blocks.push_back(std::shared_ptr<Block>(new NormalBlock({ x, y, w, h })));

					// 最下点更新
					lowest = Max(y + h, lowest);

					std::cout << "Created block. Type: Block, x:" << x << ", y:" << y << ", w:" << w << ", h:" << h << std::endl;

				}
				else if (btype == L"MOVINGBLOCK")
				{
					// 移動ブロック
					MoveType mt = MoveType::Vertical;
					if (csv.get<String>(i, 6) == L"H")
					{
						mt = MoveType::Horizontal;
					}
					stage.blocks.push_back(std::shared_ptr<Block>(new MovingBlock({ x, y, w, h }, mt, csv.get<int>(i, 7), csv.get<int>(i, 8))));

					std::cout << "Created block. Type: MovingBlock, x:" << x << ", y:" << y << ", w:" << w << ", h:" << h << std::endl;
				}

			}
			else if (cmd == L"SETPOS")
			{
				stage.initPlayerPos = { csv.get<int32>(i, 1), csv.get<int32>(i, 2) };
			}
			else if (cmd == L"SETGOAL")
			{
				stage.goalPos = { csv.get<int32>(i, 1), csv.get<int32>(i, 2) };
				stage.nextStage = csv.get<String>(i, 3);
			}
			else if (cmd == L"CREATEITEM")
			{
				const Vec2 pos = {
					csv.get<double>(i, 2),
					csv.get<double>(i, 3)
				};

				if (csv.get<String>(i, 1) == L"TEA")
				{
					stage.items.push_back(std::shared_ptr<Item>(new Item(pos, ItemType::Tea)));
				}
				else if (csv.get<String>(i, 1) == L"MARMITE")
				{
					stage.items.push_back(std::shared_ptr<Item>(new Item(pos, ItemType::Marmite)));
				}

			}
			else if (cmd == L"CREATEENEMY")
			{
				const Vec2 pos = {
					csv.get<double>(i, 2),
					csv.get<double>(i, 3)
				};

				if (csv.get<String>(i, 1) == L"BUNCHIN")
				{
					stage.enemies.push_back(std::shared_ptr<Enemy>(new EnemyBunchin(pos)));
				}
				else if (csv.get<String>(i, 1) == L"YOTIYOTI")
				{
					const int range = csv.get<int>(i, 4);
					stage.enemies.push_back(std::shared_ptr<Enemy>(new EnemyYotiyoti(pos, range)));
				}
				else if (csv.get<String>(i, 1) == L"DANMAKU")
				{
					stage.enemies.push_back(std::shared_ptr<Enemy>(new EnemyDanmaku(pos)));
				}
			}
			else if (cmd == L"SETNAME")
			{
				stage.stageName = csv.get<String>(i, 1);
			}
		}

		stage.deadLine = lowest + StageData::DEADLINE_MARGIN;

	}

	/// <summary>
	/// CSVファイルにステージ情報を書き込みます。
	/// </summary>
	/// <param name="filepath">CSVファイルへのパス</param>
	/// <param name="stage">ステージデータ</param>
	static void SaveStage(const String& filepath, StageData& stage)
	{
		CSVWriter csv(filepath);

		if (!csv)
		{
			throw "Cannot load csv file!";
		}

		csv.writeRow(L"SETPOS", (int32)stage.initPlayerPos.x, (int32)stage.initPlayerPos.y);

		csv.writeRow(L"SETGOAL", (int32)stage.goalPos.x, (int32)stage.goalPos.y, stage.nextStage);

		csv.writeRow(L"SETNAME", stage.stageName);

		for (const auto& block : stage.blocks)
		{
			if (block->getType() == BlockType::Normal)
			{
				csv.writeRow(L"CREATEBLOCK", L"BLOCK", block->getRect().x, block->getRect().y, block->getRect().w, block->getRect().h);
			}
			else
			{
				csv.writeRow(L"CREATEBLOCK", L"MOVINGBLOCK", block->getRect().x, block->getRect().y, block->getRect().w, block->getRect().h, ((MovingBlock *)block.get())->getMoveType() == MoveType::Horizontal ? L"H" : L"V", ((MovingBlock *)block.get())->getRange(), ((MovingBlock *)block.get())->getSpeed());
			}
		}

		for (const auto& item : stage.items)
		{
			csv.writeRow(L"CREATEITEM", item->getType() == ItemType::Tea ? L"TEA" : L"MARMITE", item->getRect().center.x, item->getRect().center.y);
		}

		for (const auto& enemy : stage.enemies)
		{
			String eType = L"BUNCHIN";

			if (enemy->getType() == EnemyType::Yotiyoti)
			{
				eType = L"YOTIYOTI";
			}
			else if (enemy->getType() == EnemyType::Danmaku)
			{
				eType = L"DANMAKU";
			}

			if (eType == L"YOTIYOTI")
			{
				csv.writeRow(L"CREATEENEMY", eType, enemy->getRect().center.x, enemy->getRect().center.y, ((EnemyYotiyoti *)enemy.get())->getRange());
			}
			else
			{
				csv.writeRow(L"CREATEENEMY", eType, enemy->getRect().center.x, enemy->getRect().center.y);
			}
		}
	}

};
