#include "ShurikenShot.h"
#include <DxLib.h>
#include "../Collider.h"

namespace
{
	int shurikenH = -1;
}

ShurikenShot::ShurikenShot(const Position2f& pos, const Vector2f& vel)
{
	pos_ = pos;
	vel_ = vel;
	isActive_ = true;
	if (shurikenH == -1)
	{
		shurikenH = LoadGraph(L"Resource/Image/Player/shuriken.png");
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
	angle_ += 0.5f;
	Projectile::Update(); // java‚Ìbase.Update();
	if (pos_.x > 800 || pos_.x < 0 || pos_.y > 600 || pos_.y < 0)
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
	DrawRotaGraph(pos_.x, pos_.y,1.0f, angle_, shurikenH, true);
}

void ShurikenShot::OnHit(CollisionInfo& info)
{
	if (info.collider->GetTag() == tagEnemyDamage)
	{
		isActive_ = false;
	}
}
