#include "ContinueScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "TitleScene.h"
#include "../System/Input.h"
#include "../System/Application.h"
#include "../Geometry.h"

namespace
{
	constexpr uint32_t FadeInterval = 45;
	constexpr int brend_max = 45;
	unsigned int waitTimer = 0;
}

ContinueScene::ContinueScene(SceneController & c) : Scene(c),
updater_(&ContinueScene::FadeinUpdate),
drawer_(&ContinueScene::FadeDraw)
{
	waitTimer = 0;
}

void ContinueScene::FadeinUpdate(const Input& input)
{
	if (++waitTimer == FadeInterval)
	{
		updater_ = &ContinueScene::ContinueUpdate;
		drawer_ = &ContinueScene::NomalDraw;
	}
}

void ContinueScene::FadeoutUpdate(const Input& input)
{
	if (--waitTimer == 0)
	{
		controller_.ChangeScene(new TitleScene(controller_));
	}
}

void ContinueScene::ContinueUpdate(const Input& input)
{
	if (input.IsTriggered("OK"))
	{
		waitTimer = FadeInterval;
		updater_ = &ContinueScene::FadeoutUpdate;
		drawer_ = &ContinueScene::FadeDraw;
	}
}

void ContinueScene::NomalDraw()
{
	DrawString(100, 100, L"ContinueScene", GetColor(255, 255, 255));
}

void ContinueScene::FadeDraw()
{
	NomalDraw();
	auto blendParam = static_cast<int>(brend_max * static_cast<float>(FadeInterval - waitTimer) / FadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendParam);
	auto scSize = Application::Instance().GetViewport().GetSize();
	DrawBox(0, 0, scSize.w, scSize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void ContinueScene::Update(const Input& input)
{
	(this->*updater_)(input);
	
}

void ContinueScene::Draw()
{
	(this->*drawer_)();
	
}
