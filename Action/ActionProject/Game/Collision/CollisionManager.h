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
	std::list<std::shared_ptr<Collider>>colliders_;	// �S�Փˏ��̃��X�g
public:
	/// <summary>
	/// �S�ẴR���W�����𔻒肷��
	/// </summary>
	void Update();

	/// <summary>
	/// �f�o�b�O�p�`��
	/// </summary>
	/// <param name="c">�J����(��ʃI�t�Z�b�g�p)</param>
	void DebugDraw(std::shared_ptr<Camera>c);

	/// <summary>
	/// �Փˏ���ǉ�����
	/// </summary>
	/// <param name="collider">�Փˏ���ǉ�����</param>
	void AddCollider(Collider* collider);

};

