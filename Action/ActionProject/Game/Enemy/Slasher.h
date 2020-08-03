#pragma once
#include "Enemy.h"

class EffectManager;
class Stage;
class Slasher : public Enemy
{
private:

    int frame_ = 0;
    int animFrame_ = 0;
	Enemy* MakeClone() override;
    using Func_t = void (Slasher::*)();

    void RunUpdate();
    void FallUpdate();
    void SlashUpdate();
    void JumpUpdate();
    Func_t updater_;

    void RunDraw();
    void SlashDraw();
    Func_t drawer_;

    std::shared_ptr<EffectManager>effectManager_;
    std::shared_ptr<Stage>stage_;

public:
	Slasher(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& em, std::shared_ptr<Camera> c, std::shared_ptr<Stage>s);
    ~Slasher();
	void OnDamage(int damage);

	void OnDead();
	void Update();
	void Draw();
    /// <summary>
    /// ��������������
    /// </summary>
    /// <param name="c">������������̃R���W�������</param>
    void OnHit(CollisionInfo& c)override;
};

