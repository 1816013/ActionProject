#include "Effect.h"
#include <DxLib.h>
#include "Camera.h"
#include "../System/FileManager.h"

namespace
{
	int blowH = -1;
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
	std::uniform_int_distribution<int> dst(random_min, random_max);
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, c));
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, c, 5));
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, c, 10));
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
	frame_ = 0.0f;
	pos_ = p;
	isTurn_ = isTurn_;
	delay_ = delay;
	auto& fileMng = FileManager::Instance();
	if (blowH == -1)
	{
		blowH = LoadGraph(L"Resource/Image/Effect/dron.png");
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
		DrawRectRotaGraph(pos_.x + offset.x, pos_.y,
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
