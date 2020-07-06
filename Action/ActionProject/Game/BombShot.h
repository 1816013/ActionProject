#pragma once
#include "Projectile.h"
class BombShot :
	public Projectile
{
public:
	BombShot(const Position2& pos, const Vector2f& vel);
	// Update‚ÍProjectile‚Ì‚à‚Ì‚ðŽg—p

	void Draw()override;
};

