#pragma once
#include "Spawner.h"
class Enemy;
class SideSpawner : public Spawner
{
private:
	int frame_ = 0;
public:
	SideSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em);
	~SideSpawner() = default;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update()override;
};

