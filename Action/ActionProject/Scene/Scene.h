#pragma once
class Input;
class SceneController;
// �V�[�����N���X
class Scene
{
	friend SceneController;
protected:
	SceneController& controller_;
	Scene(SceneController&);
	Scene() = default;
public:
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;
	virtual ~Scene() = default;
};

