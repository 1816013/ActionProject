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

	void CloseMenu();

	std::wstring GetWideStringFromString(const std::string str);

	void CommitCurrentKeyConfig(const Input& input);
public:
	~KeyConfigScene();
	void Update(const Input&)override;
	void Draw()override;

};

