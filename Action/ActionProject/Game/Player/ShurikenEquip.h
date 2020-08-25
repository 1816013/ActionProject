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
	/// �藠���U��
	/// </summary>
	/// <param name="player">�v���C���[�ւ̎Q��</param>
	/// <param name="input">���͎Q��</param>
	void Attack(const Player& player, const Input& input, Vector2f offset = Vector2f::ZERO)override;

};

