#pragma once
#include <memory>
#include <deque>
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
	//std::shared_ptr<Scene>_scene;
public:		
	~SceneController() = default;
	// �V�[���J�ځ@
	void ChangeScene(Scene*);
	// �V�[���X�^�b�N�̐擪�ɐς�
	void PushScene(Scene*);
	// �V�[���X�^�b�N����擪����菜��
	void PopScene();
	// �V�[���X�^�b�N�ɐς܂�Ă�����̂����ׂăN���A���Ă���J�ڂ���
	// �O�̃V�[���͌ďo����ɍ폜����邽��,���̊֐��̌Ăяo�������폜�Ώۂ������ꍇ�ɂ́A�֐��Ăяo����ɏ������s���Ă͂Ȃ�Ȃ�
	void CleanChangeScene(Scene*);

	// �����Ă���擪�V�[����Update���Ă�
	void Update(const Input&);

	// �V�[���X�^�b�N�ɐς܂�Ă��邷�ׂẴV�[����Draw���Ă�
	void Draw();
};

