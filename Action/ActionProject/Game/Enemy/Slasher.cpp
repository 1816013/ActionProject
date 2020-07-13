#include "Slasher.h"
#include "../Player/Player.h"
#include <DxLib.h>

namespace
{
    int runH = -1;
    int slashH = -1;
}
Slasher::Slasher(const std::shared_ptr<Player>& p) : Enemy(p)
{
    updater_ = &Slasher::RunUpdate;
    drawer_ = &Slasher::RunDraw;
    runH = LoadGraph(L"Resource/Image/Enemy/Slasher/run.png");
    slashH = LoadGraph(L"Resource/Image/Enemy/Slasher/slash.png");
   
}


Enemy* Slasher::MakeClone()
{
	return new Slasher(player_);
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
    if (fabsf(pos_.x - player_->Position().x) < 50) {
        updater_ = &Slasher::SlashUpdate;
        drawer_ = &Slasher::SlashDraw;
        animFrame_ = 0;
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
    DrawRectRotaGraph(
        pos_.x, pos_.y,(animFrame_ / 5) * 36, 0, 36, 26,
        4.0f, 0.0f, runH, true,
        velocity_.x < 0);
}

void Slasher::SlashDraw()
{
    DrawRectRotaGraph(pos_.x, pos_.y,
        (animFrame_ / 5) * 42, 0, 42, 26,
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
    (this->*drawer_)();
}
