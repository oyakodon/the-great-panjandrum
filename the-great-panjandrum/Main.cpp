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