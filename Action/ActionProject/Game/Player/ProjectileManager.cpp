#include "ProjectileManager.h"
#include "Projectile.h"
#include <algorithm>

//std::list<std::shared_ptr<Projectile>>& ProjectileManager::Projectiles()
//{
//	// TODO: return ステートメントをここに挿入します
//}

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
	/*auto it = std::remove_if(projectiles_.begin(), projectiles_.end(),
		[](std::shared_ptr<Projectile>& p)
		{
			return p->IsDead(); 
		});

	if (it != projectiles_.end())
	{
		projectiles_.erase(it, projectiles_.end());
	}*/
	
}

void ProjectileManager::Draw()
{
	for (auto& p : projectiles_)
	{
		p->Draw();
	}
}
