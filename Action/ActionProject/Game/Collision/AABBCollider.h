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
	/// 矩形情報から矩形衝突情報を作る
	/// </summary>
	/// <param name="c">円情報</param>
	AABBCollider(const Rect& r);

	/// <summary>
	/// 中心座標から矩形衝突情報を作る
	/// </summary>
	/// <param name="c">中心座標</param>
	/// <param name="r">半径</param>
	AABBCollider(const Position2f& p);
	bool IsHit(std::shared_ptr<Collider> col)override;

};

