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
	// �^�C�g���V�[���̊�{Updater
	void TitleUpdate(const Input&);
	// �����̓_�ł������Ȃ�Updater
	void FastBlinkUpdate(const Input&);
	// �t�F�[�h�A�E�g���s����Updater
	void FadeoutUpdate(const Input&);

	void FadeinUpdate(const Input&);
	using UpdateFunction_t = void (TitleScene::*)(const Input&);
	UpdateFunction_t updater_;

	// Drawer
	// �^�C�g���V�[���̊�{�`��
	void NomalDraw();
	// �t�F�[�h���̕`��
	void FadeDraw();
	using DrawerFunction_t = void (TitleScene::*)();
	DrawerFunction_t drawer_;
	
public:
	~TitleScene();
	
	void Update(const Input&)override;
	void Draw()override;
};

