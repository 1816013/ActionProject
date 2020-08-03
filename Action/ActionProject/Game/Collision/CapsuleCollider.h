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
	/// 実際の座標を返す
	/// </summary>
	/// <returns>起点座標</returns>
	const Vector2f AcutualPosition();

	/// <summary>
	/// 外からいじれるように参照を返す
	/// </summary>
	/// <returns>カプセルの参照</returns>
	/// <example></example>
	Capsule& GetCapsule();
};

