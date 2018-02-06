#pragma once

#include "../GameData.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

/// <summary>
/// �X�e�[�W���
/// </summary>
struct StageData
{
	/// <summary>
	/// �X�e�[�W��
	/// </summary>
	String stageName;

	/// <summary>
	/// �u���b�N
	/// </summary>
	Array<std::shared_ptr<Block>> blocks;

	/// <summary>
	/// �A�C�e��
	/// </summary>
	Array<std::shared_ptr<Item>> items;
	
	/// <summary>
	/// �G
	/// </summary>
	Array<std::shared_ptr<Enemy>> enemies;

	/// <summary>
	/// �v���C���[�̏����ʒu
	/// </summary>
	Vec2 initPlayerPos;

	/// <summary>
	/// �S�[���n�_
	/// </summary>
	Vec2 goalPos;

	/// <summary>
	/// ���̃X�e�[�W��CSV�t�@�C���p�X
	/// </summary>
	String nextStage;

	/// <summary>
	/// ���S���胉�C��
	/// </summary>
	double deadLine;

	static constexpr double DEADLINE_MARGIN = 200;

};

/// <summary>
/// �X�e�[�W�G�f�B�^�[
/// </summary>
class StageEditor
{
private:

public:

	/// <summary>
	/// CSV�t�@�C������X�e�[�W����ǂݍ��݂܂��B
	/// </summary>
	/// <param name="filepath">CSV�t�@�C���ւ̃p�X</param>
	/// <param name="stage">�X�e�[�W�f�[�^</param>
	static void LoadStage(const String& filepath, StageData& stage)
	{
		const CSVReader csv(filepath);

		if (!csv)
		{
			throw "Cannot load csv file!";
		}

		// �ŉ��_, y���΂Ȃ̂Œ���
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
					// �ʏ�u���b�N
					stage.blocks.push_back(std::shared_ptr<Block>(new NormalBlock({x, y, w, h})));

					// �ŉ��_�X�V
					lowest = Max(y + h, lowest);

					std::cout << "Created block. Type: Block, x:" << x << ", y:" << y << ", w:" << w << ", h:" << h << std::endl;

				}
				else if (btype == L"MOVINGBLOCK")
				{
					// �ړ��u���b�N
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
