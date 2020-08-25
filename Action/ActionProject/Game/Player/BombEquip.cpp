#include "BombEquip.h"
#include "Player.h"
#include "../../System/Input.h"
#include "../ProjectileManager.h"
#include "BombShot.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"
#include "../Camera.h"

namespace
{
	constexpr float bomb_shot_speed = 10;
	constexpr float bomb_radius = 24;
}
BombEquip::BombEquip(ProjectileManager& pm, std::shared_ptr<CollisionManager>col, std::shared_ptr<Camera> c) :
	pm_(pm),
	Equipment(col, c)
{
}

void BombEquip::Attack(const Player& player, const Input& input, Vector2f offset)
{
	Vector2f vel(0, 0);
	if (input.IsPressed("up"))
	{
		vel = { 0, -1 };
	}
	if (input.IsPressed("down"))
	{
		vel = { 0, 1 };
	}
	if (input.IsPressed("right"))
	{
		vel = { 1, 0 };
	}
	if (input.IsPressed("left"))
	{
		vel = { -1, 0 };
	}
	
	if (vel.x == 0 && vel.y == 0)
	{
		if (player.Direction() == Direction::RIGHT)
		{
			vel = { 1, 0 };
		}
		if (player.Direction() == Direction::LEFT)
		{
			vel = { -1, 0 };
		}
	}
	vel *= bomb_shot_speed;
	auto bomb = new BombShot(player.GetPosition(), vel, camera_);
	
	pm_.AddProjectile(bomb);
	collisionManager_->AddCollider(new CircleCollider(pm_.Projectiles().back(), tagPlayerAtack, {0, 0}, bomb_radius));
}
