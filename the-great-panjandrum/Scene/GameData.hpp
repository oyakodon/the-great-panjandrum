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
	const String Version = L"ver. 0.1.001";

	// ゲームの背景色
	const ColorF BackgroundColor = ColorF(0.4, 0.7, 0.5);

	// シーン切り替え時のフェードイン・アウトの色
	const ColorF FadeInColor = ColorF(1.0, 1.0, 1.0);

	// タイトルのフォントサイズ
	const int32 TitleFontSize = 72;

	// メニューのフォントサイズ
	const int32 MenuFontSize = 24;

	// メニュー項目「ゲームスタート」
	const String MenuGameStart = L"ゲームスタート";

	// メニュー項目「スコア」
	const String MenuScore = L"スコア";

	// メニュー項目「終了」
	const String MenuExit = L"終了";

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
