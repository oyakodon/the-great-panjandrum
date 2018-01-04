#pragma once

#include "../wm4s3d.hpp"

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

	// �Q�[���̃o�[�W�����i��̕������ OK�j
	const String Version = L"ver. 0.1.002";

	// �Z�[�u�f�[�^�̕ۑ��ꏊ
	const FilePath SaveFilePath = L"Save/Score.dat";

}

///////////////////////////////////////////////////////////////////////
//
//  �S�ẴV�[������A�N�Z�X�ł���f�[�^
//
struct GameData
{
	Wii wii;
};

using MyApp = SceneManager<String, GameData>;
