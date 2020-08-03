#include "Projectile.h"

Projectile::Projectile(std::shared_ptr<Camera> c): Character(c), camera_(c)
{
}

void Projectile::Update()
{
	pos_ += vel_;
}

bool Projectile::IsDead() const
{
	return !isActive_;
}
