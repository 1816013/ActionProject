#pragma once
#include "Enemy.h"

class EffectManager;
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

    std::shared_ptr<EffectManager>effectManager_;

public:
	Slasher(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& em, std::shared_ptr<Camera> c);
    ~Slasher();
	void OnDamage(int damage);

	void OnDead();
	void Update();
	void Draw();
    /// <summary>
    /// ‰½‚©‚ª“–‚½‚Á‚½
    /// </summary>
    /// <param name="c">“–‚½‚Á‚½‘Šè‚ÌƒRƒŠƒWƒ‡ƒ“î•ñ</param>
    void OnHit(CollisionInfo& c)override;
};

