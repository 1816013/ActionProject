#include "Ashura.h"
#include <DxLib.h>
#include "../Camera.h"
#include "../Collision/CircleCollider.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"
#include "../Effect.h"
#include <random>
#include "AsuraBullet.h"
#include "../ProjectileManager.h"
#include "../../Scene/GamePlayingScene.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"



namespace
{
	constexpr float chichu_y = 1100.f;
	float ground_line;
	constexpr float	draw_scale = 1.2f;
	std::mt19937 mt_(1);
	std::uniform_int_distribution<int> dst(60, 120);
	std::uniform_int_distribution<int> bulletAngleRange(4, 10);
}

Ashura::Ashura(GamePlayingScene* gs) :
	Boss(gs),
	updater_(&Ashura::EnteringUpdate),
	drawer_(&Ashura::NormalDraw)
	
{
	auto& fileMng = FileManager::Instance();
	ashuraH_ = fileMng.Load(L"Resource/Image/Enemy/Ashura/ashura.png")->Handle();
	circles_.emplace_back(Position2f(0.0f, -400.0f), 50.0f);
	auto rc = camera_->GetViewRange();
	ground_line = rc.size.h - 16.0f- 32.0f * 2.0f;
	pos_.x = rc.pos.x;
	pos_.y = chichu_y;
	life_ = 10;
	isActive_ = true;
	
	for (auto e : energyBalls_)
	{
		e.frame = dst(mt_);
	}
}

void Ashura::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
	if (another.collider->GetTag() == tagPlayerAtack)
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
	for (int i = 0; i < energyBalls_.size(); ++i) {
		if (--energyBalls_[i].frame <= 0) {
			energyBalls_[i].frame = dst(mt_);
			auto pos = energyBalls_[i].pos + pos_;
			effectManager_->EmitEnergyBall(pos, false, camera_);
			float angle = static_cast<float>(bulletAngleRange(mt_));
			for (int i = 0; i < 8; ++i) {
				Vector2f vel(cosf(angle), sinf(angle));
				vel *= 4.0f;
				auto& pm = gameScene_->GetProjectileManager();
				pm.AddProjectile(new AsuraBullet(pos + vel, vel, camera_, gameScene_->GetEffectMng()));
				auto colMgr = gameScene_->GetCollisionManager();
				colMgr->AddCollider(new CircleCollider(pm.Projectiles().back(), tagEnemyBullet, Circle({ 0.0f, 0.0f }, 5.0f)));
				angle += DX_PI_F / 4.0f;
			}
		}
	}
	
	
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
		static_cast<int>(pos_.x + xOffset), static_cast<int>(pos_.y),
		w / 2, h,
		draw_scale, 0.0f,
		ashuraH_, true);
	DrawFormatString(0, 200, 0xffffff, L"%d", life_);
	//DrawCircle(pos_.x + xOffset, pos_.y, 10, 0x00ff00, true);
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
	int w;
	GetGraphSize(ashuraH_, &w, nullptr);
	auto randW = (rand() % w) - w / 2;
	effectManager_->EmitGroundExprotion({ pos_.x + randW, ground_line }, camera_);
	NormalDraw();
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 128);
	NormalDraw();//í èÌï`âÊ
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
