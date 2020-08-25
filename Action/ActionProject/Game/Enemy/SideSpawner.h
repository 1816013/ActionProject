#pragma once
#include "Spawner.h"
//class Enemy;
class CollisionManager;
/// <summary>
/// 画面両端から出現させる発生器
/// </summary>
class SideSpawner : public Spawner
{
private:
	int frame_ = 0;	// フレーム
	//std::shared_ptr<CollisionManager>collisionManeger_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="prototype">敵のプロトタイプ</param>
	/// <param name="em">敵管理クラス</param>
	/// <param name="cm">衝突情報管理クラス</param>
	/// <param name="c">カメラ</param>
	SideSpawner(const Position2f& pos, Enemy* prototype,  
		std::shared_ptr<EnemyManager> em,
		std::shared_ptr<CollisionManager> cm, 
		std::shared_ptr<Camera>c);
	~SideSpawner() = default;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update()override;
};

