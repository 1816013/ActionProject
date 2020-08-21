#include "Ashura.h"
#include <DxLib.h>
#include "../Camera.h"
#include "../Collision/CircleCollider.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"

namespace
{
	constexpr float chichu_y = 1100.f;
	int ground_line;
	constexpr float	draw_scale = 1.2f;
}

Ashura::Ashura(GamePlayingScene* gs) :
	Boss(gs),
	updater_(&Ashura::EnteringUpdate),
	drawer_(&Ashura::NormalDraw)
{
	auto& fileMng = FileManager::Instance();
	ashuraH_ = fileMng.Load(L"Resource/Image/Enemy/Ashura/ashura.png")->Handle();
	circles_.emplace_back(Position2f(0, -400), 50);
	auto rc = camera_->GetViewRange();
	ground_line = rc.size.h - 16 - 32 * 2;
	pos_.x = rc.pos.x;
	pos_.y = chichu_y;
	life_ = 10;
	isActive_ = true;
}

void Ashura::OnHit(CollisionInfo& colInfo)
{
	if (colInfo.collider->GetTag() == tagPlayerAtack)
	{
		if (updater_ == &Ashura::NomalUpdate)
		{
			OnDamage(1);
		}
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
	updater_ = &Ashura::ExitingUpdate;
	drawer_ = &Ashura::ExitingDraw;
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
		pos_.y -= 3;
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
	if (pos_.y >= chichu_y)
	{
		updater_ = &Ashura::DeadUpdate;
		pos_.y = chichu_y;
	}
	else
	{
		pos_.y += 3;
	}
}

void Ashura::DeadUpdate()
{
	isDeletable_ = true;
	isActive_ = false;
}

void Ashura::NormalDraw()
{
	int w, h;
	GetGraphSize(ashuraH_, &w, &h);
	const auto xOffset = camera_->ViewOffset().x;
	DrawRotaGraph2(
		pos_.x + xOffset, pos_.y,
		w / 2, 400,
		draw_scale, 0.0f,
		ashuraH_, true);
	DrawFormatString(0, 200, 0xffffff, L"%d", life_);
	DrawCircle(pos_.x, pos_.y, 10, 0x00ff00, true);
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
	NormalDraw();
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
