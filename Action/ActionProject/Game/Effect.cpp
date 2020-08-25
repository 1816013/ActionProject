#include "Effect.h"
#include <DxLib.h>
#include "Camera.h"
#include "../System/FileManager.h"
#include "../System/File.h"

namespace
{
	constexpr int random_min = -10;
	constexpr int random_max = 10;
	constexpr int effect_blow_x = 32;
	constexpr int effect_blow_y = 32;
}

void EffectManager::EmitBlood(const Position2f& p, bool isTurn, std::shared_ptr<Camera>c)
{
	//effects_.emplace_back
}

void EffectManager::EmitBlow3(const Position2f& p, bool isTurn, std::shared_ptr<Camera>c)
{
	std::uniform_real_distribution<float> dst(random_min, random_max);
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, c));
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, c, 5));
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, c, 10));
}

void EffectManager::EmitGroundExprotion(const Position2f& p, std::shared_ptr<Camera> c)
{
	effects_.emplace_back(new GroundExprotion(p, c));
}

void EffectManager::EmitEnergyBall(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c)
{
	effects_.emplace_back(new EnergyBall(p,isTurn, c));
}

void EffectManager::EmitBulletExprode(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c)
{
	effects_.emplace_back(new BulletExprode(p, isTurn, c));
}

void EffectManager::Update()
{
	for (auto e : effects_)
	{
		e->Update();
	}
	effects_.remove_if([](std::shared_ptr<Effect>e) { return e->IsDeletable(); });
}

void EffectManager::Draw()
{
	for (auto e : effects_)
	{
		e->Draw();
	}
}

Blood::Blood(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c) : Effect(c)
{
	pos_ = p;
	isTurn_ = isTurn;
}

void Blood::Update()
{
	++frame_;
}

void Blood::Draw()
{
}


Blow::Blow(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c, float delay) : Effect(c)
{
	frame_ = 0;
	pos_ = p;
	isTurn_ = isTurn_;
	delay_ = delay;
	auto& fileMng = FileManager::Instance();
	if (blowH == -1)
	{
		blowH = fileMng.Load(L"Resource/Image/Effect/dron.png")->Handle();
	}
}

void Blow::Update()
{
	frame_ = (frame_ + 1) % 24;
	if (frame_ == 0)
	{
		isDeleatable = true;
	}

}

void Blow::Draw()
{
	if (delay_ < frame_)
	{
		auto offset = camera_->ViewOffset();
		DrawRectRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y),
			((frame_ / 3)) * effect_blow_x, 0,
			effect_blow_x, effect_blow_y, 
			2.0f,0.0f,
			blowH, true, isTurn_);
	}
}

Effect::Effect(std::shared_ptr<Camera> c) : camera_(c)
{
}

bool Effect::IsDeletable()
{
	return isDeleatable;
}

GroundExprotion::GroundExprotion(const Position2f& p, std::shared_ptr<Camera> c) : Effect(c)
{
	pos_ = p;
	if (groundExprotionH == -1)
	{
		auto& fileMng = FileManager::Instance();
		
		groundExprotionH = fileMng.Load(L"Resource/Image/Effect/ground_exp.png")->Handle();
	}
}

void GroundExprotion::Update()
{
	frame_ = (frame_ + 1) % 30;
	if (frame_ == 0)
	{
		isDeleatable = true;
	}
}

void GroundExprotion::Draw()
{
	auto offset = camera_->ViewOffset();
	DrawRectRotaGraphF(pos_.x + offset.x, pos_.y - 40, 
		((frame_ / 3)) * 128, 0, 
		128, 80,
		1.0f,0.0f, 
		groundExprotionH, true);
}

EnergyBall::EnergyBall(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c) : Effect(c)
{
	pos_ = p;
	isTurn_ = isTurn;
	frame_ = 0;
	auto& fileMng = FileManager::Instance();
	energyBallH =  fileMng.Load(L"Resource/Image/Effect/chargeball.png")->Handle();
}

void EnergyBall::Update()
{
	frame_ = (frame_ + 1) % 30;
	if (frame_ == 0)
	{
		isDeleatable = true;
	}
}

void EnergyBall::Draw()
{
	auto offset = camera_->ViewOffset();
	int idx_x = frame_ % 6;
	int idx_y =  frame_ % 5 / 6 ;
	DrawRectRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y),
		idx_x * 100, idx_y * 100,
		100, 100,
		1.0f, 0.0f,
		energyBallH, true);
}

BulletExprode::BulletExprode(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c) : Effect(c)
{
	pos_ = p;

	if (bulletExprodeH == -1)
	{
		auto& fileMng = FileManager::Instance();
		bulletExprodeH = fileMng.Load(L"Resource/Image/Effect/eliminate_b.png")->Handle();
	}
}

void BulletExprode::Update()
{
	frame_ = (frame_ + 1) % 32;
	if (frame_ == 0)
	{
		isDeleatable = true;
	}
}

void BulletExprode::Draw()
{
	auto offset = camera_->ViewOffset();
	DrawRectRotaGraph(static_cast<int>(pos_.x + offset.x),static_cast<int>(pos_.y),
		(frame_ / 4) * 32, 0,
		32, 32,
		1.0f, 0.0f,
		bulletExprodeH, true);
}
