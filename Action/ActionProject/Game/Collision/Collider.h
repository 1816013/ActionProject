#pragma once
#include <memory>
#include <string>


constexpr const char* tagPlayerAtack = "pAtk";
constexpr const char* tagEnemyDamage = "eDmg";
constexpr const char* tagPlayerDamage = "pDmg";
constexpr const char* tagEnemyBullet = "eblt";
constexpr const char* tagEnemyAttack = "eAtk";

class Camera;
class Character;
/// <summary>
/// 衝突情報基底クラス
/// </summary>
class Collider
{
private:
	std::string tag_;
	std::weak_ptr<Character> owner_;
protected:
	bool isDeletable_ = false;	// 消えてよいフラグ
	bool isImmortal_ = false;	// 不滅フラグ
	bool isActive_ = true;	// アクティブなフラグ
public:
	Collider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	virtual ~Collider() = default;

	/// <summary>
	/// 衝突情報を保持しているキャラが死んだ
	/// </summary>
	/// <returns>true:死んだ</returns>
	bool OwnerIsDead()const;	

	/// <summary>
	/// 衝突情報を消してよいか
	/// </summary>
	/// <returns>true:消してよい</returns>
	bool IsDeletable()const;

	/// <summary>
	/// 衝突情報を持っているキャラクターを取得する
	/// </summary>
	/// <returns>衝突情報を持っているキャラクター</returns>
	std::shared_ptr<Character>GetOwner();

	/// <summary>
	/// 当たり判定同士が当たったか
	/// </summary>
	/// <param name="col">相手の当たり判定</param>
	/// <returns></returns>
	virtual bool IsHit(std::shared_ptr<Collider> col) = 0;

	/// <summary>
	/// 衝突情報のタグを取得する
	/// </summary>
	/// <returns>衝突情報のタグ</returns>
	const std::string& GetTag()const;

	/// <summary>
	/// 衝突情報を消す
	/// </summary>
	void Suside();

	/// <summary>
	/// 衝突情報を一時的に無効化する
	/// </summary>
	void Sleep();

	/// <summary>
	/// 無効化した衝突情報を有効化する
	/// </summary>
	void Awake();

	/// <summary>
	/// 衝突情報が有効かどうか
	/// </summary>
	/// <returns>true:有効</returns>
	bool IsAcrive()const;

	virtual void Draw(std::shared_ptr<Camera>c) {};
};

/// <summary>
/// 衝突情報構造体
/// </summary>
struct CollisionInfo
{
	std::shared_ptr<Collider>collider;	// 衝突情報の参照
};

