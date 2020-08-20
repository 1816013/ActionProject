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
	PeripheralReferenceTable_t beforeKeyState_;	// �ύX�O

	KeyConfigScene() = default;
	KeyConfigScene(SceneController&);
	using DrawerFunction_t = void (KeyConfigScene::*)();
	DrawerFunction_t drawer_;

	using UpdateFunction_t = void (KeyConfigScene::*)(const Input&);
	UpdateFunction_t updater_;

	// updater
	void InUpdate(const Input& input);
	// ��{Updaters
	void NomalUpdate(const Input& input);

	void EditUpdate(const Input& input);
	// ���j���[���J���ۂ�Updater
	void OpenUpdate(const Input& input);
	// ���j���[�����ۂ�Updater
	void CloseUpdate(const Input& input);

	// drawer
	// ��{drawer
	void NomalDraw();
	// �J����ۂ�drawer
	void OpenCloseDraw();

	/// <summary>
	/// ���j���[�����
	/// </summary>
	void CloseMenu();

	/// <summary>
	/// string�^����wstring�^�֕ύX
	/// </summary>
	/// <param name="str">�ύX���镶����</param>
	/// <returns>wstring�^�ɂȂ���������</returns>
	std::wstring GetWideStringFromString(const std::string str);

	/// <summary>
	/// �G�f�B�b�g�����L�[�𔽉f������
	/// </summary>
	/// <param name="input">���͏��</param>
	void CommitCurrentKeyConfig(const Input& input);
public:
	~KeyConfigScene();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	void Update(const Input& input)override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;

};

