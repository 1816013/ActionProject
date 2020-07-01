#include "GamePlayingScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "GameOver.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "../Input.h"
#include "PauseScene.h"

using namespace std;
namespace 
{
	constexpr uint32_t FadeInterval = 45;
	unsigned int waitTimer = 0;
	
	int _bgH[11] = {};
	int _runH[6] = {};
	int runCount = 0;
}


GamePlayingScene::GamePlayingScene(SceneController & c) : Scene(c),
updater_(&GamePlayingScene::FadeinUpdate),
drawer_(&GamePlayingScene::FadeDraw)
{
	waitTimer = 0;
	int skipNo[2] = { 4 , 7 };
	int no = 9;
	for (int i = 0; i < _countof(_bgH); i++)
	{
		wstringstream wss;
		wss << L"Resourse/Image/BackGround/Layer_";
		wss << setw(4) << setfill(L'0') << i << "_";
		if (std::count(begin(skipNo), end(skipNo), i) > 0)
		{
			wss << "Lights";
		}
		else
		{
			wss << no;
			--no;
		}
		wss << ".png";
		_bgH[_countof(_bgH)-1-i] = LoadGraph(wss.str().c_str());
	}
	// ƒLƒƒƒ‰‚Ìƒ[ƒh
	for (int i = 0; i < _countof(_runH); i++)
	{
		wstringstream wss;
		wss << L"Resourse/Image/Player/adventurer-run-";
		wss << setw(2) << setfill(L'0') << i;
		wss << ".png";
		_runH[i] = LoadGraph(wss.str().c_str());
	}	
}

GamePlayingScene::~GamePlayingScene()
{
	for (auto& h : _bgH)
	{
		DeleteGraph(h);
	}
	for (auto& h : _runH)
	{
		DeleteGraph(h);
	}
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
	++runCount;
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
}

void GamePlayingScene::NomalDraw()
{
	for (auto h : _bgH)
	{
		DrawExtendGraph(0, 0, 800, 600, h, true);
	}
	DrawRotaGraph(350, 500,3.0f,0.0f, _runH[runCount / 5 % _countof(_runH)], true);
	
	
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
