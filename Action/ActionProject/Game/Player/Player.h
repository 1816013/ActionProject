#pragma once
#include "../Character.h"
#include <memory>
#include <vector>
#include <array>

// プレイヤークラス
class GamePlayingScene;
class Equipment;
class CollisionManager;
class Stage;
class FileManager;
class ShadowClone;
class Player : public Character
{
private:
	int runH_[6] = {};
	int jumpH_[4] = {};
	int fallH_[2] = {};
	int shadowMaskH = -1;
	std::vector<std::shared_ptr<Equipment>>equipments_;
	size_t currentEquipmentNo_ = 0;
	Direction direction_;
	GamePlayingScene* gameScene_;
	std::shared_ptr<CollisionManager>collisionManager_;
	std::array<Position2f, 41>moveHistory_;
	size_t currentMoveIndex_ = 0;
	int knockbackfFrame = 0;
	std::vector<std::shared_ptr<ShadowClone>> shadowClones_;

	using Updater_t = void(Player::*)();
	Updater_t updater_;

	using Drawer_t = void(Player::*)(Vector2f, bool);

	Drawer_t drawer_;

	void NomalUpdate();

	void RiseUpdate();

	void FallUpdate();

	void DamageUpdate();

	void RunDraw(Vector2f offset, bool isRight);

	void RizeDraw(Vector2f offset, bool isRight);

	void FallDraw(Vector2f offset, bool isRight);

	void DamageDraw(Vector2f offset, bool isRight);

	void LoadGraphPlayer(const char* key, int* handle, int size, FileManager& fmanager);

	void SetCurrentPosition();
	const Position2f& GetBackTimePosition(size_t t)const;
public:
	Player(GamePlayingScene* g);
	Player() = default;
	~Player();

	/// <summary>
	/// 持っている武器で攻撃する
	/// </summary>
	/// <param name="input">入力参照</param>
	void Attack(const Input& input);

	/// <summary>
	/// 追加攻撃(今は鎖鎌のみ)
	/// </summary>
	/// <param name="input">入力参照</param>
	void ExtensionAttack(const Input& input);

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

	void Jump();

	/// <summary>
	/// 武器変更
	/// </summary>
	void NextEquip();

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	
	size_t CurrentEquipmentNo()const;
	Direction Direction()const;

	void OnHit(CollisionInfo& mine, CollisionInfo& another)override;

	float gravity_ = 0.0f;
	float velY_ = 0.0f;
};

