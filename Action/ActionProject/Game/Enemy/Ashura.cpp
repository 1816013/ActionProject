#include "Ashura.h"
#include <DxLib.h>
#include "../Camera.h"
#include "../Collision/CircleCollider.h"

namespace
{
	constexpr float chichu_y = 1100.f;
	int ground_line;
	constexpr float	draw_scale = 0.5f;
}

Ashura::Ashura(GamePlayingScene* gs) :
	Boss(gs),
	updater_(&Ashura::EnteringUpdate),
	drawer_(&Ashura::NormalDraw)
{
	ashuraH_ = LoadGraph(L"Resource/Image/Enemy/Ashura/hotoke_asyura.png");
	circles_.emplace_back(Position2f(0, -400), 50);
	auto rc = camera_->GetViewRange();
	ground_line = rc.size.h - 16;
	pos_.x = rc.pos.x;
	pos_.y = chichu_y;
	life_ = 10000;
	isActive_ = true;
}

void Ashura::OnHit(CollisionInfo& colInfo)
{
	if (colInfo.collider->GetTag() == tagPlayerAtack)
	{
		OnDamage(1);
	}
}

void Ashura::OnDamage(int damage)
{
	updater_ = &Ashura::DamageUpdate;
	drawer_ = &Ashura::DamageDraw;
	frame_ = 8;
	life_ -= damage;
	if (life_ <= 0)
	{
		OnDead();
	}
}

void Ashura::OnDead()
{
	isDeletable_ = true;
}

void Ashura::Update()
{
	(this->*updater_)();
}

void Ashura::Draw()
{
	(this->*drawer_)();
}


void Ashura::EnteringUpdate()
{
	if (pos_.y <= ground_line)
	{
		updater_ = &Ashura::NomalUpdate;
		pos_.y = ground_line;
	}
	else
	{
		pos_.y -= 10;
	}
}

void Ashura::NomalUpdate()
{

}

void Ashura::DamageUpdate()
{
	if (--frame_ <= 0)
	{
		updater_ = &Ashura::NomalUpdate;
		drawer_ = &Ashura::NormalDraw;
	}
}

void Ashura::ExitingUpdate()
{
}

void Ashura::DeadUpdate()
{
}

void Ashura::NormalDraw()
{
	int w, h;
	GetGraphSize(ashuraH_, &w, &h);
	const auto xOffset = camera_->ViewOffset().x;
	DrawRotaGraph2(
		pos_.x + xOffset, pos_.y,
		w / 2, 800,
		draw_scale, 0.0f,
		ashuraH_, true);
	DrawFormatString(0, 200, 0xffffff, L"%d", life_);
}

void Ashura::DamageDraw()
{
	NormalDraw();
	SetDrawBlendMode(DX_BLENDMODE_ADD, 256);//â¡éZçáê¨
	NormalDraw();//í èÌï`âÊ
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Ashura::ExitingDraw()
{
}

void Ashura::DeadDraw()
{
}

Enemy* Ashura::MakeClone()
{
	return new Ashura(gameScene_);
}

const std::vector<Circle>& Ashura::GetCircles() const
{
	return circles_;
}
