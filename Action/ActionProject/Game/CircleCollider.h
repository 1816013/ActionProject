#pragma once
#include "Collider.h"
#include "../Geometry.h"
class CircleCollider : public Collider
{
private:
	Circle circle_;
public:
	CircleCollider();

	/// <summary>
	/// �~��񂩂�~�Փˏ������
	/// </summary>
	/// <param name="c">�~���</param>
	CircleCollider(const Circle& c);

	/// <summary>
	/// ���S���W�Ɣ��a��񂩂�~�Փˏ������
	/// </summary>
	/// <param name="c">���S���W</param>
	/// <param name="r">���a</param>
	CircleCollider(const Position2f& p, const float r);
	bool IsHit(Collider* col)override;
};

