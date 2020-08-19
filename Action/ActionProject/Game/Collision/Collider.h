#pragma once
#include <memory>
#include <string>


constexpr const char* tagPlayerAtack = "pAtk";
constexpr const char* tagEnemyDamage = "eDmg";

class Camera;
class Character;
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
	bool OwnerIsDead()const;	
	bool IsDeletable()const;
	std::shared_ptr<Character>GetOwner();
	/// <summary>
	/// 当たり判定同士が当たったか
	/// </summary>
	/// <param name="col">相手の当たり判定</param>
	/// <returns></returns>
	virtual bool IsHit(std::shared_ptr<Collider> col) = 0;
	const std::string& GetTag()const;

	void Suside();

	void Sleep();

	void Awake();

	bool IsAcrive()const;

	virtual void Draw(std::shared_ptr<Camera>c) {};
};

struct CollisionInfo
{
	std::shared_ptr<Collider>collider;
};

