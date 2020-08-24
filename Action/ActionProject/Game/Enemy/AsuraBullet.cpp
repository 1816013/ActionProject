#include "AsuraBullet.h"
#include <DxLib.h>
#include "../../System/FileManager.h"
#include "../../System/File.h"
#include "../Camera.h"
#include <random>
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"
#include "../Effect.h"

namespace
{
	int bulletH = -1;
	std::mt19937 mt_(1);
}
AsuraBullet::AsuraBullet(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera> c,std::shared_ptr<EffectManager> effectManager) : Projectile(c)
{
	pos_ = pos;
	vel_ = vel;
	initVel_ = vel;
	speed_ = vel.Magnitude();
	effectManager_ = effectManager;
	centripetalSpeed_ = 0.5f;
	isActive_ = true;
	if (bulletH == -1)
	{
		auto& fileMng = FileManager::Instance();
		bulletH = fileMng.Load(L"Resource/Image/Enemy/Ashura/fireball_b.png")->Handle();
	}

}

void AsuraBullet::Update()
{
	auto viewRect = camera_->GetViewRange();
	if (pos_.x > viewRect.Right() || pos_.x < viewRect.Left() || pos_.y > viewRect.size.h || pos_.y < 0.0f)
	{
		isActive_ = false;
	}
	Vector2f centripetalVel(-vel_.x, vel_.y);
	centripetalVel.Nomarize();
	centripetalVel *= centripetalSpeed_;
	//vel_ = vel_ + (vel_ + centripetalVel).Nomarized();
	Projectile::Update();
}

void AsuraBullet::Draw()
{
	float angle = atan2f(vel_.y, vel_.x);
	auto offset = camera_->ViewOffset();
	DrawRectRotaGraph(
		pos_.x + offset.x, pos_.y,
		0, 0,
		64, 32,
		1.0f, angle,
		bulletH, true);
}

void AsuraBullet::OnHit(CollisionInfo& colInfo)
{
	if (colInfo.collider->GetTag() == tagPlayerDamage)
	{
		// Ž€‚Ê
		effectManager_->EmitBulletExprode(pos_, false, camera_);
		isActive_ = false;
	}
}
