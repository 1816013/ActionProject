#pragma once
#include <list>
#include <memory>

class Projectile;
class CollisionManager;
class Camera;
/// <summary>
/// 発射物を管理するクラス
/// </summary>
class ProjectileManager
{
private:
	std::list<std::shared_ptr<Projectile>>projectiles_;

public:
	/// <summary>
	/// 発射物を管理に追加する
	/// </summary>
	/// <param name="p">発射物</param>
	void AddProjectile(Projectile* p);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 管理している発射物全てを返す
	/// </summary>
	/// <returns>管理している発射物</returns>
	std::list<std::shared_ptr<Projectile>>& Projectiles();
};

