#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

///////////////////////////////////////////////////////////////////////
//
//  セーブ用スコアデータ
//
struct ScoreData
{
	int32 score;

	Date date;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(score, date);
	}
};

///////////////////////////////////////////////////////////////////////
//
//  デフォルトのハイスコア
//
const std::array<ScoreData, 5> defaultHighScores
{
	ScoreData{ 50, Date(2017,1,1) },
	ScoreData{ 40, Date(2017,1,1) },
	ScoreData{ 30, Date(2017,1,1) },
	ScoreData{ 20, Date(2017,1,1) },
	ScoreData{ 10, Date(2017,1,1) },
};

///////////////////////////////////////////////////////////////////////
//
//  結果画面
//
class Result : public MyApp::Scene
{
private:

	std::array<ScoreData, 5> m_highScores = defaultHighScores;

public:

	~Result()
	{
		Cursor::SetStyle(CursorStyle::Default);
	}

	void init() override
	{
		//if (FileSystem::Exists(GameInfo::SaveFilePath))
		//{
		//	Deserializer<BinaryReader>{GameInfo::SaveFilePath}(m_highScores);
		//}
		//else
		//{
		//	Serializer<BinaryWriter>{GameInfo::SaveFilePath}(m_highScores);
		//}

		//if (m_highScores.back().score <= m_data->lastScore)
		//{
		//	m_highScores.back() = { m_data->lastScore, Date::Today() };

		//	std::sort(m_highScores.begin(), m_highScores.end(), [](const ScoreData& a, const ScoreData& b)
		//	{
		//		return a.score > b.score ? true : a.score == b.score ? a.date > b.date : false;
		//	});

		//	Serializer<BinaryWriter>{GameInfo::SaveFilePath}(m_highScores);
		//}
	}

	void update() override
	{
		if ((Input::MouseL | Input::KeyEscape).clicked)
		{
			changeScene(L"Title");
		}
	}

	void draw() const override
	{
		
	}
};

///////////////////////////////////////////////////////////////////////
//
//  ハイスコア一覧
//
class Score : public MyApp::Scene
{
private:

	std::array<ScoreData, 5> m_highScores = defaultHighScores;

public:

	void init() override
	{
		/*if (FileSystem::Exists(GameInfo::SaveFilePath))
		{
			Deserializer<BinaryReader>{GameInfo::SaveFilePath}(m_highScores);
		}
		else
		{
			Serializer<BinaryWriter>{GameInfo::SaveFilePath}(m_highScores);
		}*/
	}

	void update() override
	{
		if ((Input::MouseL | Input::KeyEscape).clicked)
		{
			changeScene(L"Title");
		}
	}

	void draw() const override
	{
		//const int32 h = FontAsset(L"ScoreList").height;

		//for (auto i : step(m_highScores.size()))
		//{
		//	const Rect rect = Rect(520, 100).setCenter(Window::Center().x, 120 + i * 120);

		//	rect.draw(ColorF(1.0, 0.2));

		//	FontAsset(L"ScoreList")(m_highScores[i].score)
		//		.draw(rect.pos + Point(42, (rect.h - h) / 2 + 2), Palette::Gray);

		//	FontAsset(L"ScoreList")(m_highScores[i].score)
		//		.draw(rect.pos + Point(40, (rect.h - h) / 2));

		//	const Size dateSize = FontAsset(L"ScoreListDate")(m_highScores[i].date).region().size;

		//	FontAsset(L"ScoreListDate")(m_highScores[i].date)
		//		.draw(rect.br.x - dateSize.x - 40, rect.center.y - dateSize.y / 2);

		//	for (auto k : step(5 - i))
		//	{
		//		const Point left(rect.center.movedBy(-rect.w / 2 - 40 - k * 50, 0));
		//		const Point right(rect.center.movedBy(rect.w / 2 + 40 + k * 50, 0));

		//		Rect(40).setCenter(left).rotated(45_deg).draw(AlphaF(1.0 - i * 0.1));
		//		Rect(40).setCenter(right).rotated(45_deg).draw(AlphaF(1.0 - i * 0.1));
		//	}
		//}
	}
};
