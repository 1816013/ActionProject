#pragma once
#include "Collider.h"
#include "../../Geometry.h"

class AABBCollider : public Collider
{
private:
	Rect circle_;
public:
	AABBCollider();

	/// <summary>
	/// ��`��񂩂��`�Փˏ������
	/// </summary>
	/// <param name="c">�~���</param>
	AABBCollider(const Rect& r);

	/// <summary>
	/// ���S���W�����`�Փˏ������
	/// </summary>
	/// <param name="c">���S���W</param>
	/// <param name="r">���a</param>
	AABBCollider(const Position2f& p);
	bool IsHit(std::shared_ptr<Collider> col)override;

};

