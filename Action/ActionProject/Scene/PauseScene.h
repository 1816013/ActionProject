#pragma once
#include "Scene.h"
#include <string>
#include <functional>
#include "../Geometry.h"
#include <vector>

struct MenuItem
{
	std::wstring menuText;
	Position2 pos;
	std::function<void(void)>func;
	bool isActive = false;
	MenuItem(const wchar_t* str,
			 const Position2& p,
			 std::function<void(void)> f) : menuText(str), func(f), pos(p) {}
};

class GamePlayingScene;
class PauseScene : public Scene
{
	friend GamePlayingScene;
private:
	std::vector<MenuItem>menuItems_;
	int IndicatorH = -1;

	PauseScene() = default;
	PauseScene(SceneController&);
	using DrawerFunction_t = void (PauseScene::*)();
	DrawerFunction_t drawer_;

	// updater
	// ポーズの基本Updater
	void PauseUpdate(const Input&);
	// ポーズのメニューを開く際のUpdater
	void OpenUpdate(const Input&);
	// ポーズのメニューを閉じる際のUpdater
	void CloseUpdate(const Input&);
	using UpdateFunction_t = void (PauseScene::*)(const Input&);
	UpdateFunction_t updater_;

	// drawer
	// ポーズシーンの基本drawer
	void NomalDraw();
	// ポーズのメニューの開閉する際のdrawer
	void OpenCloseDraw();
	
	void CloseMenu();


public:
	~PauseScene();
	void Update(const Input&)override;
	void Draw()override;

};

