#include "ProjectileManager.h"
#include "Projectile.h"
#include <algorithm>

std::list<std::shared_ptr<Projectile>>& ProjectileManager::Projectiles()
{
	return projectiles_;
}

void ProjectileManager::AddProjectile(Projectile* p)
{
	projectiles_.emplace_back(p);
}

void ProjectileManager::Update()
{
	for (auto& p : projectiles_)
	{
		p->Update();
	}
	projectiles_.remove_if([](std::shared_ptr<Projectile>&p) {return p->IsDead(); });	
}

void ProjectileManager::Draw()
{
	for (auto& p : projectiles_)
	{
		p->Draw();
	}
}
