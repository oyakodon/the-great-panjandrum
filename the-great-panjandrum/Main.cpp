#include "Scene\GameData.hpp"
#include "Scene\Title.hpp"
#include "Scene\Game.hpp"
#include "Scene\Result.hpp"

#include <Siv3D.hpp>
#include <HamFramework.hpp>

void Main()
{
	Window::Resize(1280, 720);
	// Window::SetFullscreen(true, Size(1920, 1080));

	ScalableWindow::Setup(1280, 720);

	Window::SetTitle(GameInfo::Title);
	System::SetExitEvent(WindowEvent::CloseButton);

	//////////////////////////////////////////////////////////////
	//
	//  使用するシーン
	//
	MyApp manager;
	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");
	manager.add<Score>(L"Score");

	//////////////////////////////////////////////////////////////
	//
	//  使用するフォント
	//
	FontAsset::Register(L"Title", 72, Typeface::Heavy, FontStyle::Outline);
	FontAsset(L"Title").changeOutlineStyle(TextOutlineStyle(Color(60), Color(255), 72 * 0.05));
	FontAsset::Register(L"Menu", 24, Typeface::Bold);
	FontAsset::Register(L"Version", 14, Typeface::Regular);
	FontAsset::Register(L"CountDown", 72, Typeface::Bold);
	FontAsset::Register(L"Result", 80, Typeface::Bold);
	FontAsset::Register(L"ResultButton", 32, Typeface::Regular);
	FontAsset::Register(L"GameTime", 40, Typeface::Light);
	FontAsset::Register(L"ScoreList", 50, Typeface::Heavy);
	FontAsset::Register(L"ScoreListDate", 25, Typeface::Regular, FontStyle::Italic);

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
		}

		ScalableWindow::DrawBlackBars();

		// Escキーが3秒以上押され続けたら終了
		if (Input::KeyEscape.pressedDuration >= 3000)
		{
			System::Exit();
		}

		if (Input::KeyEscape.pressedDuration >= 1000)
		{
			Rect(Window::Size()).draw(ColorF(0, 0, 0, (Input::KeyEscape.pressedDuration - 1000) / 1500.0f));
		}

	}

}