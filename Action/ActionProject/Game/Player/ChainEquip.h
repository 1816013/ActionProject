#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class CollisionManager;
class CapsuleCollider;
class ChainEquip : public Equipment
{
private:
	int frame_;
	//const Player& player_;
	Vector2f direction_;
	std::shared_ptr<Player>& player_;
	CapsuleCollider* capsuleCollider_ = nullptr;
public:
	ChainEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c);
	void Attack(const Player& player, const Input& input)override;
	void ExtendAttack(const Player& player, const Input& input)override;
	void Update();
	void Draw();
};

