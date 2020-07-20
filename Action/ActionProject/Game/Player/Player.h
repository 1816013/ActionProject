#pragma once
#include "../Character.h"
#include <memory>
#include <vector>

// プレイヤークラス
class GamePlayingScene;
class Equipment;
class CollisionManager;
class Player : public Character
{
private:
	std::vector<std::shared_ptr<Equipment>>equipments_;
	size_t currentEquipmentNo_ = 0;
	Direction direction_;
	std::shared_ptr<CollisionManager>collisionManager_;
public:
	Player(GamePlayingScene* g);
	Player() = default;
	~Player();
	/// <summary>
	/// 持っている武器で攻撃する
	/// </summary>
	/// <param name="input">入力参照</param>
	void Attack(const Input& input);
	void ExtendAttack(const Input& input);
	/// <summary>
	/// プレイヤーの座標を設定する
	/// </summary>
	/// <param name="pos">新たな座標</param>
	void SetPosition(const Position2f& pos);
	/// <summary>
	/// プレイヤーを移動させる
	/// </summary>
	/// <param name="v">移動ベクトル</param>
	void Move(const Vector2f& v);
	void NextEquip();
	void Update()override;
	void Draw()override;
	//const Position2f Position()const;
	size_t CurrentEquipmentNo()const;
	Direction Direction()const;

	void OnHit(CollisionInfo& c);
};

