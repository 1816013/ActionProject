#pragma once
#include <list>
#include <memory>

class Collider;
/// <summary>
/// 衝突判定を管理する
/// </summary>
class CollisionManager
{
private:
	std::list<std::shared_ptr<Collider>>colliders_;
public:
	/// <summary>
	/// 全てのコリジョンを判定する
	/// </summary>
	void Update();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="collider"></param>
	void AddCollider(Collider* collider);

};

