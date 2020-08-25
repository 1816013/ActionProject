#include "ShurikenShot.h"
#include <DxLib.h>
#include "../Collision/Collider.h"
#include "../Camera.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"

namespace
{
	constexpr float angle_rate = 0.5f;
}

ShurikenShot::ShurikenShot(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera> c):
	Projectile(c)
{
	pos_ = pos;
	vel_ = vel;
	isActive_ = true;

	auto& fileMng = FileManager::Instance();
	if (shurikenH == -1)
	{
		shurikenH = fileMng.Load(L"Resource/Image/Player/shuriken.png")->Handle();
	}
	angle_ = 0.0f;
	updater_ = &ShurikenShot::NomalUpdate;
}

ShurikenShot::~ShurikenShot()
{
#ifdef _DEBUG
	OutputDebugStringA("\n shuriken is delete\n");
#endif // _DEBUG
}

void ShurikenShot::NomalUpdate()
{
	angle_ += angle_rate;
	Projectile::Update(); // java‚Ìbase.Update();
	auto viewRect = camera_->GetViewRange();
	if (pos_.x > viewRect.Right() || pos_.x < viewRect.Left() || pos_.y > viewRect.size.h || pos_.y < 0.0f)
	{
		updater_ = &ShurikenShot::DestroyUpdate;
	}
}
void ShurikenShot::DestroyUpdate()
{
	isActive_ = false;
}

void ShurikenShot::Update()
{
	(this->*updater_)();
}

void ShurikenShot::Draw()
{
	auto offset = camera_->ViewOffset();
	DrawRotaGraphF(pos_.x + offset.x, pos_.y,1.0f, angle_, shurikenH, true);
}

void ShurikenShot::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
	if (another.collider->GetTag() == tagEnemyDamage)
	{
		isActive_ = false;
	}
}
