#pragma once
#include "Collider.h"
#include "../../Geometry.h"

/// <summary>
/// 円衝突情報のクラス
/// </summary>
class CircleCollider : public Collider
{
public:
	/// <summary>
	/// 円衝突情報を作る(半径1,座標(0, 0) )
	/// </summary>
	/// <param name="owner">円衝突情報を持っているキャラクター</param>
	/// <param name="tag">タグ</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag = "");

	/// <summary>
	/// 円情報から円衝突情報を作る
	/// </summary>
	/// <param name="owner">円衝突情報を持っているキャラクター</param>
	/// <param name="tag">タグ</param>
	/// <param name="c">円情報</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Circle& c);

	/// <summary>
	/// 中心座標と半径情報から円衝突情報を作る
	/// </summary>
	/// <param name="c">中心座標</param>
	/// <param name="r">半径</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Position2f& p, const float r);
	/// <summary>
	/// 何かが当たった
	/// </summary>
	/// <param name="col">衝突情報</param>
	/// <returns>true:当たった</returns>
	bool IsHit(std::shared_ptr<Collider> col)override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="c">カメラ(画面オフセット用)</param>
	void Draw(std::shared_ptr<Camera>c)override;

	/// <summary>
	/// 円衝突情報の円を取得する
	/// </summary>
	/// <returns>円衝突情報の円</returns>
	const Circle& GetCircle()const;

	/// <summary>
	/// 実際の座標を返す
	/// </summary>
	/// <returns>中心座標</returns>
	const Vector2f AcutualPosition();
private:
	Circle circle_;
	

	
};

