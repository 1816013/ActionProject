#pragma once
#include <list>
#include <memory>

class Collider;
class Camera;
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

	void DebugDraw(std::shared_ptr<Camera>c);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="collider"></param>
	void AddCollider(Collider* collider);

};

