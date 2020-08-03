#pragma once
#include "Collider.h"
#include "../../Geometry.h"
class CapsuleCollider : public Collider
{
private:
	Capsule capsule_;
public:
	CapsuleCollider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	CapsuleCollider(std::shared_ptr<Character> owner, const Capsule& cap,  const char* tag = "", bool immortal = false);

	bool IsHit(std::shared_ptr<Collider> col)override;
	void Draw(std::shared_ptr<Camera>c)override;
	/// <summary>
	/// ���ۂ̍��W��Ԃ�
	/// </summary>
	/// <returns>�N�_���W</returns>
	const Vector2f AcutualPosition();

	/// <summary>
	/// �O���炢�����悤�ɎQ�Ƃ�Ԃ�
	/// </summary>
	/// <returns>�J�v�Z���̎Q��</returns>
	/// <example></example>
	Capsule& GetCapsule();
};

