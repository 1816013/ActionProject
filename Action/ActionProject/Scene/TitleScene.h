#pragma once
#include "Scene.h"
class SceneController;
class ContinueScene;
class TitleScene : public Scene
{
	friend ContinueScene;
	friend SceneController;
private:
	TitleScene(SceneController&);

	// Updater
	void WaitUpdate(const Input&);
	void FastBlinkUpdate(const Input&);
	void FadeoutUpdate(const Input&);
	using UpdateFunction_t = void (TitleScene::*)(const Input&);
	UpdateFunction_t updater_;

	// Drawer
	void NomalDraw();
	void FadeDraw();
	using DrawerFunction_t = void (TitleScene::*)();
	DrawerFunction_t drawer_;
	
public:
	~TitleScene();
	
	void Update(const Input&)override;
	void Draw()override;
};

