#pragma once
#include "Scene.h"
class TitleScene;
class GamePlayingScene : public Scene
{
	friend TitleScene;
private:
	GamePlayingScene(SceneController&);

	void FadeoutUpdate(const Input&);
	void FadeinUpdate(const Input&);
	void GamePlayUpdate(const Input&);

	using UpdateFunction_t = void (GamePlayingScene::*)(const Input&);
	UpdateFunction_t updater_;
	void NomalDraw();
	void FadeDraw();

	using DrawerFunction_t = void (GamePlayingScene::*)();
	DrawerFunction_t drawer_;
	
public:
	~GamePlayingScene();
	void Update(const Input&)override;
	void Draw()override;
};
