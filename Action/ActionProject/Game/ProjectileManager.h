#pragma once
#include <list>
#include <memory>

class Projectile;
class CollisionManager;
class Camera;
/// <summary>
/// ���˕����Ǘ�����N���X
/// </summary>
class ProjectileManager
{
private:
	std::list<std::shared_ptr<Projectile>>projectiles_;

public:
	/// <summary>
	/// ���˕����Ǘ��ɒǉ�����
	/// </summary>
	/// <param name="p">���˕�</param>
	void AddProjectile(Projectile* p);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �Ǘ����Ă��锭�˕��S�Ă�Ԃ�
	/// </summary>
	/// <returns>�Ǘ����Ă��锭�˕�</returns>
	std::list<std::shared_ptr<Projectile>>& Projectiles();
};

