#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class CollisionManager;
class ChainEquip : public Equipment
{
private:
	int frame_;
	const Player& player_;
	Vector2f direction_;
public:
	ChainEquip(const Player& p, std::shared_ptr<CollisionManager>cm);
	void Attack(const Player& player, const Input& input)override;
	void Update();
	void Draw();
};

