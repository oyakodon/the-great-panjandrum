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
	static void LoadStage(const String& filepath, StageData& stage)
	{
		const CSVReader csv(filepath);

		if (!csv)
		{
			throw "Cannot load csv file!";
		}

		// 最下点, y反対なので注意
		double lowest = 0;

		for (auto i : step(csv.rows))
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
					stage.blocks.push_back(std::shared_ptr<Block>(new NormalBlock({x, y, w, h})));

					// 最下点更新
					lowest = Max(y + h, lowest);

					std::cout << "Created block. Type: Block, x:" << x << ", y:" << y << ", w:" << w << ", h:" << h << std::endl;

				}
				else if (btype == L"MOVINGBLOCK")
				{
					// 移動ブロック
					stage.blocks.push_back(std::shared_ptr<Block>(new MovingBlock({x, y, w, h})));

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
					stage.items.push_back(std::shared_ptr<Item>( new Item(pos, ItemType::Tea) ));
				}
				else if (csv.get<String>(i, 1) == L"MARMITE")
				{
					stage.items.push_back(std::shared_ptr<Item>(new Item(pos, ItemType::Marmite) ));
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
					stage.enemies.push_back(std::shared_ptr<Enemy>( new EnemyBunchin(pos) ));
				}
				else if (csv.get<String>(i, 1) == L"YOTIYOTI")
				{
					const int range = csv.get<int>(i, 4);
					stage.enemies.push_back(std::shared_ptr<Enemy>(new EnemyYotiyoti(pos, range) ));
				}
				else if (csv.get<String>(i, 1) == L"DANMAKU")
				{
					stage.enemies.push_back(std::shared_ptr<Enemy>(new EnemyDanmaku(pos) ));
				}
			}
			else if (cmd == L"SETNAME")
			{
				stage.stageName = csv.get<String>(i, 1);
			}
		}

		stage.deadLine = lowest + StageData::DEADLINE_MARGIN;

	}

};
