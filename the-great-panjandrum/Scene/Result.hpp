#pragma once

#include "GameData.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

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

