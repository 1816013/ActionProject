#include "SwordEquip.h"
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
#include "ShadowClone.h"
#include "../../System/Application.h"

namespace
{
	Direction retDir;

	constexpr int attack_frame = 24;
	constexpr int expand_frame = attack_frame / 2;
	constexpr int chain_length = 400;
	constexpr int chain_y = 48;
	constexpr float radian360 = DX_PI_F * 2;
	float angle_;
	float dist_;
	int captureH_;
	int psH_ = -1;
	int normalH_ = -1;
	SlashShape slash_({ 400.0f, 300.0f }, { -125.0f, -125.0f }, 0);


	constexpr int slash_frame = 30;
	constexpr float slash_target_rad = 45 * (DX_PI_F / 180);
	constexpr float slash1_speed = slash_target_rad / slash_frame;
	constexpr float slash2_speed = slash_target_rad / slash_frame;
	constexpr float slash1_Decay_rate = slash1_speed / slash_frame * 2;
	constexpr float slash2_Decay_rate = slash2_speed / slash_frame;

	float slash1Speed = slash_target_rad / slash_frame / 2;	// 始端スピード
	float slash2Speed = slash_target_rad / slash_frame;	// 終端スピード
}
void SwordEquip::NomalUpdate()
{
	if (--frame_ >= 0)
	{
		slash_.center = player_->GetPosition();
		slash_.AddAngle1(slash1Speed);
		slash_.AddAngle2(slash2Speed);
		//slash1Speed -= slash1_Decay_rate;
		//slash2Speed -= slash2_Decay_rate;
		if (frame_ == 0)
		{
			slash_.SetAngle1(0.0f);
			slash_.SetAngle2(0.0f);
			frame_ = -1;
			

		}
	}
}
SwordEquip::SwordEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c, ShadowClone* shadow) :
	player_(p),
	Equipment(cm, c),
	shadow_(shadow),
	updater_(&SwordEquip::NomalUpdate)
{
	frame_ = -1;	// -1で初期化
	extensionFrame_ = 0;
	auto& fileMng = FileManager::Instance();
	if (chainH == -1)
	{
		chainH = fileMng.Load(L"Resource/Image/Equipment/chainsickle.png")->Handle();
	}
	auto& rc = Application::Instance().GetViewport();
	captureH_ = MakeScreen(rc.GetSize().w, rc.GetSize().h);
	if (psH_ == -1)
	{
		psH_ = LoadPixelShader(L"Resource/Etc/testps.pso");
	}
	if (normalH_ == -1)
	{
		normalH_ = fileMng.Load(L"Resource/Etc/normal.png")->Handle();
	}
}

void SwordEquip::Attack(const Player& player, const Input& input, Vector2f offset)
{
	if (frame_ >= 0)return;

	if (capsuleCollider_ == nullptr)
	{
		capsuleCollider_ = new CapsuleCollider(player_, { {offset,offset}, 20 }, tagPlayerAtack, true);
		collisionManager_->AddCollider(capsuleCollider_);
	}
	frame_ = slash_frame;
	slash_.SetAngle1(0);
	slash_.SetAngle2(0);

}

void SwordEquip::SetDirection(const Input& input, const Player& player)
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

void SwordEquip::Update()
{
	if (shadow_ != nullptr && capsuleCollider_ != nullptr)
	{
		offset_ = shadow_->GetPosition() - player_->GetPosition();
		capsuleCollider_->GetCapsule().seg.start = offset_;
	}
	(this->*updater_)();
}

void SwordEquip::Draw()
{
	if (frame_ >= 0)
	{
		auto pos = player_->GetPosition() + offset_;
		auto cameraOffset = camera_->ViewOffset();

		GetDrawScreenGraph(0, 0, 800, 600, captureH_);
		slash_.Draw(captureH_, dist_, psH_, normalH_, cameraOffset + offset_);
	}
}
