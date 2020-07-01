#pragma once
#include "Scene.h"
class GameOverScene;
class ContinueScene : public Scene
{
	friend GameOverScene;
private:
	ContinueScene(SceneController&);

	void FadeinUpdate(const Input&);
	void FadeoutUpdate(const Input&);
	void ContinueUpdate(const Input&);
	using UpdateFunction_t = void (ContinueScene::*)(const Input&);
	UpdateFunction_t updater_;

	void NomalDraw();
	void FadeDraw();
	using DrawerFunction_t = void (ContinueScene::*)();
	DrawerFunction_t drawer_;
public:
	~ContinueScene() = default;
	void Update(const Input&)override;
	void Draw()override;
};

