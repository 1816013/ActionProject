#pragma once
#include <list>
#include <memory>

class Collider;
/// <summary>
/// �Փ˔�����Ǘ�����
/// </summary>
class CollisionManager
{
private:
	std::list<std::shared_ptr<Collider>>colliders_;
public:
	/// <summary>
	/// �S�ẴR���W�����𔻒肷��
	/// </summary>
	void Update();

	void DebugDraw();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="collider"></param>
	void AddCollider(Collider* collider);

};

