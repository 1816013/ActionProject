#pragma once
#include "Scene.h"
class GamePlayingScene;
class GameOverScene : public Scene
{
	friend GamePlayingScene;
private:
	GameOverScene(SceneController&);

	void FadeinUpdate(const Input&);
	void FadeoutUpdate(const Input&);
	void GameOverUpdate(const Input&);
	using UpdateFunction_t = void (GameOverScene::*)(const Input&);
	UpdateFunction_t updater_;

	void NomalDraw();
	void FadeDraw();
	using DrawerFunction_t = void (GameOverScene::*)();
	DrawerFunction_t drawer_;
public:
	~GameOverScene() = default;
	void Update(const Input&)override;
	void Draw()override;
};


