#pragma once
#include "Equipment.h"

class FanCollider;
class ShadowClone;
class SwordEquip :
	public Equipment
{
private:
	int frame_;
	std::shared_ptr<Player>& player_;
	FanCollider* fanCollider_ = nullptr;
	using func_t = void(SwordEquip::*)();
	ShadowClone* shadow_;
	Vector2f offset_ = Vector2f::ZERO;
	func_t updater_;
	SlashShape slash_;
	bool isRight_;

	void NomalUpdate();
public:
	/// <summary>
	/// 剣インスタンス
	/// </summary>
	/// <param name="p">プレイヤー</param>
	/// <param name="cm">コリジョン管理用</param>
	/// <param name="c">カメラ</param>
	SwordEquip(std::shared_ptr<Player>& p,
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
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};

