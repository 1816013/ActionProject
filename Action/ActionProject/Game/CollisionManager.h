#pragma once
#include <list>
#include <memory>

class Collider;
class Camera;
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

	void DebugDraw(std::shared_ptr<Camera>c);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="collider"></param>
	void AddCollider(Collider* collider);

};

