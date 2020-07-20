#include "Equipment.h"

Equipment::Equipment(std::shared_ptr<CollisionManager> cm):
	collisionManager_(cm)
{
}

void Equipment::ExtendAttack(const Player& player, const Input& input)
{
}
