#include "ChainEquip.h"
#include <DxLib.h>
#include <cmath>
#include "Player.h"
#include "../../System/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CapsuleCollider.h"
#include "../Camera.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"
#include "../../Arithmetic.h"

namespace
{
	bool extensionF = false;
	Direction retDir;

	constexpr int attack_frame = 24;
	constexpr int expand_frame = attack_frame / 2;
	constexpr int chain_length = 400;
	constexpr int chain_y = 48;
	constexpr float radian360 = DX_PI_F * 2;
}
void ChainEquip::NomalUpdate()
{
	if (frame_ < 0)
	{
		if (capsuleCollider_ != nullptr)
		{
			capsuleCollider_->GetCapsule().seg.vec = Vector2f::ZERO;
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
		vec = direction_ * static_cast<float>(ExpandWidth());
	}
}
void ChainEquip::ExtensionUpdate()
{
	if (++extensionFrame_ <= expand_frame)
	{	
		angle += variationAngle / expand_frame;
	}
	else
	{
		updater_ = &ChainEquip::NomalUpdate;
		extensionFrame_ = 0;
	}
	auto& vec = capsuleCollider_->GetCapsule().seg.vec;
	vec = Vector2f(cos(angle), sin(angle)) * static_cast<float>(ExpandWidth());
}
ChainEquip::ChainEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm ,std::shared_ptr<Camera> c):
	player_(p),
	Equipment(cm, c),
	updater_(&ChainEquip::NomalUpdate)
{
	frame_ = -1;	// -1で初期化
	extensionFrame_ = 0;
	auto& fileMng = FileManager::Instance();
	if (chainH == -1)
	{
		chainH = fileMng.Load(L"Resource/Image/Player/chainsickle.png")->Handle();
	}
}

void ChainEquip::Attack(const Player& player, const Input& input, Vector2f offset)
{
	if (frame_ >= 0)return;
	
	direction_ = {};
	SetDirection(input, player);
	angle = atan2f(direction_.y, direction_.x);
	retDir = player.Direction();
	
	if (capsuleCollider_ == nullptr)
	{
		capsuleCollider_ = new CapsuleCollider(player_, { {{0, 0}, {0, 0}}, 20 }, tagPlayerAtack, true);
		collisionManager_->AddCollider(capsuleCollider_);
	}
	frame_ = 0;
	
}
void ChainEquip::ExtensionAttack(const Player& player, const Input& input)
{
	if (frame_ < expand_frame || extensionF)return;
	auto oldDir = direction_;
	SetDirection(input, player);
	if (direction_ == oldDir)return;
	variationAngle = atan2f(direction_.y, direction_.x);
	if (retDir == Direction::RIGHT)
	{
		if (variationAngle > 0)
		{
			variationAngle = -radian360 + variationAngle;
		}
	}
	else
	{
		variationAngle = variationAngle + radian360;
	}
	variationAngle -= angle;
	if (fabs(variationAngle) > radian360)
	{
		variationAngle = (fabs(variationAngle) - radian360) * Sign(variationAngle);
	}
	updater_ = &ChainEquip::ExtensionUpdate;
	
	extensionF = true;
}

void ChainEquip::SetDirection(const Input& input, const Player& player)
{
	direction_ = {};
	if (input.IsPressed("left"))
	{
		direction_ += Vector2f::LEFT;
	}
	if (input.IsPressed("right"))
	{
		direction_ += Vector2f::RIGHT;
	}
	if (input.IsPressed("up"))
	{
		direction_ += Vector2f::UP;
	}
	if (input.IsPressed("down"))
	{
		direction_ += Vector2f::DOWN;
	}
	// 何も押していないとき
	if (direction_ == Vector2f::ZERO)
	{
		if (player.Direction() == Direction::RIGHT)
		{
			direction_ = Vector2f::RIGHT;
		}
		if (player.Direction() == Direction::LEFT)
		{
			direction_ = Vector2f::LEFT;
		}
	}
	direction_.Nomarize();
}
int ChainEquip::ExpandWidth()
{
	int f = abs((frame_ + (expand_frame)) % attack_frame - (expand_frame));
	return (f * chain_length) / (expand_frame);
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
		int w = ExpandWidth();
		DrawRectRotaGraph2(
			static_cast<int>(pos.x + offset.x), static_cast<int>(pos.y),
			chain_length - w, 0,
			w, chain_y, 0, chain_y / 2, 
			1.0f, angle,
			chainH, true);
	}
}
