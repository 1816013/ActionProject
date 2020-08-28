#include "Samurai.h"
#include "../Player/Player.h"
#include <DxLib.h>
#include <cassert>
#include "../Collision/Collider.h"
#include "../Effect.h"
#include "../Camera.h"
#include "../Stage.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"

namespace
{
    constexpr float narakuY = 1000.0f;
    constexpr int change_AI_intarval = 150;
    constexpr int speed = 5;
    constexpr float jump_power = 15.0f;
    constexpr int slash_distance = 150;
    constexpr int pict_width = 200;
    constexpr int pict_hight = 200;
    constexpr int samurai_botom_y = 127;
    constexpr int one_picture_frame = 5;
    constexpr int run_pict_num = 8;
    constexpr int Hslash_pict_num = 4;
    constexpr int damage_pict_num = 3;
    constexpr int damage_frames = one_picture_frame * damage_pict_num;
    constexpr int run_frames = one_picture_frame * run_pict_num;
    constexpr int Hslash_frames = one_picture_frame * Hslash_pict_num;
}
Samurai::Samurai(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& em, std::shared_ptr<Camera> c, std::shared_ptr<Stage>s) :
    Enemy(p, c, s),
    effectManager_(em)
{
    life_ = 10;
    isActive_ = true;
    lastUpdater_ = &Samurai::IdleUpdate;
    updater_ = &Samurai::RunUpdate;
    drawer_ = &Samurai::RunDraw;
    auto& fileMng = FileManager::Instance();
    if (idleH_ == -1)
    {
        idleH_ = fileMng.Load(L"Resource/Image/Enemy/Samurai/Idle.png")->Handle();
    }
    if (runH == -1)
    {
        runH = fileMng.Load(L"Resource/Image/Enemy/Samurai/Run.png")->Handle();
    }
    if (HslashH == -1)
    {
        HslashH = fileMng.Load(L"Resource/Image/Enemy/Samurai/HAttack.png")->Handle();
    }
    if (VslashH_ == -1)
    {
        VslashH_ = fileMng.Load(L"Resource/Image/Enemy/Samurai/VAttack.png")->Handle();
    }
    if (damageH_ == -1)
    {
        damageH_ = fileMng.Load(L"Resource/Image/Enemy/Samurai/damage.png")->Handle();
    }
}

Samurai::~Samurai()
{
}


Enemy* Samurai::MakeClone()
{
    return new Samurai(player_, effectManager_, camera_, stage_);
}

void Samurai::IdleUpdate()
{
}

void Samurai::RunUpdate()
{
    
    if (frame_ % change_AI_intarval == 0)
    {
        AimPlayer();
        velocity_ *= speed;
        slashed = false;
    }
    ++frame_;
    pos_ += velocity_;
    animFrame_ = (animFrame_ + 1) % run_frames;
    if (fabs(pos_.x - player_->GetPosition().x) < slash_distance && !slashed)
    {
        slashed = true;
        HSlash();      
    }

    auto seg3 = stage_->GetThreeSegment(pos_);
    //ジャンプ判断 
    if (velocity_.x > 0) {
        if (seg3[2].IsNil() || seg3[2].vec.x == 0) {
            auto diff = seg3[1].End().x - pos_.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                Jump();
            }
        }
    }
    else {
        if (seg3[0].IsNil() || seg3[0].vec.x == 0) {
            auto diff = pos_.x - seg3[1].start.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                Jump();
            }
        }
    }
    // 床判定（床があれば床まで座標を床に補正）
    if (seg3[1].IsNil())
    {
        pos_.y = narakuY;
    }
    else
    {
        assert(seg3[1].vec.x > 0.0f);
        auto yVariation = seg3[1].vec.y / seg3[1].vec.x;
        if (updater_ == &Samurai::RunUpdate)
        {
            pos_.y = seg3[1].start.y + yVariation * (pos_.x - seg3[1].start.x);
        }
    }
    

}
void Samurai::Jump()
{
    velocity_.y = -jump_power;
    updater_ = &Samurai::JumpUpdate;
}
void Samurai::HSlash()
{
    updater_ = &Samurai::HSlashUpdate;
    drawer_ = &Samurai::HSlashDraw;
    animFrame_ = 0;
    frame_ = 0;
}
void Samurai::VSlash()
{
    slashed = true;
    updater_ = &Samurai::VSlashUpdate;
    drawer_ = &Samurai::VSlashDraw;
    animFrame_ = 0;
    frame_ = 0;
}
void Samurai::JumpUpdate()
{
    velocity_.y += 0.75f;
    pos_ += velocity_;
    if (velocity_.y >= 0.0f) {
        updater_ = &Samurai::FallUpdate;
        frame_ = 0;
    }
}

void Samurai::FallUpdate()
{
    velocity_.y += 0.75f;
    pos_ += velocity_;
    auto groundy = stage_->GetGroundY(pos_);
    if (groundy < pos_.y) {
        pos_.y = groundy;
        updater_ = &Samurai::RunUpdate;
        frame_ = 0;
    }
    if (fabs(pos_.x - player_->GetPosition().x) < slash_distance * 2)
    {
        VSlash();
    }
}

void Samurai::DamageUpdate()
{
    animFrame_ = (animFrame_ + 1) % damage_frames / damage_pict_num;
    if (--damageTimer == 0)
    {
        updater_ = lastUpdater_;
        drawer_ = &Samurai::RunDraw;
        if (updater_ != &Samurai::JumpUpdate && updater_ != &Samurai::FallUpdate)
        {
            if (rand() % 5 == 0)
            {
                if (fabs(pos_.x - player_->GetPosition().x) < slash_distance && !slashed)
                {
                    HSlash();
                }
                else
                {
                    Jump();
                }
            }
            else
            {
                Jump();
            }
        }
        
    }
    auto groundy = stage_->GetGroundY(pos_);
    if (groundy < pos_.y) {
        pos_.y = groundy;
        updater_ = &Samurai::RunUpdate;
        frame_ = 0;
    }
}

void Samurai::HSlashUpdate()
{
    animFrame_ = (animFrame_ + 1) % Hslash_frames;
    if (animFrame_ == 0) {
        slashed = true;
        frame_ = 1;
        updater_ = &Samurai::RunUpdate;
        drawer_ = &Samurai::RunDraw;
    }
}

void Samurai::VSlashUpdate()
{
    animFrame_ = (animFrame_ + 1) % Hslash_frames;
    if (animFrame_ == 0) {
        updater_ = &Samurai::RunUpdate;
        drawer_ = &Samurai::RunDraw;
    }
    velocity_.y += 0.75f;
    pos_ += velocity_;
    auto groundy = stage_->GetGroundY(pos_);
    if (groundy < pos_.y) {
        pos_.y = groundy;
        updater_ = &Samurai::RunUpdate;
        drawer_ = &Samurai::RunDraw;
        frame_ = 0;
    }
}
void Samurai::IdleDraw()
{
}

void Samurai::RunDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(
        pos_.x + offset.x, pos_.y, 
        (animFrame_ / one_picture_frame) * pict_width, 0,
        pict_width, pict_hight,
        pict_width / 2, samurai_botom_y,
        2.0f, 0.0f, runH, true,
        velocity_.x < 0);
}

void Samurai::FallDraw()
{
}

void Samurai::DamageDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(pos_.x + offset.x, pos_.y,
        (animFrame_ / one_picture_frame) * pict_width, 0,
        pict_width, pict_hight,
        pict_width / 2, samurai_botom_y,
        2.0f, 0.0f, damageH_, true,
        velocity_.x < 0);
}

void Samurai::HSlashDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(pos_.x + offset.x, pos_.y,
        (animFrame_ / one_picture_frame) * pict_width, 0,
        pict_width, pict_hight,
        pict_width / 2, samurai_botom_y,
        2.0f, 0.0f, HslashH, true,
        velocity_.x < 0);
}

void Samurai::VSlashDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(pos_.x + offset.x, pos_.y,
        (animFrame_ / one_picture_frame) * pict_width, 0,
        pict_width, pict_hight,
        pict_width / 2, samurai_botom_y,
        2.0f, 0.0f, VslashH_, true,
        velocity_.x < 0);
}


void Samurai::OnDamage(int damage)
{
    life_ -= damage;
   
    if (life_ <= 0)
    {
        OnDead();
    }
    else
    {
        AimPlayer();
        velocity_ *= speed;
        damageTimer = 40;
        updater_ = &Samurai::DamageUpdate;
        drawer_ = &Samurai::DamageDraw;
    }
}

void Samurai::OnDead()
{
    effectManager_->EmitBlow3(pos_, velocity_.x < 0, camera_);
    isDeletable_ = true;
}

void Samurai::Update()
{
    (this->*updater_)();
}

void Samurai::Draw()
{
    auto rc = camera_->GetViewRange();
    constexpr int xmargin = 25;
    if (pos_.x < rc.Left() - xmargin || rc.Right() + xmargin < pos_.x) {
        return;
    }
    (this->*drawer_)();
}

void Samurai::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
    if (another.collider->GetTag() == tagPlayerAtack)
    {
        
        if (updater_ == &Samurai::DamageUpdate)
        {
            return;
        }
        lastUpdater_ = updater_;
        // ダメージ
        OnDamage(1);
    }
}

const std::vector<Circle>& Samurai::GetCircles() const
{
    return circles_;
}
