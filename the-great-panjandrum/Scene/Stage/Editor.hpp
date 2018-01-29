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
class StageData
{
public:

	Array<Block> blocks;
	Array<Item> items;
	Array<Enemy> enemies;
	Vec2 initPlayerPos;
	Vec2 goalPos;

};


/// <summary>
/// ステージエディター
/// </summary>
class StageEditor
{
private:

public:

	/// <summary>
	/// CSVファイルからステージ情報を読み込みます。
	/// </summary>
	/// <param name="filepath">CSVファイルへのパス</param>
	/// <param name="stage">ステージデータ</param>
	static void LoadStage(const String& filepath, StageData stage)
	{
		const CSVReader csv(filepath);

		if (!csv)
		{
			throw "Cannot load csv file!";
		}

		for (auto i : step(csv.rows))
		{			
			const String cmd = csv.get<String>(i, 0);

			if (cmd == L"CREATEBLOCK")
			{
				const String btype = csv.get<String>(i, 1);
				if (btype == L"BLOCK")
				{
					// 通常ブロック
					stage.blocks.emplace_back(NormalBlock({
						csv.get<double>(i, 2),
						csv.get<double>(i, 3),
						csv.get<double>(i, 4),
						csv.get<double>(i, 5)
					}));
				}
				else if (btype == L"MOVINGBLOCK")
				{
					// 移動ブロック
					stage.blocks.emplace_back(MovingBlock({
						csv.get<double>(i, 2),
						csv.get<double>(i, 3),
						csv.get<double>(i, 4),
						csv.get<double>(i, 5)
					}));
				}

			}
			else if (cmd == L"SETPOS")
			{
				stage.initPlayerPos = { csv.get<int32>(i, 1), csv.get<int32>(i, 2) };
			}
			else if (cmd == L"SETGOAL")
			{
				stage.goalPos = { csv.get<int32>(i, 1), csv.get<int32>(i, 2) };
			}
			else if (cmd == L"CREATEITEM")
			{
				const Vec2 pos = {
					csv.get<int32>(i, 2),
					csv.get<int32>(i, 3)
				};

				if (csv.get<String>(i, 1) == L"TEA")
				{
					Item item = Item(pos, ItemType::Tea);
					// stage.items.push_back(item);
				}
				else if (csv.get<String>(i, 1) == L"MARMITE")
				{
					Item item = Item(pos, ItemType::Marmite);
					// stage.items.push_back(item);
				}

			}
			else if (cmd == L"CREATEENEMY")
			{
				const Vec2 pos = { csv.get<int32>(i, 2), csv.get<int32>(i, 3) };

				if (csv.get<String>(i, 1) == L"IMMOVABLE")
				{
					stage.enemies.emplace_back(EnemyImmovable(pos));
				}
				else if (csv.get<String>(i, 1) == L"TOTTER")
				{
					stage.enemies.emplace_back(EnemyTotter(pos));
				}
				else if (csv.get<String>(i, 1) == L"BARRAGE")
				{
					stage.enemies.emplace_back(EnemyBarrage(pos));
				}

			}

		}


	}

};
