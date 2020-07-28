#include "GamePlayingScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "GameOver.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <assert.h>
#include "../Input.h"
#include "PauseScene.h"
#include "../Game/Player/Player.h"
#include "../Game/Background.h"
#include "../Game/Player/ProjectileManager.h"
#include "../Game/Enemy/EnemyManager.h"
#include "../Game/Enemy/SideSpawner.h"
#include "../Game/Enemy/Slasher.h"
#include "../Game/CollisionManager.h"
#include "../Game/Effect.h"
#include "../Stage.h"
#include "../Camera.h"
#include "../Debugger.h"

using namespace std;
namespace 
{
	constexpr uint32_t FadeInterval = 45;
	unsigned int waitTimer = 0;
	int weaponUIH_[3];
}


GamePlayingScene::GamePlayingScene(SceneController & c) : Scene(c),
updater_(&GamePlayingScene::FadeinUpdate),
drawer_(&GamePlayingScene::FadeDraw)
{
	
	waitTimer = 0;
	camera_ = make_shared<Camera>();
	collisionManager_ = make_shared<CollisionManager>();
	effectManager_ = make_shared<EffectManager>();
	bg_ = make_unique<Background>(camera_);
	projectileManager_ = make_unique<ProjectileManager>();
	player_ = make_shared<Player>(this);
	player_->SetPosition({ 350, 500 });
	camera_->SetPlayer(player_);
	enemyManager_ = make_shared<EnemyManager>();
	spawners_.emplace_back(new SideSpawner({ 0, 0 }, new Slasher(player_, effectManager_, camera_), enemyManager_, collisionManager_, camera_));
	

	weaponUIH_[0] = LoadGraph(L"Resource/Image/UI/bomb.png");
	weaponUIH_[1] = LoadGraph(L"Resource/Image/UI/shuriken.png");
	weaponUIH_[2] = LoadGraph(L"Resource/Image/UI/chain.png");

	stage_ = make_shared<Stage>(camera_);
	stage_->Load(L"Resource/level/level2.fmf");
}

GamePlayingScene::~GamePlayingScene()
{
	
}

void GamePlayingScene::AddListner(std::shared_ptr<InputListner> listner)
{
	listners_.push_back(listner);
}


void GamePlayingScene::GamePlayUpdate(const Input& input)
{
	camera_->Update();
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
	collisionManager_->Update();
	projectileManager_->Update();
	
	player_->Update();
	for (auto& listner : listners_)
	{
		listner->Notify(input);
	}
	enemyManager_->Update();
	for (auto spw : spawners_)
	{
		spw->Update();
	}

	effectManager_->Update();
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

void GamePlayingScene::NomalDraw()
{		
	bg_->Draw();
	stage_->Draw(static_cast<size_t>(LayerType::Base));
	projectileManager_->Draw();
	enemyManager_->Draw();
	player_->Draw();
	effectManager_->Draw();
	stage_->Draw(static_cast<size_t>(LayerType::Flont));

	
	// •ŠíUI•\Ž¦
	DrawBox(10, 10, 76, 76, 0x000000, false);
	DrawGraph(10, 10, weaponUIH_[player_->CurrentEquipmentNo()], true);
	DrawBox(10, 10, 74, 74, 0xffffff, false);
	DrawString(100, 100, L"GamePlayingScene", 0xffffff);
	collisionManager_->DebugDraw(camera_);
}

void GamePlayingScene::FadeDraw()
{
	NomalDraw();
	
	auto blendParam = static_cast<int>(255 * static_cast<float>(FadeInterval - waitTimer) / FadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, blendParam);
	DrawBox(0, 0, 800, 600, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

ProjectileManager& GamePlayingScene::GetProjectileManager()
{
	assert(projectileManager_);
	return *projectileManager_;
}

std::shared_ptr<CollisionManager> GamePlayingScene::GetCollisionManager()
{
	return collisionManager_;
}

std::shared_ptr<Player>& GamePlayingScene::GetPlayer()
{
	return player_;
}

std::shared_ptr<Camera>& GamePlayingScene::GetCamera()
{
	return camera_;
}



void GamePlayingScene::Update(const Input & input)
{
	(this->*updater_)(input);	
}

void GamePlayingScene::Draw()
{
	(this->*drawer_)();	
}
