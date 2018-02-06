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
	const String Version = L"Ver. 0.1.9";

	// セーブデータの保存場所
	const FilePath SaveFilePath = L"save.dat";

	// ロゴ画面中央下部に表示される説明
	const Array<String> Descriptions = {
		L"プログラミング部 部内プロコン2017",
		L"個人制作作品",
		L"By Oyakodon"
	};

	// 中心から見てプレイヤーの描画位置をどれくらいずらすか(中心より下なら+)
	const int32 playerPosOffset = 100;

}

///////////////////////////////////////////////////////////////////////
//
//  全てのシーンからアクセスできるデータ
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
//  セーブ用スコアデータ
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
//  デフォルトのハイスコア
//
const std::array<ScoreData, 5> defaultHighScores
{
	ScoreData{ 50, DateTime(2018,1,1), PlayMode::Story },
	ScoreData{ 40, DateTime(2018,1,1), PlayMode::Story },
	ScoreData{ 30, DateTime(2018,1,1), PlayMode::Story },
	ScoreData{ 20, DateTime(2018,1,1), PlayMode::Endless },
	ScoreData{ 10, DateTime(2018,1,1), PlayMode::VS },
};
