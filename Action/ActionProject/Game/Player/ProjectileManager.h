#pragma once
#include <list>
#include <memory>

class Projectile;
class CollisionManager;
class ProjectileManager
{
private:
	std::list<std::shared_ptr<Projectile>>projectiles_;
public:
	std::list<std::shared_ptr<Projectile>>& Projectiles();
	void AddProjectile(Projectile* p);
	void Update();
	void Draw();
};

