#pragma once

#include "../wm4s3d.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  ゲームの基本情報
//
namespace GameInfo
{
	// ゲームのタイトル
	const String Title = L"The Great Panjandrum";

	// ゲームのバージョン（空の文字列も OK）
	const String Version = L"ver. 0.1.002";

	// セーブデータの保存場所
	const FilePath SaveFilePath = L"Save/Score.dat";

}

///////////////////////////////////////////////////////////////////////
//
//  全てのシーンからアクセスできるデータ
//
struct GameData
{
	Wii wii;
};

using MyApp = SceneManager<String, GameData>;
