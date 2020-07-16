#include "Effect.h"
#include <DxLib.h>

namespace
{
	int blowH = -1;
}

void EffectManager::EmitBlood(const Position2f& p, bool isTurn)
{
	//effects_.emplace_back
}

void EffectManager::EmitBlow3(const Position2f& p, bool isTurn)
{
	std::uniform_int_distribution<int> dst(-10, 10);
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn));
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn, 5));
	effects_.emplace_back(new Blow(p + Vector2f(dst(mt_), dst(mt_) * 2.0f), isTurn,10));
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

Blood::Blood(const Position2f& p, bool isTurn)
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


Blow::Blow(const Position2f& p, bool isTurn
, float delay)
{
	frame_ = 0.0f;
	pos_ = p;
	isTurn_ = isTurn_;
	delay_ = delay;
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
		DrawRectRotaGraph(pos_.x, pos_.y, ((frame_ / 3)) * 32, 0, 32, 32, 2.0f, 0.0f, blowH, true, isTurn_);
	}
}

bool Effect::IsDeletable()
{
	return isDeleatable;
}
