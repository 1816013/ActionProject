#include "Enemy.h"
#include "../Player/Player.h"
#include "../Stage.h"

Enemy::Enemy(const std::shared_ptr<Player>& p, std::shared_ptr<Camera> c, std::shared_ptr<Stage>s) : player_(p), Character(c), stage_(s)
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

void Enemy::SetWeakRef(std::shared_ptr<Enemy> ref)
{
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
