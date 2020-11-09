#pragma once
#include "Collider.h"
#include "../../Geometry.h"
class FanCollider :
	public Collider
{
private:
	FanShape fanShape_;
	bool isAttack_;
public:
	FanCollider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	/// <summary>
	/// 扇形の衝突情報を作る
	/// </summary>
	/// <param name="owner">衝突情報を保持しているキャラクター</param>
	/// <param name="cap">扇形情報</param>
	/// <param name="tag">タグ</param>
	/// <param name="immortal">不死かどうか</param>
	FanCollider(std::shared_ptr<Character> owner, const FanShape& fan, const char* tag = "", bool immortal = false);
	/// <summary>
	/// 何かが当たった
	/// </summary>
	/// <param name="col">コライダー</param>
	/// <returns>true:当たった</returns>
	bool IsHit(std::shared_ptr<Collider> col)override;

	/// <summary>
	/// デバッグ描画
	/// カメラは座標のオフセットを取得するため
	/// </summary>
	/// <param name="c">カメラ</param>
	void Draw(std::shared_ptr<Camera>c)override;

	/// <summary>
	/// 実際の座標を返す
	/// </summary>
	/// <returns>中心座標</returns>
	const Vector2f AcutualPosition();

	/// <summary>
	/// 外からいじれるように参照を返す
	/// </summary>
	/// <returns>衝突情報の扇形の参照</returns>
	/// <example></example>
	FanShape& GetFanShape();

	/// <summary>
	/// 攻撃中かどうか
	/// </summary>
	/// <returns></returns>
	void SetIsAttack(bool isAttack);
};

