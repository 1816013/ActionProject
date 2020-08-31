#pragma once
#include "Enemy.h"

class EffectManager;
class CollisionManager;
class Collider;
/// <summary>
/// 侍雑魚敵
/// </summary>
class Samurai : public Enemy
{
private:
    int idleH_ = -1;
    int runH = -1;
    int HslashH = -1;
    int VslashH_ = -1;
    int damageH_ = -1;
    int frame_ = 0;
    int animFrame_ = 0;
    int damageTimer = 0;

    std::shared_ptr<CollisionManager>collisionManager_;
    std::vector<Circle>circles_;
    std::weak_ptr<Collider> slashCol_;
    std::weak_ptr<Enemy>weakThis_;

    bool slashed = false;
    Enemy* MakeClone() override;
    using Func_t = void (Samurai::*)();
    Func_t lastUpdater_;

    void SetWeakRef(std::shared_ptr<Enemy>ref)override;

    //更新
    void IdleUpdate();
    void RunUpdate();
    void Jump();
    void HSlash();
    void VSlash();
    void JumpUpdate();
    void FallUpdate();
    void DamageUpdate();
    void HSlashUpdate();
    void VSlashUpdate();
    
    Func_t updater_;

    // 描画
    void IdleDraw();
    void RunDraw();
    void FallDraw();
    void DamageDraw();
    void HSlashDraw();
    void VSlashDraw();
    Func_t drawer_;

    std::shared_ptr<EffectManager>effectManager_;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="p">プレイヤー</param>
    /// <param name="effectManager">エフェクト管理用クラス</param>
    /// <param name="c">カメラ</param>
    /// <param name="stage">ステージ</param>
    Samurai(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& effectManager, std::shared_ptr<CollisionManager>& collisionManager, std::shared_ptr<Camera> c, std::shared_ptr<Stage>stage);
    ~Samurai();

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

