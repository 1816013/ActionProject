#pragma once
#include <memory>
#include <string>

class Character;
class Collider
{
private:
	std::string tag_;
	std::weak_ptr<Character> owner_;
	bool isActive_ = false;
public:
	Collider(std::shared_ptr<Character> owner, const char* tag = "");
	virtual ~Collider() = default;
	bool OwnerIsDead()const;	
	std::shared_ptr<Character>GetOwner();
	/// <summary>
	/// �����蔻�蓯�m������������
	/// </summary>
	/// <param name="col">����̓����蔻��</param>
	/// <returns></returns>
	virtual bool IsHit(std::shared_ptr<Collider> col) = 0;
	const std::string& GetTag()const;
};

struct CollisionInfo
{
	std::shared_ptr<Collider>collider;
};
