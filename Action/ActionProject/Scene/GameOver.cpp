#include "GameOver.h"
#include <DxLib.h>
#include "SceneController.h"
#include "ContinueScene.h"
#include "../System/Input.h"
#include "../System/Application.h"
#include "../Geometry.h"

namespace
{
	constexpr uint32_t FadeInterval = 45;
	unsigned int waitTimer = 0;
}


GameOverScene::GameOverScene(SceneController & c) : Scene(c), 
updater_(&GameOverScene::FadeinUpdate),
drawer_(&GameOverScene::FadeDraw)
{
	waitTimer = 0;
}

void GameOverScene::FadeinUpdate(const Input &)
{
	if (++waitTimer == FadeInterval)
	{
		updater_ = &GameOverScene::GameOverUpdate;
		drawer_ = &GameOverScene::NomalDraw;
	}
}

void GameOverScene::FadeoutUpdate(const Input& input)
{
	if (--waitTimer == 0)
	{
		controller_.ChangeScene(new ContinueScene(controller_));
	}
}

void GameOverScene::GameOverUpdate(const Input& input)
{
	if (input.IsTriggered("OK"))
	{
		waitTimer = FadeInterval;
		updater_ = &GameOverScene::FadeoutUpdate;
		drawer_ = &GameOverScene::FadeDraw;
	}
}

void GameOverScene::NomalDraw()
{
	DrawString(100, 100, L"GameOver", GetColor(255, 255, 255));
}

void GameOverScene::FadeDraw()
{
	NomalDraw();
	auto blendParam = static_cast<int>(255 * static_cast<float>(FadeInterval - waitTimer) / FadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendParam);
	auto scSize = Application::Instance().GetViewport().GetSize();
	DrawBox(0, 0, scSize.w, scSize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::Update(const Input& input)
{
	(this->*updater_)(input);
	
}

void GameOverScene::Draw()
{
	(this->*drawer_)();
}
