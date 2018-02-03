#include "Scene\GameData.hpp"
#include "Scene\Logo.hpp"
#include "Scene\Title.hpp"
#include "Scene\Wiimgr.hpp"
#include "Scene\Setting.hpp"
#include "Scene\Result.hpp"
#include "Scene\Score.hpp"

#include "Scene\Stage\Editor.hpp"
#include "Scene\Stage\Endless.hpp"
#include "Scene\Stage\Story.hpp"
#include "Scene\Stage\VS.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

void Main()
{
	Window::Resize(1280, 720);
	ScalableWindow::Setup(1280, 720);

	Window::SetTitle(GameInfo::Title);
	System::SetExitEvent(WindowEvent::CloseButton);

	//////////////////////////////////////////////////////////////
	//
	//  使用するシーン
	//
	MyApp manager;
	manager.add<Logo>(L"Logo");
	manager.add<Wiimgr>(L"Wiimgr");
	manager.add<Title>(L"Title");
	manager.add<StageStory>(L"StageStory");
	manager.add<Result>(L"Result");
	manager.add<Score>(L"Score");
	manager.add<Setting>(L"Setting");

	//////////////////////////////////////////////////////////////
	//
	//  使用するフォント
	//
	FontAsset::Register(L"Title", 72, Typeface::Heavy, FontStyle::Outline);
	FontAsset(L"Title").changeOutlineStyle(TextOutlineStyle(Color(60), Color(255), 72 * 0.05));
	FontAsset::Register(L"Menu", 24, Typeface::Bold);
	FontAsset::Register(L"Version", 14, Typeface::Regular);
	FontAsset::Register(L"UI_Small", 14, L"Meiryo UI", FontStyle::Regular);
	FontAsset::Register(L"UI", 18, L"Meiryo UI", FontStyle::Regular);
	FontAsset::Register(L"UI_Large", 28, L"Meiryo UI", FontStyle::Bold);

	//////////////////////////////////////////////////////////////
	//
	//  使用する音
	//
	SoundAsset::Register(L"one01", L"Asset/one01.mp3");

	//////////////////////////////////////////////////////////////
	//
	//  使用する画像
	//
	TextureAsset::Register(L"bg_natural_umi", L"Asset/bg_natural_umi.jpg"); // 背景
	TextureAsset::Register(L"hata", L"Asset/hata.png"); // 旗

	// Block
	TextureAsset::Register(L"table_white_left", L"Asset/table_white_left.png");
	TextureAsset::Register(L"table_white_center", L"Asset/table_white_center.png");
	TextureAsset::Register(L"table_white_right", L"Asset/table_white_right.png");
	
	// Player
	TextureAsset::Register(L"panjandrum", L"Asset/panjandrum.png");


	// Debugビルドならデバッグモードに
#ifdef _DEBUG
	manager.get()->debugMode = true;
	Console::Open();
#endif

	//////////////////////////////////////////////////////////////
	//
	//  メインループ
	//
	while (System::Update())
	{
		{
			const auto transformer = ScalableWindow::CreateTransformer();
			
			if (!manager.updateAndDraw())
			{
				break;
			}

			// デバッグモード表示
			if (manager.get()->debugMode)
			{
				// Ctrl + Shiftでマウス座標を右上に表示する
				if (Input::KeyLControl.pressed && Input::KeyLShift.pressed)
				{
					FontAsset(L"Debug")(L"マウス座標: ", Mouse::PosF()).draw({0, 0}, Palette::Red);
					Line(Mouse::PosF() - Vec2(5, 0), Mouse::PosF() + Vec2(5, 0)).draw(Palette::Red);
					Line(Mouse::PosF() - Vec2(0, 5), Mouse::PosF() + Vec2(0, 5)).draw(Palette::Red);
				}

				const Size debugSize = FontAsset(L"Debug")(L"DEBUGMODE").region().size;
				FontAsset(L"Debug")(L"DEBUGMODE").drawAt(Window::BaseSize().moveBy(-debugSize), Palette::Orange);
			}

		}
		
		// フルスクリーン
		if (Input::KeyF11.clicked)
		{
			if (Window::IsFullSceen())
			{
				Window::SetFullscreen(false, Size(1280, 720));
			}
			else
			{
				const Array<Size> resolutions = Graphics::GetFullScreenSize();
				Window::SetFullscreen(true, resolutions[resolutions.size() - 1]);
			}
			
		}

		ScalableWindow::DrawBlackBars();
	}

}