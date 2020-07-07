#include "BombShot.h"
#include <DxLib.h>
#include "Projectile.h"

namespace
{
	int bombH = -1;
}
BombShot::BombShot(const Position2& pos, const Vector2f& vel)
{
	pos_ = pos;
	vel_ = vel;
	if (bombH == -1)
	{
		bombH = LoadGraph(L"Resourse/Image/Player/bombshot2.png");
		//bombH = LoadGraph(L"Resourse/Image/Title/pressstart.png");
	}
	updater_ = &BombShot::NomalUpdate;
	isActive_ = true;
	angle_ = 0.0f;
}

BombShot::~BombShot()
{
	OutputDebugStringA("\n bomb is delete\n");
}

void BombShot::NomalUpdate()
{
	angle_ += 0.5f;
	Projectile::Update(); // java‚Ìbase.Update();
	if (pos_.x > 800 || pos_.x < 0 || pos_.y > 600 || pos_.y < 0)
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
	DrawRotaGraph(pos_.x, pos_.y, 0.5f, angle_, bombH, true);
}
