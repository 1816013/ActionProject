#include "BombEquip.h"
#include "Player.h"
#include "../../Input.h"
#include "ProjectileManager.h"
#include "BombShot.h"
#include "../CollisionManager.h"
#include "../CircleCollider.h"

BombEquip::BombEquip(ProjectileManager& pm, std::shared_ptr<CollisionManager>col) : 
	pm_(pm),
	collisionManager_(col)
{
}

void BombEquip::Attack(const Player& player, const Input& input)
{
	Vector2f vel(0, 0);
	if (input.IsPressed("right"))
	{
		vel = { 10, 0 };
	}
	if (input.IsPressed("left"))
	{
		vel = { -10, 0 };
	}
	if (input.IsPressed("up"))
	{
		vel = { 0, -10 };
	}
	if (input.IsPressed("down"))
	{
		vel = { 0, 10 };
	}
	if (vel.x == 0 && vel.y == 0)
	{
		if (player.Direction() == Direction::RIGHT)
		{
			vel = { 5, 0 };
		}
		if (player.Direction() == Direction::LEFT)
		{
			vel = { -5, 0 };
		}
	}
	auto bomb = new BombShot(player.Position(), vel);
	
	pm_.AddProjectile(bomb);
	collisionManager_->AddCollider(new CircleCollider(pm_.Projectiles().back()));
}
