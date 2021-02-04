#include "Slasher.h"
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
}
Slasher::Slasher(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& em, std::shared_ptr<Camera> c,std::shared_ptr<Stage>s) :
    Enemy(p, c, s),
    effectManager_(em)
{
    updater_ = &Slasher::RunUpdate;
    drawer_ = &Slasher::RunDraw;
    auto& fileMng = FileManager::Instance();
    if (runH == -1)
    {
        runH = fileMng.Load(L"Resource/Image/Enemy/Slasher/run.png")->Handle();
    }
    if (slashH == -1)
    {
        slashH = fileMng.Load(L"Resource/Image/Enemy/Slasher/slash.png")->Handle();
    }
}

Slasher::~Slasher()
{
}


Enemy* Slasher::MakeClone()
{
	return new Slasher(player_, effectManager_, camera_, stage_);
}

void Slasher::RunUpdate()
{
    if (frame_ % change_AI_intarval == 0)
    {
        AimPlayer();
        velocity_ *= speed;
    }
    pos_ += velocity_;
    ++frame_;
    animFrame_ = (animFrame_ + 1) % 15;
    if (abs(pos_.x - player_->GetPosition().x) < 50 && frame_ > 60) {
        updater_ = &Slasher::SlashUpdate;
        drawer_ = &Slasher::SlashDraw;
        animFrame_ = 0;
        frame_ = 0;
    }

    auto seg3 = stage_->GetThreeSegment(pos_);
    //ジャンプ判断 
    if (velocity_.x > 0) {
        if (seg3[2].IsNil() || seg3[2].vec.x == 0) {
            auto diff = seg3[1].End().x - pos_.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                velocity_.y = -jump_power;
                updater_ = &Slasher::JumpUpdate;
            }
        }
    }
    else {
        if (seg3[0].IsNil() || seg3[0].vec.x == 0) {
            auto diff = pos_.x - seg3[1].start.x;
            if (0 < diff && diff <= fabsf(velocity_.x) * 10) {
                velocity_.y = -jump_power;
                updater_ = &Slasher::JumpUpdate;
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
        if (updater_ == &Slasher::RunUpdate)
        {
            pos_.y = seg3[1].start.y + yVariation * (pos_.x - seg3[1].start.x);
        }
    }
}
void Slasher::JumpUpdate()
{
    velocity_.y += 0.75f;
    pos_ += velocity_;
    if (velocity_.y >= 0.0f) {
        updater_ = &Slasher::FallUpdate;
        frame_ = 0;
    }
}

void Slasher::FallUpdate()
{
    velocity_.y += 0.75f;
    pos_ += velocity_;
    auto groundy = stage_->GetGroundY(pos_);
    if (groundy < pos_.y) {
        pos_.y = groundy;
        updater_ = &Slasher::RunUpdate;
        frame_ = 0;
    }
}

void Slasher::SlashUpdate()
{
    animFrame_ = (animFrame_ + 1) % 20;
    if (animFrame_ == 0) {
        frame_ = 1;
        updater_ = &Slasher::RunUpdate;
        drawer_ = &Slasher::RunDraw;
    }
}



void Slasher::RunDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(
        pos_.x + offset.x, pos_.y,(animFrame_ / 5) * 36,0, 36, 26,
        18, 25,
        4.0f, 0.0f, runH, true,
        velocity_.x < 0);
}

void Slasher::SlashDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2F(pos_.x + offset.x, pos_.y,
        (animFrame_ / 5) * 42, 0, 42, 26,
        18, 25,
        4.0f, 0.0f, slashH, true,
        velocity_.x < 0);
}


void Slasher::OnDamage(int damage)
{
}

void Slasher::OnDead()
{
}

void Slasher::Update()
{
    (this->*updater_)();
}

void Slasher::Draw()
{
    auto rc = camera_->GetViewRange();
    constexpr int xmargin = 25;
    if (pos_.x < rc.Left() - xmargin || rc.Right() + xmargin < pos_.x) {
        return;
    }
    (this->*drawer_)();
}

void Slasher::OnHit(CollisionInfo& mine, CollisionInfo& another)
{
    if (another.collider->GetTag() == tagPlayerAtack)
    {
        // 死ぬ
        effectManager_->EmitBlow3(pos_, velocity_.x < 0, camera_);
        isDeletable_ = true;
    }
}

const std::vector<Circle>& Slasher::GetCircles() const
{
    return circles_;
}
