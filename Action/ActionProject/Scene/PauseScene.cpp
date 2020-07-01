#include "PauseScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "../Input.h"
//#include "../Geometry.h"
#include "../Application.h"

namespace
{
	const Size& vpSize = Application::Instance().GetViewport().GetSize();
	const Size rectSize = Size(400, 400);
	Rect menuRect(Position2(vpSize.w / 2, vpSize.h / 2),Size(400, 400));
	constexpr int OpenInterval = 20;
	
	int waitTimer = 0;
	
}


PauseScene::PauseScene(SceneController& c) : Scene(c),
updater_(&PauseScene::OpenUpdate),
drawer_(&PauseScene::OpenDraw)
{
	waitTimer = OpenInterval;
}

void PauseScene::PauseUpdate(const Input& input)
{
	if (input.IsTriggered("pause"))
	{
		controller_.PopScene();		
	}
}

void PauseScene::OpenUpdate(const Input& input)
{	
	if (--waitTimer == 0)
	{
		
		updater_ = &PauseScene::PauseUpdate;
	}
}

void PauseScene::Update(const Input& input)
{
	(this->*updater_)(input);
}

void PauseScene::NomalDraw()
{
	DrawString(0, 0, L"PauseScene", 0xff0000);

	// ˜g‚Ì•`‰æ
	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);
	DrawBox(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0xffffff, false);
}

void PauseScene::OpenDraw()
{
	auto vh = static_cast<float>(OpenInterval - waitTimer) / OpenInterval;
	Rect rc = menuRect;
	menuRect.size.h = vh * rectSize.h;
	// ˜g‚Ì•`‰æ
	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);
	DrawBox(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(menuRect.Left(), menuRect.Top(), menuRect.Right(), menuRect.Bottom(), 0xffffff, false);
	/*menuRect.size.w = rectSize.w * static_cast<float>(OpenInterval - waitTimer) / OpenInterval;
	menuRect.size.h = rectSize.h * static_cast<float>(OpenInterval - waitTimer) / OpenInterval;*/
}


void PauseScene::Draw()
{
	(this->*drawer_)();	
}
