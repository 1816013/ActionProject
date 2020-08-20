#pragma once
#include "Scene.h"
#include <vector>
#include "../Geometry.h"
#include <string>
#include "../System/Input.h"

class GamePlayingScene;
class PauseScene;
class KeyConfigScene : public Scene
{
	friend GamePlayingScene;
	friend PauseScene;
private:
	Rect frameRect = { {400, 300}, {500, 400} };
	int IndicatorH = -1;

	bool isEditing = false;
	size_t currentSelectNo_ = 0;
	std::vector<std::string>menuItems_;
	PeripheralReferenceTable_t peripheralReferenceTable_;
	PeripheralReferenceTable_t beforeKeyState_;	// 変更前

	KeyConfigScene() = default;
	KeyConfigScene(SceneController&);
	using DrawerFunction_t = void (KeyConfigScene::*)();
	DrawerFunction_t drawer_;

	using UpdateFunction_t = void (KeyConfigScene::*)(const Input&);
	UpdateFunction_t updater_;

	// updater
	void InUpdate(const Input& input);
	// 基本Updaters
	void NomalUpdate(const Input& input);

	void EditUpdate(const Input& input);
	// メニューを開く際のUpdater
	void OpenUpdate(const Input& input);
	// メニューを閉じる際のUpdater
	void CloseUpdate(const Input& input);

	// drawer
	// 基本drawer
	void NomalDraw();
	// 開閉する際のdrawer
	void OpenCloseDraw();

	/// <summary>
	/// メニューを閉じる
	/// </summary>
	void CloseMenu();

	/// <summary>
	/// string型からwstring型へ変更
	/// </summary>
	/// <param name="str">変更する文字列</param>
	/// <returns>wstring型になった文字列</returns>
	std::wstring GetWideStringFromString(const std::string str);

	/// <summary>
	/// エディットしたキーを反映させる
	/// </summary>
	/// <param name="input">入力情報</param>
	void CommitCurrentKeyConfig(const Input& input);
public:
	~KeyConfigScene();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力情報</param>
	void Update(const Input& input)override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

};

