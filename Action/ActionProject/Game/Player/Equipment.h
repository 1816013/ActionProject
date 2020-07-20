#pragma once
#include <memory>

class Player;
class Input;
class CollisionManager;
class Equipment
{
protected:
	std::shared_ptr<CollisionManager>collisionManager_;
public:
	Equipment(std::shared_ptr<CollisionManager>cm);
	virtual ~Equipment() = default;
	/// <summary>
	/// 今の武器で攻撃する
	/// </summary>
	/// <param name="p"> プレイヤーの参照</param>
	/// <param name="i">入力参照</param>
	virtual void Attack(const Player& p, const Input& i) = 0;
	virtual void ExtendAttack(const Player& player, const Input& input);
	virtual void Update() {};
	virtual void Draw() {};
};

