#pragma once
#include "Equipment.h"
#include <memory>
class ProjectileManager;
class CollisionManager;
class BombEquip : public Equipment
{
private:
	ProjectileManager& pm_;
	//std::shared_ptr<CollisionManager>collisionManager_;
public:
	BombEquip(ProjectileManager& pm, std::shared_ptr<CollisionManager>col, std::shared_ptr<Camera> c);

	/// <summary>
	/// 爆弾攻撃
	/// </summary>
	/// <param name="player">プレイヤーへの参照</param>
	/// <param name="input">入力参照</param>
	void Attack(const Player& player, const Input& input)override;

};

