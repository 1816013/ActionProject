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
	bool isDeletable_ = false;
	bool isImmortal_ = false;
public:
	Collider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	virtual ~Collider() = default;
	bool OwnerIsDead()const;	
	bool IsDeletable()const;
	std::shared_ptr<Character>GetOwner();
	/// <summary>
	/// “–‚½‚è”»’è“¯Žm‚ª“–‚½‚Á‚½‚©
	/// </summary>
	/// <param name="col">‘ŠŽè‚Ì“–‚½‚è”»’è</param>
	/// <returns></returns>
	virtual bool IsHit(std::shared_ptr<Collider> col) = 0;
	const std::string& GetTag()const;

	void Suside();

	virtual void Draw(std::shared_ptr<Camera>c) {};
};

struct CollisionInfo
{
	std::shared_ptr<Collider>collider;
};

