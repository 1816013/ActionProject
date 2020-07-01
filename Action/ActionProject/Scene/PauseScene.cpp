#include "PauseScene.h"
#include <DxLib.h>
#include "SceneController.h"
#include "../Input.h"

PauseScene::PauseScene(SceneController& c) : Scene(c)
{
}

void PauseScene::Update(const Input& input)
{
	if (input.IsTriggered("pause"))
	{
		controller_.PopScene();
	}
}

void PauseScene::Draw()
{
	DrawString(0, 0, L"PauseScene", 0xff0000);
}
