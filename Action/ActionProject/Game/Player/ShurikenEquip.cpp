#include "ShurikenEquip.h"
#include "../../Geometry.h"
#include "../../System/Input.h"
#include "../ProjectileManager.h"
#include "Player.h"
#include "ShurikenShot.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"

namespace
{
	constexpr int shuriken_speed = 15; 
	constexpr int collider_radius = 10;
}


ShurikenEquip::ShurikenEquip(ProjectileManager& pm, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c)
	: pm_(pm), Equipment(cm, c)
{
}

void ShurikenEquip::Attack(const Player& player, const Input& input, Vector2f offset)
{
	Vector2f vel(Vector2f::ZERO);
	if (input.IsPressed("right"))
	{
		vel += Vector2f::RIGHT;
	}
	if (input.IsPressed("left"))
	{
		vel += Vector2f::LEFT;
	}
	if (input.IsPressed("up"))
	{
		vel += Vector2f::UP;
	}
	if (input.IsPressed("down"))
	{
		vel += Vector2f::DOWN;
	}
	if (vel == Vector2f::ZERO)
	{
		if (player.Direction() == Direction::RIGHT)
		{
			vel += Vector2f::RIGHT;
		}
		if (player.Direction() == Direction::LEFT)
		{
			vel += Vector2f::LEFT;
		}
	}
	vel.Nomarize();
	vel *= shuriken_speed;
	pm_.AddProjectile(new ShurikenShot(player.GetPosition() + offset + Vector2f(0, -50), vel, camera_));
	collisionManager_->AddCollider(new CircleCollider(pm_.Projectiles().back(), 
		tagPlayerAtack, Circle{ Position2f::ZERO, collider_radius }));
}
