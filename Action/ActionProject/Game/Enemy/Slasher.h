#pragma once
#include "Enemy.h"
class Slasher : public Enemy
{
private:

    int frame_ = 0;
    int animFrame_ = 0;
	Enemy* MakeClone() override;
    using Func_t = void (Slasher::*)();

    void RunUpdate();
    void SlashUpdate();
    Func_t updater_;

    void RunDraw();
    void SlashDraw();
    Func_t drawer_;

public:
	Slasher(const std::shared_ptr<Player>& p);
    ~Slasher() = default;
	void OnDamage(int damage);

	void OnDead();
	void Update();
	void Draw();
};

