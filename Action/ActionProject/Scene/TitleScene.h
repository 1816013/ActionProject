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
	float angle_;
	float dist_;
	int captureH_;

	TitleScene(SceneController&);

	// Updater
	
	/// <summary>
	///  タイトルシーンの更新
	/// </summary>
	/// <param name="input">入力情報</param>
	void TitleUpdate(const Input& input);

	/// <summary>
	/// 文字の点滅が早くなる際の更新
	/// </summary>
	/// <param name="input">入力情報</param>
	void FastBlinkUpdate(const Input& input);

	/// <summary>
	///  フェードアウト実行時の更新
	/// </summary>
	/// <param name="input">入力情報</param>
	void FadeoutUpdate(const Input& input);

	/// <summary>
	/// フェードイン実行時の更新
	/// </summary>
	/// <param name="input">入力情報</param>
	void FadeinUpdate(const Input& input);
	using UpdateFunction_t = void (TitleScene::*)(const Input&);
	UpdateFunction_t updater_;

	// Drawer
	/// <summary>
	/// タイトルシーンの描画
	/// </summary>
	void NomalDraw();

	/// <summary>
	/// フェード時の描画
	/// </summary>
	void FadeDraw();
	using DrawerFunction_t = void (TitleScene::*)();
	DrawerFunction_t drawer_;
	
public:
	~TitleScene();
	
	void Update(const Input&)override;
	void Draw()override;
};

