#pragma once
#include <list>
#include <memory>

class Projectile;
class CollisionManager;
class Camera;
class ProjectileManager
{
private:
	std::list<std::shared_ptr<Projectile>>projectiles_;

public:
	void AddProjectile(Projectile* p);
	void Update();
	void Draw();
	std::list<std::shared_ptr<Projectile>>& Projectiles();
};

