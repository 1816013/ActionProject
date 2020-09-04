#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class Player;
class CollisionManager;
class CapsuleCollider;
class ShadowClone;
/// <summary>
/// 鎖鎌
/// </summary>
class ChainEquip : public Equipment
{
private:
	int frame_;
	int extensionFrame_;
	Vector2f direction_;
	std::shared_ptr<Player>& player_;
	CapsuleCollider* capsuleCollider_ = nullptr;
	float angle_ = 0.0f;
	float variationAngle = 0.0f;
	using func_t = void(ChainEquip::*)();
	ShadowClone* shadow_;
	Vector2f offset_ = Vector2f::ZERO;
	bool extensionF_ = false;
	func_t updater_;
	int chainH = -1;


	void NomalUpdate();
	void ExtensionUpdate();
	/// <summary>
	/// 鎖鎌を伸ばす方向を決める
	/// </summary>
	/// <param name="input">入力情報</param>
	/// <param name="player">プレイヤー</param>
	void SetDirection(const Input& input, const Player& player);
	/// <summary>
	/// 現在のフレームから鎖鎌の長さを取得する
	/// </summary>
	/// <returns>鎖鎌の長さ</returns>
	int ExpandWidth();
public:
	/// <summary>
	/// 鎖鎌インスタンス
	/// </summary>
	/// <param name="p">プレイヤー</param>
	/// <param name="cm">コリジョン管理用</param>
	/// <param name="c">カメラ</param>
	ChainEquip(std::shared_ptr<Player>& p,
		std::shared_ptr<CollisionManager>cm,
		std::shared_ptr<Camera> c,
		ShadowClone* shadow = nullptr);

	/// <summary>
	/// 攻撃
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="input">入力情報</param>
	void Attack(const Player& player, const Input& input, Vector2f offset = Vector2f::ZERO)override;

	/// <summary>
	/// 追加攻撃
	/// 攻撃時に伸びきった後最初の攻撃と別ベクトルにキーを入れたら追加攻撃
	/// 鎖鎌を振り回す
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="input">入力情報</param>
	void ExtensionAttack(const Player& player, const Input& input)override;
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};

