#pragma once
#include <list>
#include <memory>

class Collider;
class Camera;
/// <summary>
/// 衝突判定を管理するクラス
/// </summary>
class CollisionManager
{
public:
	/// <summary>
	/// 全てのコリジョンを判定する
	/// </summary>
	void Update();

	/// <summary>
	/// デバッグ用描画
	/// </summary>
	/// <param name="c">カメラ(画面オフセット用)</param>
	void DebugDraw(std::shared_ptr<Camera>c);

	/// <summary>
	/// 衝突情報を追加する
	/// </summary>
	/// <param name="collider">衝突情報を追加する</param>
	void AddCollider(Collider* collider);

	/// <summary>
	/// 衝突情報をすべて取得する
	/// </summary>
	/// <returns></returns>
	std::list<std::shared_ptr<Collider>>GetColliders();

private:
	std::list<std::shared_ptr<Collider>>colliders_;	// 全衝突情報のリスト


};

