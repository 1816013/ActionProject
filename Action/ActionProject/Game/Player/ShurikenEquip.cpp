#include "ShurikenEquip.h"
#include "../../Geometry.h"
#include "../../Input.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "ShurikenShot.h"

ShurikenEquip::ShurikenEquip(ProjectileManager& pm) : pm_(pm)
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
	vel *= 15;
	pm_.AddProjectile(new ShurikenShot(player.Position(), vel));
}
