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
	/// “–‚½‚è”»’è“¯Žm‚ª“–‚½‚Á‚½‚©
	/// </summary>
	/// <param name="col">‘ŠŽè‚Ì“–‚½‚è”»’è</param>
	/// <returns></returns>
	virtual bool IsHit(Collider* col) = 0;

};

