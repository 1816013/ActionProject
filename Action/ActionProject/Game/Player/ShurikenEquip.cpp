#include "ShurikenEquip.h"
#include "../../Geometry.h"
#include "../../System/Input.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "ShurikenShot.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"

namespace
{
	constexpr int shuriken_speed = 15;
}


ShurikenEquip::ShurikenEquip(ProjectileManager& pm, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c)
	: pm_(pm), Equipment(cm, c)
{
}

void ShurikenEquip::Attack(const Player& player, const Input& input)
{
	Vector2f vel(0, 0);
	if (input.IsPressed("right"))
	{
		vel += { 1, 0 };
	}
	if (input.IsPressed("left"))
	{
		vel += { -1, 0 };
	}
	if (input.IsPressed("up"))
	{
		vel += { 0, -1 };
	}
	if (input.IsPressed("down"))
	{
		vel += { 0, 1 };
	}
	if (vel.x == 0 && vel.y == 0)
	{
		if (player.Direction() == Direction::RIGHT)
		{
			vel += { 1, 0 };
		}
		if (player.Direction() == Direction::LEFT)
		{
			vel += { -1, 0 };
		}
	}
	vel.Nomarize();
	vel *= shuriken_speed;
	pm_.AddProjectile(new ShurikenShot(player.GetPosition(), vel, camera_));
	collisionManager_->AddCollider(new CircleCollider(pm_.Projectiles().back(), tagPlayerAtack, Circle{ {0, 0}, 10 }));
}
