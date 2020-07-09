#include "ShurikenShot.h"
#include <DxLib.h>

namespace
{
	int shurikenH = -1;
}

ShurikenShot::ShurikenShot(const Position2& pos, const Vector2f& vel)
{
	pos_ = pos;
	vel_ = vel;

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
	isActive_ = true;
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
	DrawGraph(pos_.x, pos_.y, shurikenH, true);
}
