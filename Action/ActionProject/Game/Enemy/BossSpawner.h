#pragma once
#include "Spawner.h"
#include <memory>

class CollisionManager;
class BossSpawner : public Spawner
{
private:
	std::shared_ptr<CollisionManager>collisionManager_;

	using Updater_t = void (BossSpawner::*)();
	Updater_t updater_;

	/// <summary>
	/// ボスが生成されるときだけに呼ばれる更新
	/// </summary>
	void SpawnUpdate();
	/// <summary>
	/// 生成された後呼ばれる更新(何もしない)
	/// </summary>
	void SleepUpdate();
public:
	/// <summary>
	/// ボスを出現させるスポナー
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="prototype">エネミーのプロトタイプ</param>
	/// <param name="enemyManager">エネミー管理クラス</param>
	/// <param name="collisionManager">衝突管理クラス</param>
	/// <param name="camera">カメラ</param>
	BossSpawner(const Position2f& pos,
		Enemy* prototype,
		std::shared_ptr<EnemyManager>enemyManager,
		std::shared_ptr<CollisionManager>collisionManager,
		std::shared_ptr<Camera> camera);
	~BossSpawner() = default;
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

};

