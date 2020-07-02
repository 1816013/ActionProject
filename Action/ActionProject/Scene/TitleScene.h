#pragma once
#include "Scene.h"

class SceneController;
class ContinueScene;
class PauseScene;
class TitleScene : public Scene
{
	friend ContinueScene;
	friend PauseScene;
	friend SceneController;
private:
	TitleScene(SceneController&);

	// Updater
	// タイトルシーンの基本Updater
	void TitleUpdate(const Input&);
	// 文字の点滅が早くなるUpdater
	void FastBlinkUpdate(const Input&);
	// フェードアウト実行時のUpdater
	void FadeoutUpdate(const Input&);

	void FadeinUpdate(const Input&);
	using UpdateFunction_t = void (TitleScene::*)(const Input&);
	UpdateFunction_t updater_;

	// Drawer
	// タイトルシーンの基本描画
	void NomalDraw();
	// フェード時の描画
	void FadeDraw();
	using DrawerFunction_t = void (TitleScene::*)();
	DrawerFunction_t drawer_;
	
public:
	~TitleScene();
	
	void Update(const Input&)override;
	void Draw()override;
};

