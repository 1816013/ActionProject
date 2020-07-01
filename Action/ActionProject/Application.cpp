#include "Application.h"
#include <DxLib.h>
#include "Scene/SceneController.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Geometry.h"

Size Viewport::GetSize() const
{
	Size ret = { 800, 600 };
	return ret;
}

bool Application::Initialize()
{	
	ChangeWindowMode(true);
	SetGraphMode(800, 600, 32);
	SetWindowText(L"");
	const auto& wsize = viewport_.GetSize();
	if (DxLib_Init())
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	sceneController_.reset(new SceneController());
	return true;
}

void Application::Run()
{
	Input input;
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();	
		
		input.Update();
		sceneController_->Update(input);
		sceneController_->Draw();
		ScreenFlip();
	}
}

void Application::Terminate()
{
	DxLib_End();
}

Application::~Application()
{
}

const Viewport& Application::GetViewport() const
{
	return viewport_;
}

Application::Application()
{

}
