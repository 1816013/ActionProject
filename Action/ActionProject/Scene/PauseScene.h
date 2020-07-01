#pragma once
#include "Scene.h"

class GamePlayingScene;
class PauseScene : public Scene
{
	friend GamePlayingScene;
private:
	PauseScene() = default;
	PauseScene(SceneController&);
public:
	void Update(const Input&)override;
	void Draw()override;

};

