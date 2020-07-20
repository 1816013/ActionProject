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
	/// ���̕���ōU������
	/// </summary>
	/// <param name="p"> �v���C���[�̎Q��</param>
	/// <param name="i">���͎Q��</param>
	virtual void Attack(const Player& p, const Input& i) = 0;
	virtual void ExtendAttack(const Player& player, const Input& input);
	virtual void Update() {};
	virtual void Draw() {};
};

