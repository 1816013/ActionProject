#pragma once
#include "Collider.h"
#include "../../Geometry.h"
class CapsuleCollider : public Collider
{
private:
	Capsule capsule_;
public:
	CapsuleCollider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	/// <summary>
	/// カプセル状の衝突情報を作る
	/// </summary>
	/// <param name="owner">衝突情報を保持しているキャラクター</param>
	/// <param name="cap">カプセル情報</param>
	/// <param name="tag">タグ</param>
	/// <param name="immortal">不死かどうか</param>
	CapsuleCollider(std::shared_ptr<Character> owner, const Capsule& cap,  const char* tag = "", bool immortal = false);
	/// <summary>
	/// 何かが当たった
	/// </summary>
	/// <param name="col">コライダー</param>
	/// <returns>true:当たった</returns>
	bool IsHit(std::shared_ptr<Collider> col)override;

	/// <summary>
	/// 描画
	/// カメラは座標のオフセットを取得するため
	/// </summary>
	/// <param name="c">カメラ</param>
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

