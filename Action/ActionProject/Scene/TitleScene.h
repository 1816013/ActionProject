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
	///  �^�C�g���V�[���̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	void TitleUpdate(const Input& input);

	/// <summary>
	/// �����̓_�ł������Ȃ�ۂ̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	void FastBlinkUpdate(const Input& input);

	/// <summary>
	///  �t�F�[�h�A�E�g���s���̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	void FadeoutUpdate(const Input& input);

	/// <summary>
	/// �t�F�[�h�C�����s���̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	void FadeinUpdate(const Input& input);
	using UpdateFunction_t = void (TitleScene::*)(const Input&);
	UpdateFunction_t updater_;

	// Drawer
	/// <summary>
	/// �^�C�g���V�[���̕`��
	/// </summary>
	void NomalDraw();

	/// <summary>
	/// �t�F�[�h���̕`��
	/// </summary>
	void FadeDraw();
	using DrawerFunction_t = void (TitleScene::*)();
	DrawerFunction_t drawer_;
	
public:
	~TitleScene();
	
	void Update(const Input&)override;
	void Draw()override;
};

