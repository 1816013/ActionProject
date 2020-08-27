#pragma once
#include <memory>
#include "../../Geometry.h"

class Enemy;
class EnemyManager;
class Camera;
class CollisionManager;
/// <summary>
/// 敵発生器
/// </summary>
class Spawner
{
protected:
	Position2f pos_;	// スポナー座標
	std::shared_ptr<Enemy> prototype_;	// 敵のプロトタイプ
	std::shared_ptr<EnemyManager> enemyManager_;
	std::shared_ptr<Camera>camera_;
	std::shared_ptr<CollisionManager>collisionManeger_;

	virtual Enemy* CreateClone()final;
public:
	Spawner(const Position2f& pos,
		Enemy* prototype,
		std::shared_ptr<EnemyManager>& em,
		std::shared_ptr<CollisionManager> cm, 	
		std::shared_ptr<Camera>c);
	virtual ~Spawner() = default;
	//virtual std::shared_ptr<Enemy>* Spawn() = 0;
	virtual void Update() = 0;
};

