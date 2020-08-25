#pragma once
#include "Equipment.h"

class ProjectileManager;
class CollisionManager;
class ShurikenEquip :
	public Equipment
{
private:
	ProjectileManager& pm_;
public:
	ShurikenEquip(ProjectileManager& pm,std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c);

	/// <summary>
	/// 手裏剣攻撃
	/// </summary>
	/// <param name="player">プレイヤーへの参照</param>
	/// <param name="input">入力参照</param>
	void Attack(const Player& player, const Input& input, Vector2f offset = Vector2f::ZERO)override;

};

