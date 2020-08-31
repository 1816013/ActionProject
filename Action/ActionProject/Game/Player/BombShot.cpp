#include "BombShot.h"
#include <DxLib.h>
#include "../Projectile.h"
#include "../Camera.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/Collider.h"

namespace
{
	int exprotionH_ = -1;
}

BombShot::BombShot(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera>c) : Projectile(c)
{
	pos_ = pos;
	vel_ = vel;
	auto& fileMng = FileManager::Instance();
	if (bombH == -1)
	{
		bombH = fileMng.Load(L"Resource/Image/Equipment/bombshot2.png")->Handle();
	}
	if (exprotionH_)
	{
		exprotionH_ = fileMng.Load(L"Resource/Image/Effect/bomb_prj_exp.png")->Handle();
	}
	updater_ = &BombShot::NomalUpdate;
	drawer_ = &BombShot::NomalDraw;
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
	if (pos_.x > viewRect.Right() || pos_.x < viewRect.Left() || pos_.y > viewRect.size.h || pos_.y < 0.0f)
	{
		isActive_ = false;
	}
}

void BombShot::ExprotionUpdate()
{
	if (--frame_ == 0)
	{
		isActive_ = false;
	}
}

void BombShot::NomalDraw()
{
	auto offset = camera_->ViewOffset();
	DrawRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y),
		0.5f, angle_,
		bombH, true);
}

void BombShot::ExprotionDraw()
{
	auto offset = camera_->ViewOffset();
	DrawRectRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y),
		(frame_ / 8) * 48, 0,
		48,48,
		3.0f, 0.0f,
		exprotionH_, true);
}

void BombShot::Update()
{
	(this->*updater_)();
}

void BombShot::Draw()
{
	(this->*drawer_)();
	
}

void BombShot::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
	if (another.collider->GetTag() == tagEnemyDamage && frame_ == 0)
	{
		updater_ = &BombShot::ExprotionUpdate;
		drawer_ = &BombShot::ExprotionDraw;
		frame_ = 40;
	}
}
