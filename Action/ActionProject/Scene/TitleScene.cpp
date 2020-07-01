#include "TitleScene.h"
#include "SceneController.h"
#include "GamePlayingScene.h"
#include <DxLib.h>
#include "../Input.h"
#include "../Application.h"
#include "../Geometry.h"

namespace{
	constexpr uint32_t FadeoutInterval = 45;
	constexpr uint32_t BlinkIntervalNomal = 30;
	constexpr uint32_t BlinkIntervalFast = 2;
	unsigned int waitTimer = 0;
	unsigned int blinkTimer = 0;
	unsigned int blinkInterval = 45;
	int titleH;
	int startH;
}

TitleScene::TitleScene(SceneController& c): Scene(c),
updater_(&TitleScene::WaitUpdate),
drawer_(&TitleScene::NomalDraw)
{
	blinkInterval = BlinkIntervalNomal;
	titleH = LoadGraph(L"Resourse/Image/Title/Title.png");
	startH = LoadGraph(L"Resourse/Image/Title/pressstart.png");
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleH);
	DeleteGraph(startH);
}


void TitleScene::WaitUpdate(const Input& input)
{
	if (input.IsTriggered("OK"))
	{
		waitTimer = BlinkIntervalFast;
		updater_ = &TitleScene::FastBlinkUpdate;
		blinkInterval = BlinkIntervalFast;
	}
}

void TitleScene::FastBlinkUpdate(const Input& input)
{
	if (--waitTimer == 0)
	{
		waitTimer = FadeoutInterval;
		updater_ = &TitleScene::FadeoutUpdate;
		drawer_ = &TitleScene::FadeDraw;

	}
}

void TitleScene::FadeoutUpdate(const Input &)
{
	if (--waitTimer == 0)
	{
		controller_.ChangeScene(new GamePlayingScene(controller_));
	}
}


void TitleScene::Update(const Input & input)
{
	blinkTimer++;
	(this->*updater_)(input);
}

void TitleScene::NomalDraw()
{
	//Position2 pos;
	//Size iSize;
	//GetGraphSize(titleH, &iSize.w, &iSize.h);
	const auto& vpSize = Application::Instance().GetViewport().GetSize();
	//pos.x = (vpSize.w - iSize.w) / 2;
	//pos.y = (vpSize.h - iSize.h) / 2;
	DrawRotaGraph(vpSize.w / 2, vpSize.h / 2, 1.0, 0.0, titleH, false);
	DrawString(100, 100, L"TitleScene", 0xffffff);
	
	if (blinkTimer / blinkInterval % 2  == 1)
	{
		DrawRotaGraph(vpSize.w / 2, 400, 1.0, 0.0, startH, true);
		
	}
}

void TitleScene::FadeDraw()
{
	const auto& vpSize = Application::Instance().GetViewport().GetSize();
	NomalDraw();
	auto blendParam = static_cast<int>(255 * static_cast<float>(FadeoutInterval - waitTimer) / FadeoutInterval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendParam);
	DrawBox(0, 0, vpSize.w, vpSize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Draw()
{
	(this->*drawer_)();
	//DrawString(100, 100, "TitleScene",GetColor(255, 255, 255));
}