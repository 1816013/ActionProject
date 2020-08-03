#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class CollisionManager;
class CapsuleCollider;
class ChainEquip : public Equipment
{
private:
	int frame_;
	int extensionFrame_;
	//const Player& player_;
	Vector2f direction_;
	std::shared_ptr<Player>& player_;
	CapsuleCollider* capsuleCollider_ = nullptr;
	float angle = 0.0f;
	float variationAngle = 0.0f;
	using func_t = void(ChainEquip::*)();
	func_t updater_;

	void NomalUpdate();
	void ExtensionUpdate();
	void SetDirection(const Input& input, const Player& player);
public:
	ChainEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c);
	void Attack(const Player& player, const Input& input)override;
	void ExtensionAttack(const Player& player, const Input& input)override;
	
	void Update();
	void Draw();
};

