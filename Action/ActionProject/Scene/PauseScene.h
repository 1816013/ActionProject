#pragma once
#include "Scene.h"
#include <string>
#include <functional>
#include "../Geometry.h"


struct MenuItem
{
	std::string menuText;
	Position2 pos;
	std::function<void(void)>func;
	MenuItem(const char* str,
			 const Position2& p,
			 std::function<void(void)>& f) : menuText(str), func(f), pos(p) {}
};


class GamePlayingScene;
class PauseScene : public Scene
{
	friend GamePlayingScene;
private:
	PauseScene() = default;
	PauseScene(SceneController&);
	void PauseUpdate(const Input&);
	void OpenUpdate(const Input&);
	using UpdateFunction_t = void (PauseScene::*)(const Input&);
	UpdateFunction_t updater_;

	void NomalDraw();
	void OpenDraw();
	using DrawerFunction_t = void (PauseScene::*)();
	DrawerFunction_t drawer_;
public:
	void Update(const Input&)override;
	void Draw()override;

};

