#include "Equipment.h"


Equipment::Equipment(std::shared_ptr<CollisionManager> cm, std::shared_ptr<Camera> c):
	collisionManager_(cm),
	camera_(c)
{
}

void Equipment::ExtendAttack(const Player& player, const Input& input)
{
}
