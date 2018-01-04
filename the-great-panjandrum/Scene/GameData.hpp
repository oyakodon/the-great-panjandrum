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
	const String Version = L"ver. 0.1.001";

	// �Q�[���̔w�i�F
	const ColorF BackgroundColor = ColorF(0.4, 0.7, 0.5);

	// �V�[���؂�ւ����̃t�F�[�h�C���E�A�E�g�̐F
	const ColorF FadeInColor = ColorF(1.0, 1.0, 1.0);

	// �^�C�g���̃t�H���g�T�C�Y
	const int32 TitleFontSize = 72;

	// ���j���[�̃t�H���g�T�C�Y
	const int32 MenuFontSize = 24;

	// ���j���[���ځu�Q�[���X�^�[�g�v
	const String MenuGameStart = L"�Q�[���X�^�[�g";

	// ���j���[���ځu�X�R�A�v
	const String MenuScore = L"�X�R�A";

	// ���j���[���ځu�I���v
	const String MenuExit = L"�I��";

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
