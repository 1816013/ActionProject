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
	std::deque<std::shared_ptr<Scene>>scene_;
	SceneController();
	//std::shared_ptr<Scene>_scene;
public:		
	~SceneController() = default;
	void ChangeScene(Scene*);
	void PushScene(Scene*);
	void PopScene();
	void Update(const Input&);
	void Draw();
};

