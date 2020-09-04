#include "SwordEquip.h"
#include <DxLib.h>
#include <cmath>
#include "Player.h"
#include "../../System/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/FanCollider.h"
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
	
	constexpr int slash_frame = 30;
	constexpr int slash_end_frame = slash_frame / 2;
	constexpr float slash_target_rad = 135 * (DX_PI_F / 180);
	constexpr float slash_end_speed = slash_target_rad / slash_frame;// 始端スピード
	constexpr float slash_start_speed = slash_target_rad / (slash_frame - slash_end_frame);	// 終端スピード

	float slash1Speed = slash_end_speed;	
	float slash2Speed = slash_start_speed;
}
void SwordEquip::NomalUpdate()
{
	slash_.center = player_->GetPosition();
	if (--frame_ > 0)
	{		
		if (isRight_)
		{			
			slash_.AddAngle1(slash1Speed);
			if (frame_ >= slash_end_frame)
			{
				slash_.AddAngle2(slash2Speed);
			}
		}
		else
		{
			slash_.AddAngle2(slash2Speed);
			if (frame_ >= slash_end_frame)
			{
				slash_.AddAngle1(slash1Speed);
			}
		}
	}
	else
	{
		frame_ = -1;
	}
}
SwordEquip::SwordEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c, ShadowClone* shadow) :
	player_(p),
	Equipment(cm, c),
	shadow_(shadow),
	updater_(&SwordEquip::NomalUpdate)
{
	slash_ = SlashShape({ 400.0f, 300.0f }, { -125.0f, -125.0f }, 0);
	frame_ = -1;	// -1で初期化
	isRight_ = true;
	
	
	auto& rc = Application::Instance().GetViewport();
	captureH_ = MakeScreen(rc.GetSize().w, rc.GetSize().h);
	if (psH_ == -1)
	{
		psH_ = LoadPixelShader(L"Resource/Etc/testps.pso");
	}
	auto& fileMng = FileManager::Instance();
	if (normalH_ == -1)
	{
		normalH_ = fileMng.Load(L"Resource/Etc/normal.png")->Handle();
	}
}

void SwordEquip::Attack(const Player& player, const Input& input, Vector2f offset)
{
	if (frame_ >= 0)return;

	/*if (capsuleCollider_ == nullptr)
	{
		capsuleCollider_ = new CapsuleCollider(player_, { {offset,offset}, 20 }, tagPlayerAtack, true);
		collisionManager_->AddCollider(capsuleCollider_);
	}*/
	frame_ = slash_frame;
	
	if (player.Direction() == Direction::RIGHT)
	{
		//v2を先に移動
		slash1Speed = slash_end_speed;	// 始端スピード
		slash2Speed = slash_start_speed;	// 終端スピード
		slash_.v1 = slash_.v2= {-125.0f, -125.0f} ;
		isRight_ = true;
	/*	fanCollider_ = new FanCollider(player_, FanShape({0, 0}, { -125.0f, -125.0f }, 135 * (DX_PI_F / 180)), tagPlayerAtack, true);
		collisionManager_->AddCollider(fanCollider_);*/
	}
	else
	{		
		//v1を先に移動
		slash1Speed = -slash_start_speed;	// 始端スピード
		slash2Speed = -slash_end_speed;	// 終端スピード
		slash_.v1 = slash_.v2 = { 125.0f, -125.0f };
		isRight_ = false;
	}
	

}

void SwordEquip::Update()
{
	if (shadow_ != nullptr)
	{
		offset_ = shadow_->GetPosition() - player_->GetPosition();
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
		slash_.Draw(captureH_, dist_, psH_, normalH_,isRight_, cameraOffset ,offset_ + Vector2f(0, -50));
	}
}
