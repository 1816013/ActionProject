#pragma once
#include "Spawner.h"
class Enemy;
class CollisionManager;
class SideSpawner : public Spawner
{
private:
	int frame_ = 0;
	std::shared_ptr<CollisionManager>collisionManeger_;
public:
	SideSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em, std::shared_ptr<CollisionManager> cm, std::shared_ptr<Camera>c);
	~SideSpawner() = default;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update()override;
};

