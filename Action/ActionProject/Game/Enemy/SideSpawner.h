#pragma once
#include "Spawner.h"
#include <memory>
#include <list>

class CollisionManager;
/// <summary>
/// 画面両端から出現させる発生器のクラス
/// </summary>
class SideSpawner : public Spawner
{
private:
	int frame_ = 0;	// フレーム
	int limitSpawnNum_ = 0;
	int averageSpawnFrame_ = 0;
	bool needBalance_ = false;
	struct Regurator
	{
		std::weak_ptr<Enemy>ownedWeakRef;
		bool isRight;
		Regurator(std::weak_ptr<Enemy> wref, bool isright) :
			ownedWeakRef(wref),
			isRight(isright) {};
	};
	std::list <Regurator>regurators_;
	std::list<std::weak_ptr<Enemy>>ownedEnemiesWeakRefs_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="prototype">敵のプロトタイプ</param>
	/// <param name="em">敵管理クラス</param>
	/// <param name="cm">衝突情報管理クラス</param>
	/// <param name="c">カメラ</param>
	/// <param name="averageSpawnFrame">平均発生時間</param>
	/// <param name="limitCnt">発生数</param>
	/// <param name="needBalance">右と左の発生数を同じ数にするか</param>
	SideSpawner(const Position2f& pos, Enemy* prototype,  
		std::shared_ptr<EnemyManager> em,
		std::shared_ptr<CollisionManager> cm, 
		std::shared_ptr<Camera>c,
		int averageSpawnFrame = 60,
		int limitCnt = -1,
		bool needBalance = false);
	~SideSpawner() = default;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update()override;
};

