#include "ShadowClone.h"
#include <DxLib.h>
#include "Player.h"
#include "../Camera.h"
#include "../../Scene/GamePlayingScene.h"
#include "../../System/Input.h"
#include "BombEquip.h"
#include "ShurikenEquip.h"
#include "ChainEquip.h"
#include "SwordEquip.h"

using namespace std;

void ShadowClone::ExtensionAttack(const Input& input)
{
	equipments_[currentEquipmentNo_]->ExtensionAttack(*player_, input);
}

ShadowClone::ShadowClone(GamePlayingScene* gs, Player* player, std::shared_ptr<Camera> camera) : 
	player_(player), 
	camera_(camera)
{
	equipments_.emplace_back(make_shared<SwordEquip>(gs->GetPlayer(), gs->GetCollisionManager(), camera_, this));
	equipments_.emplace_back(make_shared<BombEquip>(gs->GetProjectileManager(), gs->GetCollisionManager(), camera_));
	equipments_.emplace_back(make_shared<ShurikenEquip>(gs->GetProjectileManager(), gs->GetCollisionManager(), camera_));
	equipments_.emplace_back(make_shared<ChainEquip>(gs->GetPlayer(), gs->GetCollisionManager(), camera_, this));
}

const Position2f& ShadowClone::GetPosition() const
{
	return pos_;
}

void ShadowClone::Attack(const Input& input, size_t equipNo)
{
	auto offset = pos_ - player_->GetPosition();
	equipments_[equipNo]->Attack(*player_, input, offset);
	currentEquipmentNo_ = equipNo;
}

void ShadowClone::Update(const Position2f& pos)
{
	pos_ = pos;
	for (auto e : equipments_)
	{
		e->Update();
	}
}

void ShadowClone::Draw()
{
	equipments_[currentEquipmentNo_]->Draw();

	auto offset = camera_->ViewOffset();
	DrawCircleAA(pos_.x + offset.x, pos_.y, 10, 32, 0xff0000, true);
}
