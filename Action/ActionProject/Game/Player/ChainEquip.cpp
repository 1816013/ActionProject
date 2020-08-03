#include "ChainEquip.h"
#include <DxLib.h>
#include <cmath>
#include "Player.h"
#include "../../System/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CapsuleCollider.h"
#include "../Camera.h"

namespace
{
	int chainH = -1;
	bool extensionF = false;
	Direction retDir;

	constexpr int attack_frame = 40;
	constexpr int chain_length = 400;
	constexpr int chain_y = 48;
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
		if (frame_ > attack_frame)
		{
			frame_ = -1;
			extensionF = false;
		}
		auto& vec = capsuleCollider_->GetCapsule().seg.vec;
		int f = abs((frame_ + (attack_frame / 2)) % attack_frame - (attack_frame / 2));
		float w = (f * chain_length) / (attack_frame / 2);
		vec = direction_ * w;
	}
}
void ChainEquip::ExtensionUpdate()
{
	if (++extensionFrame_ <= attack_frame / 2)
	{	
		auto variation = variationAngle;
		if (fabsf(variation) > DX_PI)
		{
			variation = (fabsf(variation) - DX_PI * 2) * -1.0f;
		}
		angle += variation / (attack_frame / 2);
	}
	else
	{
		frame_ = attack_frame - frame_;
		updater_ = &ChainEquip::NomalUpdate;
		extensionFrame_ = 0;
	}
	auto& vec = capsuleCollider_->GetCapsule().seg.vec;
	int f = abs((frame_ + (attack_frame / 2)) % attack_frame - (attack_frame / 2));
	float w = (f * chain_length) / (attack_frame / 2);
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
	SetDirection(input, player);
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
	SetDirection(input, player);
	if (direction_ == oldDir)return;
	variationAngle = atan2f(direction_.y, direction_.x);
	variationAngle -= angle;
	updater_ = &ChainEquip::ExtensionUpdate;
	retDir = player.Direction();
	extensionF = true;
}

void ChainEquip::SetDirection(const Input& input, const Player& player)
{
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
		int f = abs((frame_ + (attack_frame / 2)) % attack_frame - (attack_frame / 2));
		int w = (f * chain_length) / (attack_frame / 2);
		DrawRectRotaGraph2(pos.x + offset.x, pos.y, chain_length - w, 0, w, chain_y, 0, chain_y / 2,  1.0f, angle, chainH, true);
	}
}
