#pragma once
#include <memory>
#include "../../Geometry.h"

class Player;
class Input;
class CollisionManager;
class Camera;
class Equipment
{
protected:
	std::shared_ptr<CollisionManager>collisionManager_;
	std::shared_ptr<Camera> camera_;
public:
	Equipment(std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c);
	virtual ~Equipment() = default;
	/// <summary>
	/// 今の武器で攻撃する
	/// </summary>
	/// <param name="p"> プレイヤーの参照</param>
	/// <param name="i">入力参照</param>
	virtual void Attack(const Player& p, const Input& i, Vector2f offset = Vector2f::ZERO) = 0;
	virtual void ExtensionAttack(const Player& player, const Input& input);
	virtual void Update() {};
	virtual void Draw() {};
};

