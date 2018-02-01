#pragma once

#include "../Wiimote/wm4s3d.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  �Q�[���̊�{���
//
namespace GameInfo
{
	// �Q�[���̃^�C�g��
	const String Title = L"The Great Panjandrum";

	// �Q�[���̃o�[�W����
	const String Version = L"Ver. 0.1.7";

	// �Z�[�u�f�[�^�̕ۑ��ꏊ
	const FilePath SaveFilePath = L"save.dat";

	// ���S��ʒ��������ɕ\����������
	const Array<String> Descriptions = {
		L"�v���O���~���O�� �����v���R��2017",
		L"�l�����i",
		L"By Oyakodon"
	};

	// ���S���猩�ăv���C���[�̕`��ʒu���ǂꂭ�炢���炷��(���S��艺�Ȃ�+)
	const int32 playerPosOffset = 100;

}

///////////////////////////////////////////////////////////////////////
//
//  �S�ẴV�[������A�N�Z�X�ł���f�[�^
//
struct GameData
{
	Wii wii[2];
	bool debugMode = false;
};

using MyApp = SceneManager<String, GameData>;

enum class PlayMode
{
	Story,
	Endless,
	VS
};

///////////////////////////////////////////////////////////////////////
//
//  �Z�[�u�p�X�R�A�f�[�^
//
struct ScoreData
{
	int32 score;

	DateTime date;

	PlayMode mode;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(score, date, mode);
	}
};

///////////////////////////////////////////////////////////////////////
//
//  �f�t�H���g�̃n�C�X�R�A
//
const std::array<ScoreData, 5> defaultHighScores
{
	ScoreData{ 50, DateTime(2018,1,1), PlayMode::Story },
	ScoreData{ 40, DateTime(2018,1,1), PlayMode::Story },
	ScoreData{ 30, DateTime(2018,1,1), PlayMode::Story },
	ScoreData{ 20, DateTime(2018,1,1), PlayMode::Endless },
	ScoreData{ 10, DateTime(2018,1,1), PlayMode::VS },
};
