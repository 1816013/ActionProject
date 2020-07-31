#include "ChainEquip.h"
#include <DxLib.h>
#include <cmath>
#include "Player.h"
#include "../../Input.h"
#include "../CollisionManager.h"
#include "../CapsuleCollider.h"
#include "../../Camera.h"

namespace
{
	int chainH = -1;
	bool extensionF = false;
	Direction retDir;
}
void ChainEquip::NomalUpdate()
{
	if (frame_ < 0)
	{
		if (capsuleCollider_ != nullptr)
		{
			capsuleCollider_->GetCapsule().seg.vec = { 0, 0 };
		}
		return;
	}
	if (frame_ >= 0)
	{
		++frame_;
		if (frame_ > 40)
		{
			frame_ = -1;
			extensionF = false;
		}
		auto& vec = capsuleCollider_->GetCapsule().seg.vec;
		int f = abs((frame_ + 20) % 40 - 20);
		float w = (f * 400) / 20;
		vec = direction_ * w;
	}
}
void ChainEquip::ExtensionUpdate()
{
	if (++extensionFrame_ <= 20)
	{	
		auto variation = variationAngle;
		if (fabsf(variation) > DX_PI)
		{
			variation = (fabsf(variation) - DX_PI * 2) * -1.0f;
		}
		//retDir
		angle += variation / 20.0f;
	}
	else
	{
		frame_ = 40 - frame_;
		updater_ = &ChainEquip::NomalUpdate;
		extensionFrame_ = 0;
	}
	auto& vec = capsuleCollider_->GetCapsule().seg.vec;
	int f = abs((frame_ + 20) % 40 - 20);
	float w = (f * 400) / 20;
	vec = Vector2f(cos(angle), sin(angle)) * w;
}
ChainEquip::ChainEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm ,std::shared_ptr<Camera> c):
	player_(p),
	Equipment(cm, c),
	updater_(&ChainEquip::NomalUpdate)
{
	frame_ = -1;	// -1‚Å‰Šú‰»
	extensionFrame_ = 0;
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
	direction_.Nomarize();
	angle = atan2f(direction_.y, direction_.x);
	
	if (capsuleCollider_ == nullptr)
	{
		capsuleCollider_ = new CapsuleCollider(player_, { {{0, 0}, {0, 0}}, 20 }, tagPlayerAtack, true);
		collisionManager_->AddCollider(capsuleCollider_);
	}
	frame_ = 0;
	
}
void ChainEquip::ExtensionAttack(const Player& player, const Input& input)
{
	if (frame_ < 10  || extensionF)return;
	auto oldDir = direction_;
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
	direction_.Nomarize();
	if (direction_ == oldDir)return;
	variationAngle = atan2f(direction_.y, direction_.x);
	variationAngle -= angle;
	updater_ = &ChainEquip::ExtensionUpdate;
	retDir = player.Direction();
	extensionF = true;
}
void ChainEquip::Update()
{
	(this->*updater_)();
}

void ChainEquip::Draw()
{
	auto pos = player_->GetPosition();
	if (frame_ >= 0)
	{
		auto offset = camera_->ViewOffset();
		//angle = atan2f(direction_.y, direction_.x);
		int f = abs((frame_ + 20) % 40 - 20);
		int w = (f * 400) / 20;
		//DrawRectGraph(pos.x, pos.y, 400 - w, 0, w, 48, chainH, true);
		DrawRectRotaGraph2(pos.x + offset.x, pos.y, 400 - w, 0, w, 48, 0, 24,  1.0f, angle, chainH, true);
	}
}
