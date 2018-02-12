#pragma once

#include "../Wiimote/wm4s3d.hpp"

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

	// ゲームのバージョン
	const String Version = L"Ver. 0.1.10";

	// ロゴ画面中央下部に表示される説明
	const Array<String> Descriptions = {
		L"プログラミング部 部内プロコン2017",
		L"個人制作作品",
		L"By Oyakodon"
	};

	// 中心から見てプレイヤーの描画位置をどれくらいずらすか(中心より下なら+)
	const int32 playerPosOffset = 100;

}

/// <summary>
/// ゲームモード
/// </summary>
enum class PlayMode : int
{
	Story = 0,
	Endless,
	VS
};

///////////////////////////////////////////////////////////////////////
//
//  全てのシーンからアクセスできるデータ
//
struct GameData
{
	Wii wii[2];
	PlayMode lastMode;
	long long lastClearTime;
	bool debugMode = false;
};

using MyApp = SceneManager<String, GameData>;

///////////////////////////////////////////////////////////////////////
//
//  セーブ用スコアデータ
//
struct ScoreData
{
	long long clearTime;

	DateTime date;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(clearTime, date);
	}
};

