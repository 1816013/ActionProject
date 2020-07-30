#include "Slasher.h"
#include "../Player/Player.h"
#include <DxLib.h>
#include "../Collider.h"
#include "../Effect.h"
#include "../../Camera.h"
#include "../../Stage.h"

namespace
{
    int runH = -1;
    int slashH = -1;
}
Slasher::Slasher(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& em, std::shared_ptr<Camera> c,std::shared_ptr<Stage>s) :
    Enemy(p, c),
    effectManager_(em),
    stage_(s)
{
    updater_ = &Slasher::RunUpdate;
    drawer_ = &Slasher::RunDraw;
    runH = LoadGraph(L"Resource/Image/Enemy/Slasher/run.png");
    slashH = LoadGraph(L"Resource/Image/Enemy/Slasher/slash.png");
   
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
    if (frame_ % 150 == 0)
    {
        AimPlayer();
        velocity_ *= 5;
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
    auto groundY = stage_->GetGroundY(pos_);
    pos_.y = groundY;
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
    DrawRectRotaGraph2(
        pos_.x + offset.x, pos_.y,(animFrame_ / 5) * 36,0, 36, 26,
        18, 25,
        4.0f, 0.0f, runH, true,
        velocity_.x < 0);
}

void Slasher::SlashDraw()
{
    auto offset = camera_->ViewOffset();
    DrawRectRotaGraph2(pos_.x + offset.x, pos_.y,
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
    if (pos_.x < rc.Left() + xmargin || rc.Right() - xmargin < pos_.x) {
        return;
    }
    (this->*drawer_)();
}

void Slasher::OnHit(CollisionInfo& col)
{
    if (col.collider->GetTag() == tagPlayerAtack)
    {
        // Ž€‚Ê
        effectManager_->EmitBlow3(pos_, velocity_.x < 0, camera_);
        isDeletable_ = true;
    }
}
