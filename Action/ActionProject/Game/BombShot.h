#pragma once
#include "Projectile.h"
class BombShot :
	public Projectile
{
public:
	BombShot(const Position2& pos, const Vector2f& vel);
	// Update��Projectile�̂��̂��g�p

	void Draw()override;
};

