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
}

Enemy* Thrower::MakeClone()
{
	return new Thrower(player_, effectManager_, camera_, stage_, projectileManager_);
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
    velocity_.y += 0.75f;
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
    velocity_.y += 0.75f;
    pos_ += velocity_;
    if (velocity_.y >= 0.0f) {
        updater_ = &Thrower::FallUpdate;
        frame_ = 0;
    }
}

void Thrower::ThrowUpdate()
{
    animFrame_ = (animFrame_ + 1) % 20;
    if (animFrame_ == 19)
    {
        auto vel = player_->GetPosition() -  pos_;
        vel.Nomarize();
        vel *= 5;
        projectileManager_.AddProjectile(new Kunai(pos_ + vel, vel, camera_));
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
    velocity_.y += 0.75f;
    pos_ += velocity_;
    if (velocity_.y >= 0.0f) {
        updater_ = &Thrower::FallUpdate;
        frame_ = 0;
    }
    animFrame_ = (animFrame_ + 1) % 20;
    if (animFrame_ == 19)
    {
        auto vel = player_->GetPosition() - pos_;
        vel.Nomarize();
        vel *= 5;
        projectileManager_.AddProjectile(new Kunai(pos_ + vel, vel, camera_));
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
    std::shared_ptr<Camera> c,
    std::shared_ptr<Stage> stage,
    ProjectileManager& pm):
    Enemy(p, c, stage),
    effectManager_(effectManager),
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
