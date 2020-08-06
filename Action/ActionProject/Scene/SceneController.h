#pragma once
#include <memory>
#include <deque>
#include <functional>

class Input;
class Application;
class Scene;
class SceneController
{
	friend class Application;
private:
	// �V�[���X�^�b�N(FIFO)���R���e�i���g������deque
	std::deque<std::shared_ptr<Scene>>scene_;	
	SceneController();
	// �V�[���؂�ւ��̎�Draw�̌�ɃV�[���؂�ւ��̊֐����ĂԂ��߂̂���
	// ���ʂɌĂяo���Ă���ƑO�̃V�[����Draw���Ăяo���ꂽ�肵��
	// �������Ⴂ���Ȃ����̂�������\��������
	std::function<void(void)> postDrawExecuter_;
	//std::shared_ptr<Scene>_scene;
public:		
	~SceneController() = default;
	/// <summary>
	/// �V�[���J��
	/// </summary>
	/// <param name="scene">���̃V�[��</param>
	void ChangeScene(Scene* scene);
	// �V�[���X�^�b�N�̐擪�ɐς�
	void PushScene(Scene* scene);
	// �V�[���X�^�b�N����擪����菜��
	void PopScene();
	// �V�[���X�^�b�N�ɐς܂�Ă�����̂����ׂăN���A���Ă���J�ڂ���
	// �O�̃V�[���͌ďo����ɍ폜����邽��,���̊֐��̌Ăяo�������폜�Ώۂ������ꍇ�ɂ́A�֐��Ăяo����ɏ������s���Ă͂Ȃ�Ȃ�
	void CleanChangeScene(Scene* scene);

	// �����Ă���擪�V�[����Update���Ă�
	void Update(const Input& input);

	// �V�[���X�^�b�N�ɐς܂�Ă��邷�ׂẴV�[����Draw���Ă�
	void Draw();

	void ClearScene();
};

