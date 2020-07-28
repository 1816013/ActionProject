#pragma once
#include "Collider.h"
#include "../Geometry.h"
class CircleCollider : public Collider
{
private:
	Circle circle_;
	
public:
	CircleCollider(std::shared_ptr<Character> owner, const char* tag = "");

	/// <summary>
	/// �~��񂩂�~�Փˏ������
	/// </summary>
	/// <param name="c">�~���</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Circle& c);

	/// <summary>
	/// ���S���W�Ɣ��a��񂩂�~�Փˏ������
	/// </summary>
	/// <param name="c">���S���W</param>
	/// <param name="r">���a</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Position2f& p, const float r);
	bool IsHit(std::shared_ptr<Collider> col)override;

	void Draw(std::shared_ptr<Camera>c)override;

	const Circle& GetCircle()const;

	/// <summary>
	/// ���ۂ̍��W��Ԃ�
	/// </summary>
	/// <returns>���S���W</returns>
	const Vector2f AcutualPosition();
	
};

