#include "GamePlayingScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "GameOver.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "../Input.h"
#include "PauseScene.h"
#include "../Game/Player.h"
#include "../Game/Background.h"

using namespace std;
namespace 
{
	constexpr uint32_t FadeInterval = 45;
	unsigned int waitTimer = 0;
}


GamePlayingScene::GamePlayingScene(SceneController & c) : Scene(c),
updater_(&GamePlayingScene::FadeinUpdate),
drawer_(&GamePlayingScene::FadeDraw)
{
	waitTimer = 0;
		
	player_ = make_unique<Player>(this);
	bg_ = make_unique<Background>();
}

GamePlayingScene::~GamePlayingScene()
{
	
}

void GamePlayingScene::AddListner(std::shared_ptr<InputListner> listner)
{
	listners_.push_back(listner);
}

void GamePlayingScene::FadeoutUpdate(const Input& input)
{
	if (--waitTimer == 0)
	{
		controller_.ChangeScene(new GameOverScene(controller_));		
	}
}

void GamePlayingScene::FadeinUpdate(const Input& input )
{
	if (++waitTimer == FadeInterval)
	{
		updater_ = &GamePlayingScene::GamePlayUpdate;
		drawer_ = &GamePlayingScene::NomalDraw;
	}
}

void GamePlayingScene::GamePlayUpdate(const Input& input)
{
	if (input.IsTriggered("OK"))
	{
		updater_ = &GamePlayingScene::FadeoutUpdate;
		drawer_ = &GamePlayingScene::FadeDraw;
		waitTimer = FadeInterval;
	}
	if (input.IsTriggered("pause"))
	{
		controller_.PushScene(new PauseScene(controller_));
	}
	bg_->Update();
	player_->Update();
	for (auto& listner : listners_)
	{
		listner->Notify(input);
	}
}

void GamePlayingScene::NomalDraw()
{	
	bg_->Draw();	
	player_->Draw();
	DrawString(100, 100, L"GamePlayingScene", 0xffffff);
}

void GamePlayingScene::FadeDraw()
{
	NomalDraw();
	
	auto blendParam = static_cast<int>(255 * static_cast<float>(FadeInterval - waitTimer) / FadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendParam);
	DrawBox(0, 0, 800, 600, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



void GamePlayingScene::Update(const Input & input)
{
	(this->*updater_)(input);	
}

void GamePlayingScene::Draw()
{
	(this->*drawer_)();
	
}
