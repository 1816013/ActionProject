#include "TitleScene.h"
#include "SceneController.h"
#include "GamePlayingScene.h"
#include <DxLib.h>
#include "../System/Input.h"
#include "../System/Application.h"
#include "../Geometry.h"
#include "../System/FileManager.h"
#include "../System/File.h"
#include "../System/Application.h"

namespace{
	constexpr uint32_t FadeInterval = 45;
	constexpr uint32_t BlinkIntervalNomal = 30;
	constexpr uint32_t BlinkIntervalFast = 2;
	unsigned int waitTimer = 0;
	unsigned int blinkTimer = 0;
	unsigned int blinkInterval = 45;
	int titleH;
	int startH;
	SlashShape slash_({ 400.0f, 300.0f }, { -125.0f, -125.0f }, 0.0f);
}

TitleScene::TitleScene(SceneController& c): Scene(c),
updater_(&TitleScene::FadeinUpdate),
drawer_(&TitleScene::FadeDraw)
{
	waitTimer = 0;
	dist_ = 0.5;
	angle_ = DX_PI_F;
	blinkInterval = BlinkIntervalNomal;
	auto& fileMng = FileManager::Instance();
	titleH = fileMng.Load(L"Resource/Image/Title/Title.png")->Handle();
	startH = fileMng.Load(L"Resource/Image/Title/pressstart.png")->Handle();
	auto& rc = Application::Instance().GetViewport();
	captureH_ = MakeScreen(rc.GetSize().w, rc.GetSize().h);
	if (psH_ == -1)
	{
		psH_ = LoadPixelShader(L"Resource/Etc/testps.pso");
	}
	if (normalH_ == -1)
	{
		normalH_ = fileMng.Load(L"Resource/Etc/normal.png")->Handle();
	}
}



TitleScene::~TitleScene()
{
	FileManager::Instance().DeleteAllResources();
}


void TitleScene::TitleUpdate(const Input& input)
{
	if (input.IsTriggered("OK"))
	{
		waitTimer = BlinkIntervalFast;
		updater_ = &TitleScene::FastBlinkUpdate;
		blinkInterval = BlinkIntervalFast;
	}
	else
	{
		if (input.IsPressed("left"))
		{
			slash_.AddAngle1(0.01f);//angle_ -= 0.05f;
		}
		
		if (input.IsPressed("right"))
		{
			slash_.AddAngle2(0.01f);
		}
		if (input.IsPressed("shot"))
		{
			slash_.AddAngle1(-0.01f);//angle_ -= 0.05f;
		}
		if (input.IsPressed("jump"))
		{
			slash_.AddAngle2(-0.01f);
		}
		if (input.IsPressed("up"))
		{
			dist_ -= 1.0f;
		}

		if (input.IsPressed("down"))
		{
			dist_ += 1.0f;
		}
	}
}

void TitleScene::FastBlinkUpdate(const Input& input)
{
	if (--waitTimer == 0)
	{
		waitTimer = FadeInterval;
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

void TitleScene::FadeinUpdate(const Input&)
{
	if (++waitTimer == FadeInterval)
	{
		updater_ = &TitleScene::TitleUpdate;
		drawer_ = &TitleScene::NomalDraw;
	}
}


void TitleScene::Update(const Input & input)
{
	blinkTimer++;
	(this->*updater_)(input);
}

void TitleScene::NomalDraw()
{
	const auto& vpSize = Application::Instance().GetViewport().GetSize();
	DrawRotaGraph(vpSize.w / 2, vpSize.h / 2, 1.0, 0.0, titleH, false);
	DrawString(100, 100, L"TitleScene", 0xffffff);
	
	if (blinkTimer / blinkInterval % 2  == 1)
	{
		DrawRotaGraph(vpSize.w / 2, 400, 1.0, 0.0, startH, true);		
	}
	SlashShape fan({ 400.0f, 300.0f }, {-125.0f, -125.0f},angle_);
	GetDrawScreenGraph(0, 0, 800, 600, captureH_);
	slash_.Draw(captureH_, dist_, psH_, normalH_);
}

void TitleScene::FadeDraw()
{
	const auto& vpSize = Application::Instance().GetViewport().GetSize();
	NomalDraw();
	auto blendParam = static_cast<int>(255 * static_cast<float>(FadeInterval - waitTimer) / FadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendParam);
	DrawBox(0, 0, vpSize.w, vpSize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Draw()
{
	(this->*drawer_)();
	//DrawString(100, 100, "TitleScene",GetColor(255, 255, 255));
}
