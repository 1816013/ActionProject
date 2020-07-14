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
	/// 円情報から円衝突情報を作る
	/// </summary>
	/// <param name="c">円情報</param>
	CircleCollider(const Circle& c);

	/// <summary>
	/// 中心座標と半径情報から円衝突情報を作る
	/// </summary>
	/// <param name="c">中心座標</param>
	/// <param name="r">半径</param>
	CircleCollider(const Position2f& p, const float r);
	bool IsHit(Collider* col)override;
};

