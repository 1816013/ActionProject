#include "PauseScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "../Input.h"
#include "../Application.h"

namespace
{
	const Size& vpSize = Application::Instance().GetViewport().GetSize();
	const Size rectSize = Size(400, 400);
	Rect menuRect(Position2(vpSize.w / 2, vpSize.h / 2),Size(rectSize.w, 0));
	constexpr int AccordionInterval = 20;	
	int waitTimer = 0;	
}


PauseScene::PauseScene(SceneController& c) : Scene(c),
updater_(&PauseScene::AccordionOpenUpdate),
drawer_(&PauseScene::AccordionDraw)
{
	waitTimer = AccordionInterval;
}

void PauseScene::PauseUpdate(const Input& input)
{
	if (input.IsTriggered("pause"))
	{
		waitTimer = 0;
		updater_ = &PauseScene::AccordionCloseUpdate;
		drawer_ = &PauseScene::AccordionDraw;
	}
}

// メニューを開く
void PauseScene::AccordionOpenUpdate(const Input& input)
{	
	if (--waitTimer < 0)	// ここは順番的に-1まで含めないと開き切らない
	{		
		updater_ = &PauseScene::PauseUpdate;
		drawer_ = &PauseScene::NomalDraw;
	}
}

// メニューを閉じる
void PauseScene::AccordionCloseUpdate(const Input&)
{
	if (++waitTimer == AccordionInterval)
	{		
		controller_.PopScene();
	}
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
	DrawBox(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0xffffff, false);
}

void PauseScene::AccordionDraw()
{         
	auto vh = static_cast<float>(AccordionInterval - waitTimer) / AccordionInterval;
	menuRect.size.h = vh * rectSize.h;
	NomalDraw();
}


void PauseScene::Draw()
{
	(this->*drawer_)();	
}
