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
	bool isDeletable_ = false;	// �����Ă悢�t���O
	bool isImmortal_ = false;	// �s�Ńt���O
	bool isActive_ = true;	// �A�N�e�B�u�ȃt���O
public:
	Collider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	virtual ~Collider() = default;
	bool OwnerIsDead()const;	
	bool IsDeletable()const;
	std::shared_ptr<Character>GetOwner();
	/// <summary>
	/// �����蔻�蓯�m������������
	/// </summary>
	/// <param name="col">����̓����蔻��</param>
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

