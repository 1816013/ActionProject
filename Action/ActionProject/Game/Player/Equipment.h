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
	/// ���̕���ōU������
	/// </summary>
	/// <param name="p"> �v���C���[�̎Q��</param>
	/// <param name="i">���͎Q��</param>
	virtual void Attack(const Player& p, const Input& i, Vector2f offset = Vector2f::ZERO) = 0;
	virtual void ExtensionAttack(const Player& player, const Input& input);
	virtual void Update() {};
	virtual void Draw() {};
};

