#include "Thrower.h"
#include <DxLib.h>
#include "../../System/File.h"
#include "../../System/FileManager.h"
#include "../Player/Player.h"
#include "../Stage.h"
#include "../Camera.h"
#include "../Collision/CircleCollider.h"
#include "../Collision/CollisionManager.h"
#include "../Effect.h"
#include "Kunai.h"
#include "../ProjectileManager.h"

namespace
{
    constexpr float narakuY = 1000.0f;
    constexpr int change_AI_intarval = 150;
    constexpr int speed = 5;
    constexpr float jump_power = 15.0f;
    constexpr int attack_distance = 200;
    constexpr int throw_frame = 20;
    constexpr int throw_onepicture_frame = throw_frame / 4;
    constexpr float specialattack_jump_power = 30.0f;
    constexpr float fall_gravity = 0.75f;
    constexpr float jump_gravity = 0.75f;
    constexpr int bullet_speed = 5;
}

Enemy* Thrower::MakeClone()
{
	return new Thrower(player_, effectManager_,collisionManager_, camera_, stage_, projectileManager_);
}

void Thrower::SpecialAttack()
{
    AimPlayer();
    velocity_.y = -jump_power;
    updater_ = &Thrower::SpecialAttackUpdate;
    frame_ = 0;
    animFrame_ = 0;
}

void Thrower::RunUpdate()
{
    if (++frame_ % change_AI_intarval == 1)
    {
        AimPlayer();
        velocity_ *= speed;
    }
    pos_ += velocity_;
    animFrame_ = (animFrame_ + 1) % 15;
    // UŒ‚”»’f
    if (abs(pos_.x - player_->GetPosition().x) < attack_distance) {
        updater_ = &Thrower::ThrowUpdate;
        drawer_ = &Thrower::ThrowDraw;
        animFrame_ = 0;
        frame_ = 0;
    }

    auto seg3 = stage_->GetThreeSegment(pos_);
    //ƒWƒƒƒ“ƒv”»’f 
    if (velocity_.x > 0) {
        if (seg3[2].IsNil() || seg3[2].vec.x == 0) {
            auto diff = seg3[1].End().x - pos_.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                velocity_.y = -jump_power;
                updater_ = &Thrower::JumpUpdate;
            }
        }
    }
    else {
        if (seg3[0].IsNil() || seg3[0].vec.x == 0) {
            auto diff = pos_.x - seg3[1].start.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                velocity_.y = -jump_power;
                updater_ = &Thrower::JumpUpdate;
            }
        }
    }
    // °”»’èi°‚ª‚ ‚ê‚Î°‚Ü‚ÅÀ•W‚ð°‚É•â³j
    if (seg3[1].IsNil())
    {
        pos_.y = narakuY;
    }
    else
    {
        assert(seg3[1].vec.x > 0.0f);
        auto yVariation = seg3[1].vec.y / seg3[1].vec.x;
        if (updater_ == &Thrower::RunUpdate)
        {
            pos_.y = seg3[1].start.y + yVariation * (pos_.x - seg3[1].start.x);
        }
    }
}

void Thrower::RunawayUpdate()
{
    if (++frame_ % change_AI_intarval == 1)
    {
        AimPlayer();
        velocity_.x = -velocity_.x;
        velocity_ *= speed;
    }
    pos_ += velocity_;
    
    animFrame_ = (animFrame_ + 1) % 15;
    // UŒ‚”»’f
    if (fabs(pos_.x - player_->GetPosition().x) > attack_distance){
        updater_ = &Thrower::ThrowUpdate;
        drawer_ = &Thrower::ThrowDraw;
        AimPlayer();
        velocity_ *= speed;
        animFrame_ = 0;
        frame_ = 0;
    }

    auto seg3 = stage_->GetThreeSegment(pos_);
    //ƒWƒƒƒ“ƒv”»’f 
    if (velocity_.x > 0) {
        if (seg3[2].IsNil() || seg3[2].vec.x == 0) {
            auto diff = seg3[1].End().x - pos_.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                velocity_.y = -jump_power;
                updater_ = &Thrower::JumpUpdate;
            }
        }
    }
    else {
        if (seg3[0].IsNil() || seg3[0].vec.x == 0) {
            auto diff = pos_.x - seg3[1].start.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                velocity_.y = -jump_power;
                updater_ = &Thrower::JumpUpdate;
            }
        }
    }
    // °”»’èi°‚ª‚ ‚ê‚Î°‚Ü‚ÅÀ•W‚ð°‚É•â³j
    if (seg3[1].IsNil())
    {
        pos_.y = narakuY;
    }
    else
    {
        assert(seg3[1].vec.x > 0.0f);
        auto yVariation = seg3[1].vec.y / seg3[1].vec.x;
        pos_.y = seg3[1].start.y + yVariation * (pos_.x - seg3[1].start.x);
        
    }
}

void Thrower::FallUpdate()
{
    velocity_.y += fall_gravity;
    pos_ += velocity_;
    auto groundy = stage_->GetGroundY(pos_);
    if (groundy < pos_.y) {
        pos_.y = groundy;
        updater_ = &Thrower::RunUpdate;
        frame_ = 0;
    }
}

void Thrower::JumpUpdate()
{
    velocity_.y += jump_gravity;
    pos_ += velocity_;
    if (velocity_.y >= 0.0f) {
        updater_ = &Thrower::FallUpdate;
        frame_ = 0;
    }
}

void Thrower::ThrowUpdate()
{
    animFrame_ = (animFrame_ + 1) % throw_frame;
    if (animFrame_ == throw_frame - throw_onepicture_frame * 2)
    {
        if (rand() % 3 == 0)
        {
            SpecialAttack();
        }
        else
        {
            auto vel = player_->GetPosition() - pos_;
            vel.Nomarize();
            vel *= bullet_speed;
            projectileManager_.AddProjectile(new Kunai(pos_ + vel + Vector2f(0, -25), vel, camera_));
            collisionManager_->AddCollider(new CircleCollider(projectileManager_.Projectiles().back(), tagEnemyBullet, Circle(Position2f::ZERO, 5.0f)));
        }
    }
    if (fabs(player_->GetPosition().x - pos_.x) > attack_distance) 
    {
        updater_ = &Thrower::RunUpdate;
        drawer_ = &Thrower::RunDraw;
    }
    else if(fabs(player_->GetPosition().x - pos_.x) < attack_distance - 50)
    {
        updater_ = &Thrower::RunawayUpdate;
        drawer_ = &Thrower::RunDraw;
    }
}

void Thrower::SpecialAttackUpdate()
{

    auto lastVelY = velocity_.y;
    if (specialAttackTimer == 0)
    {
        velocity_.y += jump_gravity;
        pos_ += velocity_;
        if (lastVelY > 0.0f)
        {
            specialAttackTimer = 40;
            auto vel = player_->GetPosition() - pos_;
            lockonAngle_ = atan2f(vel.y, vel.x);
            addAngle_ = (vel.x > 0 ? -1.0f : 1.0f)* (DX_PI_F / 18.0f);
        }
    }
    
    if (specialAttackTimer > 0)
    {
        if (--specialAttackTimer == 0)
        {
            updater_ = &Thrower::FallUpdate;
            frame_ = 0;
        }
        else
        {
            if (specialAttackTimer % 5 == 0)
            {
                Vector2f vel(cosf(lockonAngle_), sinf(lockonAngle_));
                vel = vel.Nomarized() * bullet_speed;
                lockonAngle_ += addAngle_;
                projectileManager_.AddProjectile(new Kunai(pos_ + vel + Vector2f(0, -25), vel, camera_));
                collisionManager_->AddCollider(new CircleCollider(projectileManager_.Projectiles().back(), tagEnemyBullet, Circle(Position2f::ZERO, 5.0f)));
            }
        }
    }
    else
    {

    }
    
}

void Thrower::RunDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(
        pos_.x + offset.x, pos_.y, (animFrame_ / 5) * 36, 0, 36, 26,
        18, 25,
        4.0f, 0.0f, runH, true,
        velocity_.x < 0);
}

void Thrower::ThrowDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(pos_.x + offset.x, pos_.y,
        (animFrame_ / 5) * 42, 0, 42, 26,
        18, 25,
        4.0f, 0.0f, throwH_, true,
        velocity_.x < 0);
}

Thrower::Thrower(const std::shared_ptr<Player>& p, 
    std::shared_ptr<EffectManager>& effectManager,
    std::shared_ptr<CollisionManager>colManager,
    std::shared_ptr<Camera> c,
    std::shared_ptr<Stage> stage,
    ProjectileManager& pm):
    Enemy(p, c, stage),
    effectManager_(effectManager),
    collisionManager_(colManager),
    stage_(stage),
    projectileManager_(pm)
{
    updater_ = &Thrower::RunUpdate;
    drawer_ = &Thrower::RunDraw;
    auto& fileMng = FileManager::Instance();
    if (runH == -1)
    {
        runH = fileMng.Load(L"Resource/Image/Enemy/Thrower/run.png")->Handle();
    }
    if (throwH_ == -1)
    {
        throwH_ = fileMng.Load(L"Resource/Image/Enemy/Thrower/throw.png")->Handle();
    }
}
Thrower::~Thrower()
{
}

void Thrower::OnDamage(int damage)
{
}

void Thrower::OnDead()
{
}

void Thrower::Update()
{
    (this->*updater_)();
}

void Thrower::Draw()
{
    (this->*drawer_)();
}

void Thrower::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
    if (another.collider->GetTag() == tagPlayerAtack)
    {
        // Ž€‚Ê
        effectManager_->EmitBlow3(pos_, velocity_.x < 0, camera_);
        isDeletable_ = true;
    }
}

const std::vector<Circle>& Thrower::GetCircles() const
{
    return circles_;
}
