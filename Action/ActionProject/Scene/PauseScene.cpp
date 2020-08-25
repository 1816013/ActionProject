#include "PauseScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "../System/Input.h"
#include "../System/Application.h"
#include "TitleScene.h"
#include "../System/FileManager.h"
#include "../System/File.h"
#include "KeyConfigScene.h"
#include "../Arithmetic.h"


namespace
{
	const Size& vpSize = Application::Instance().GetViewport().GetSize();
	const Size rectSize = Size(400, 400);
	Rect menuRect(Position2f(vpSize.w / 2.0f, vpSize.h / 2.0f),Size(rectSize.w, rectSize.h));
	constexpr int AccordionInterval = 20;	
	unsigned int waitTimer = 0;	
	
	int indicatorWidth_ = 0;
	constexpr int pauseTitle_y = 32;	// メニュー上からタイトルまでのオフセット
	constexpr int menubase_y = 96;		// メニューのタイトルからのオフセット
	constexpr int indicater_y = 32;
	constexpr int menuInterval_y = 48;	// メニューの文字間隔
	const wchar_t* titleName = L"Pause Menu";

	size_t currentSelectNo_;
}

PauseScene::~PauseScene()
{
	DeleteGraph(IndicatorH);
}


PauseScene::PauseScene(SceneController& c) : Scene(c),
updater_(&PauseScene::OpenUpdate),
drawer_(&PauseScene::OpenCloseDraw)
{
	waitTimer = AccordionInterval;
	auto& fileMng = FileManager::Instance();
	if (IndicatorH == -1)
	{
		IndicatorH = fileMng.Load(L"Resource/Image/UI/indicator.png")->Handle();
	}

	int y = menubase_y;

	menuItems_.emplace_back(MenuItem(L"ゲームに戻る", 
		{ menubase_y, y},
		[this]() { CloseMenu();}));
	y += menuInterval_y;
	menuItems_.emplace_back(MenuItem(L"キーコンフィグ",
		{ menubase_y, y },
		[this]() { controller_.PushScene(new KeyConfigScene(controller_)); }));
	y += menuInterval_y;
	menuItems_.emplace_back(MenuItem(L"タイトルに戻る",
		{ menubase_y, y },
		[this]() { controller_.CleanChangeScene(new TitleScene(controller_)); }));
	y += menuInterval_y;
	menuItems_.emplace_back(MenuItem(L"ゲームを終了する",
		{ menubase_y, y },
		[this]() { Application::Instance().Exit(); }));
	currentSelectNo_ = 0;
	
	GetGraphSize(IndicatorH, &indicatorWidth_, nullptr);
}

void PauseScene::PauseUpdate(const Input& input)
{
	if (input.IsTriggered("pause"))
	{
		CloseMenu();
	}
	if (input.IsTriggered("down"))
	{
		currentSelectNo_ = ModuloIncrement(currentSelectNo_, menuItems_.size());
	}
	if (input.IsTriggered("up"))
	{
		currentSelectNo_ = ModuloDecrement(currentSelectNo_, menuItems_.size());
	}

	for (auto& m : menuItems_)
	{
		m.isActive = false;
	}
	menuItems_[currentSelectNo_].isActive = true;

	if (input.IsTriggered("OK"))
	{
		menuItems_[currentSelectNo_].func();
	}
}

// メニューを開く
void PauseScene::OpenUpdate(const Input& input)
{	
	if (--waitTimer == 0)	
	{		
		updater_ = &PauseScene::PauseUpdate;
		drawer_ = &PauseScene::NomalDraw;
	}
}

// メニューを閉じる
void PauseScene::CloseUpdate(const Input&)
{
	if (++waitTimer == AccordionInterval)
	{		
		controller_.PopScene();
	}
}


void PauseScene::CloseMenu()
{
	waitTimer = 0;
	updater_ = &PauseScene::CloseUpdate;
	drawer_ = &PauseScene::OpenCloseDraw;
}

void PauseScene::Update(const Input& input)
{
	(this->*updater_)(input);
}

void PauseScene::NomalDraw()
{
	DrawString(0, 0, L"PauseScene", 0xff0000);

	// 枠の描画
	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);
	DrawBoxAA(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBoxAA(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0xffffff, false);

	// メニュー文字表示
	int titleW =GetDrawStringWidth(titleName, static_cast<int>(wcslen(titleName)));
	DrawStringF(menuRect.pos.x - titleW / 2, menuRect.Top() + pauseTitle_y, titleName, 0xffffff);
	for(auto m : menuItems_)
	{
		uint32_t col = 0xffffff;
		int offset_x = 0;
		if (m.isActive)
		{
			col = 0xff0000;
			offset_x = indicatorWidth_;
		}
		DrawStringF(menuRect.Left() + m.pos.x + offset_x, menuRect.Top() + m.pos.y, m.menuText.c_str(), col);
	}

	auto& indicatorPos = menuItems_[currentSelectNo_].pos;
	DrawGraphF(menuRect.Left() + indicatorPos.x - indicatorWidth_, menuRect.Top() + indicatorPos.y , IndicatorH, true);
}

void PauseScene::OpenCloseDraw()
{         
	auto vh = static_cast<float>(AccordionInterval - waitTimer) / AccordionInterval;
	Rect rc = menuRect;
	rc.size.h =static_cast<int>(vh * rectSize.h);

	// 枠の描画
	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);
	DrawBoxAA(rc.Left(), rc.Top(), rc.Right(), rc.Bottom(), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBoxAA(rc.Left(), rc.Top(), rc.Right(), rc.Bottom(), 0xffffff, false);
}


void PauseScene::Draw()
{
	(this->*drawer_)();	
}
