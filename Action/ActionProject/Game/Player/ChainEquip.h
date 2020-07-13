#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class ChainEquip : public Equipment
{
private:
	int frame_;
	const Player& player_;
	Vector2f direction_;
public:
	ChainEquip(const Player& p);
	void Attack(const Player& player, const Input& input)override;
	void Update();
	void Draw();
};

