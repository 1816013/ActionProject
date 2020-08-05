#include "BombShot.h"
#include <DxLib.h>
#include "Projectile.h"
#include "../Camera.h"
#include "../../System/FileManager.h"

namespace
{
	int bombH = -1;
}
BombShot::BombShot(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera>c) : Projectile(c)
{
	pos_ = pos;
	vel_ = vel;
	auto& fileMng = FileManager::Instance();
	if (bombH == -1)
	{
		bombH = LoadGraph(L"Resource/Image/Player/bombshot2.png");
	}
	updater_ = &BombShot::NomalUpdate;
	isActive_ = true;
	angle_ = 0.0f;
}

BombShot::~BombShot()
{
#ifdef _DEBUG
	OutputDebugStringA("\n bomb is delete\n");
#endif // _DEBUG
}

void BombShot::NomalUpdate()
{
	angle_ += 0.5f;
	Projectile::Update(); // java‚Ìbase.Update();
	auto viewRect = camera_->GetViewRange();
	if (pos_.x > viewRect.Right() || pos_.x < viewRect.Left() || pos_.y > viewRect.Bottom() || pos_.y < viewRect.Top())
	{
		updater_ = &BombShot::DestroyUpdate;
	}
}

void BombShot::DestroyUpdate()
{
	isActive_ = false;
}

void BombShot::Update()
{
	(this->*updater_)();
}

void BombShot::Draw()
{
	auto offset = camera_->ViewOffset();
	DrawRotaGraph(pos_.x + offset.x, pos_.y, 0.5f, angle_, bombH, true);
}

void BombShot::OnHit(CollisionInfo& c)
{
	isActive_ = false;
}
