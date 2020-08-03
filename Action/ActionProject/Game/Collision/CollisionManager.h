#pragma once
#include <list>
#include <memory>

class Collider;
class Camera;
/// <summary>
/// Õ“Ë”»’è‚ğŠÇ—‚·‚é
/// </summary>
class CollisionManager
{
private:
	std::list<std::shared_ptr<Collider>>colliders_;
public:
	/// <summary>
	/// ‘S‚Ä‚ÌƒRƒŠƒWƒ‡ƒ“‚ğ”»’è‚·‚é
	/// </summary>
	void Update();

	void DebugDraw(std::shared_ptr<Camera>c);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="collider"></param>
	void AddCollider(Collider* collider);

};

