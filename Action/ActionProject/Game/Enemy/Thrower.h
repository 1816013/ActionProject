#pragma once
#include "Enemy.h"

class EffectManager;
class Stage;
class ProjectileManager;
class CollisionManager;
class Thrower : public Enemy
{
private:
    int runH = -1;
    int throwH_ = -1;
    int frame_ = 0;
    int animFrame_ = 0;
    Enemy* MakeClone() override;
    using Func_t = void (Thrower::*)();
    int specialAttackTimer = 0;
    float lockonAngle_ = 0.0f;
    float addAngle_ = 0.0f;

    void SpecialAttack();

    //更新
    void RunUpdate();
    void RunawayUpdate();
    void FallUpdate();
    void JumpUpdate();
    void ThrowUpdate();
    void SpecialAttackUpdate();
    Func_t updater_;

    // 描画
    void RunDraw();
    void ThrowDraw();

    Func_t drawer_;

    std::shared_ptr<EffectManager>effectManager_;
    std::shared_ptr<Stage>stage_;
    ProjectileManager& projectileManager_;
    std::shared_ptr<CollisionManager>collisionManager_;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="p">プレイヤー</param>
    /// <param name="effectManager">エフェクト管理用クラス</param>
    /// <param name="c">カメラ</param>
    /// <param name="stage">ステージ</param>
    Thrower(const std::shared_ptr<Player>& p, 
        std::shared_ptr<EffectManager>& effectManager,
        std::shared_ptr<CollisionManager>colManager,
        std::shared_ptr<Camera> c,
        std::shared_ptr<Stage>stage,
        ProjectileManager& pm);
    ~Thrower();

    /// <summary>
    /// ダメージを受けた
    /// </summary>
    /// <param name="damage">ダメージ値</param>
    void OnDamage(int damage);

    /// <summary>
    /// 死んだ
    /// </summary>
    void OnDead();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 何かが当たった
    /// </summary>
    /// <param name="c">当たった相手のコリジョン情報</param>
    void OnHit(CollisionInfo& mine, CollisionInfo& another)override;

    /// <summary>
    /// キャラが持っている円衝突情報を全て取得する
    /// </summary>
    /// <returns></returns>
    const std::vector<Circle>& GetCircles()const override;
};

