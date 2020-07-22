#include "Camera.h"
#include <DxLib.h>
#include "Game/Player/Player.h"
#include "Application.h"
#include <algorithm>

Camera::Camera()
{
	stageSize_ = { 800, 600 };
}

void Camera::SetPlayer(std::shared_ptr<Player> player)
{
	player_ = player;

}

void Camera::SetStageSize(const Size& size)
{
	stageSize_ = size;
}

void Camera::Update()
{
	auto& app = Application::Instance();
	auto& viewPort = app.GetViewport();
	const auto& cameraSize = viewPort.GetSize();
	pos_ = player_->GetPosition();
	pos_.x = std::clamp(pos_.x, 0 + cameraSize.w / 2.0f, stageSize_.w - cameraSize.w / 2.0f);
}

const Position2f& Camera::GetPosition() const
{
	return pos_;
}

const Rect Camera::GetViewRange() const
{
	return Rect(pos_, stageSize_);
}

const Vector2f Camera::ViewOffset() const
{
	return Vector2f(-pos_.x, -pos_.y);
}
