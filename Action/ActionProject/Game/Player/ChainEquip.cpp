#include "ChainEquip.h"
#include <DxLib.h>
#include <cmath>
#include "Player.h"
#include "../../Input.h"

namespace
{
	int chainH = -1;
}
ChainEquip::ChainEquip(const Player& p): player_(p)
{
	frame_ = -1;
	if (chainH == -1)
	{
		chainH = LoadGraph(L"Resource/Image/Player/chainsickle.png");
	}
	
}

void ChainEquip::Attack(const Player& player, const Input& input)
{
	if (frame_ >= 0)return;
	direction_ = {};
	if (input.IsPressed("left"))
	{
		direction_ += {-1.0f, 0.0f};
	}
	if (input.IsPressed("right"))
	{
		direction_ += {1.0f, 0.0f};
	}
	if (input.IsPressed("up"))
	{
		direction_ += {0.0f, -1.0f};
	}
	if (input.IsPressed("down"))
	{
		direction_ += {0.0f, 1.0f};
	}
	// ‰½‚à‰Ÿ‚µ‚Ä‚¢‚È‚¢‚Æ‚«
	if (direction_.x == 0.0f && direction_.y == 0.0f)
	{
		if (player.Direction() == Direction::RIGHT)
		{
			direction_ = { 1.0, 0.0f };
		}
		if (player.Direction() == Direction::LEFT)
		{
			direction_ = { -1.0, 0.0f };
		}
	}
	frame_ = 0;
}

void ChainEquip::Update()
{
	if (frame_ >= 0)
	{
		++frame_;
		if (frame_ > 40)
		{
			frame_ = -1;
		}
	}
}

void ChainEquip::Draw()
{
	auto pos = player_.Position();
	if (frame_ >= 0)
	{
		auto angle = atan2f(direction_.y, direction_.x);
		int f = abs((frame_ + 20) % 40 - 20);
		int w = (f * 400) / 20;
		//DrawRectGraph(pos.x, pos.y, 400 - w, 0, w, 48, chainH, true);
		DrawRectRotaGraph2(pos.x, pos.y, 400 - w, 0, w, 48, 0, 24,  1.0f, angle, chainH, true);
	}
}
