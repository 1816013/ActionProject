#pragma once
#include <memory>

// �A�v���P�[�V�����N���X
// ���ׂĂ̂������ƂɂȂ�N���X
class SceneController;
struct Size;


// �\�����ׂ���ʂ̏�������
class Viewport
{
public:
//	Viewport();
	Size GetSize() const;
};

class Application
{
private:
	Viewport viewport_;
	std::unique_ptr<SceneController>sceneController_;
	// �R���X�g���N�^��private
	Application();
	// ����A�R�s�[�̋֎~
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;
public:	
	// ����
	static Application& Instance()
	{
		static Application app;
		return app;
	}

	// ������
	bool Initialize();
	// ���s
	void Run();
	// �I������
	void Terminate();
	~Application();

	const Viewport& GetViewport()const;

};
// �R���X�g���N�^�ƃf�X�g���N�^��unique_ptr�̂�ŃC�����C���ɂł��Ȃ�

