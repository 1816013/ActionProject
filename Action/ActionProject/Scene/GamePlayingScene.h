#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class Player;
class Background;
class TitleScene;
class InputListner;
class ProjectileManager;
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

	

	std::unique_ptr<Player>player_;
	std::unique_ptr<Background>bg_;
	std::vector<std::shared_ptr<InputListner>>listners_;
	std::unique_ptr<ProjectileManager>pm_;

public:
	~GamePlayingScene();
	void AddListner(std::shared_ptr<InputListner> listner);
	void Update(const Input&)override;
	void Draw()override;
	ProjectileManager& GetProjectileManager();
};

