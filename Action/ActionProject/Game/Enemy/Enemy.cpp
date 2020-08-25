#include "Enemy.h"
#include "../Player/Player.h"

Enemy::Enemy(const std::shared_ptr<Player>& p, std::shared_ptr<Camera> c) : player_(p), Character(c)
{
}

Enemy* Enemy::MakeClone()
{
	return nullptr;
}

void Enemy::AimPlayer()
{
	velocity_ = player_->GetPosition() - pos_;
	velocity_.y = 0;
	velocity_.Nomarize(); 
}

void Enemy::SetPosition(const Position2f& pos)
{
	pos_ = pos;
}

const Vector2f& Enemy::GetVelocity() const
{
	return velocity_;
}

void Enemy::SetVelocity(const Vector2f& vel)
{
	velocity_ = vel;
}

bool Enemy::IsDead() const
{
	return life_ <= 0;
}

bool Enemy::IsDeletable() const
{
	return isDeletable_;
}

void Enemy::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
}
