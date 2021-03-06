#pragma once
#include <memory>
#include <list>


class Enemy;
using EnemyList = std::list<std::shared_ptr<Enemy>>;
/// <summary>
/// 敵を管理する
/// </summary>
class EnemyManager
{
private:
	EnemyList enemies_;
public:
	/// <summary>
	/// 敵を管理に追加する
	/// </summary>
	/// <param name="enemy">敵の本体</param>
	void AddEnemy(Enemy* enemy);

	/// <summary>
	/// 管理している敵全てを取得する
	/// </summary>
	/// <returns></returns>
	EnemyList& Enemies();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};


