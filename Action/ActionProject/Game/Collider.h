#pragma once
#include <memory>
#include <string>

class Character;
class Collider
{
private:
	std::string tag_;
	std::weak_ptr<Character> owner_;
public:
	virtual ~Collider() = default;
	bool OwnerIsDead()const;	
	std::shared_ptr<Character>GetOwner();
	/// <summary>
	/// �����蔻�蓯�m������������
	/// </summary>
	/// <param name="col">����̓����蔻��</param>
	/// <returns></returns>
	virtual bool IsHit(Collider* col) = 0;

};

