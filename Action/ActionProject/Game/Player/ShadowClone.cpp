#include "ShadowClone.h"
#include <DxLib.h>
#include "Player.h"
#include "../Camera.h"

ShadowClone::ShadowClone(Player* player, std::shared_ptr<Camera> camera) : player_(player), camera_(camera)
{
}

void ShadowClone::Update(Position2f pos)
{
	pos_ = pos;
}

void ShadowClone::Draw()
{
	auto offset = camera_->ViewOffset();
	DrawCircleAA(pos_.x + offset.x, pos_.y, 10, 0, 0xff0000, true);
}
