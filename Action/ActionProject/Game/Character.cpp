#include "Character.h"

Character::Character(std::shared_ptr<Camera> camera):camera_(camera)
{
}

const Position2f Character::GetPosition() const
{
	return pos_;
}
