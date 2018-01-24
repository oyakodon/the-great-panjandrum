#pragma once

#include "../GameData.hpp"
#include "Block.hpp"
#include "Item.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

/// <summary>
/// ステージエディター
/// </summary>
class StageEditor
{
private:

public:

	/// <summary>
	/// CSVファイルからステージ情報を読み込みます。
	/// </summary>
	/// <param name="filepath">CSVファイルへのパス</param>
	/// <param name="blocks">ブロック</param>
	/// <param name="items">アイテム</param>
	static void LoadStage(const String& filepath, Array<Block>& blocks, Array<Item>& items)
	{

	}

};