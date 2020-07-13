#include "BombEquip.h"
#include "Player.h"
#include "../../Input.h"
#include "ProjectileManager.h"
#include "BombShot.h"

BombEquip::BombEquip(ProjectileManager& pm) : pm_(pm)
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
	pm_.AddProjectile(new BombShot(player.Position(), vel));
}
