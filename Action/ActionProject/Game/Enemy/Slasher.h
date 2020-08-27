#pragma once
#include "Enemy.h"

class EffectManager;

/// <summary>
/// 雑魚敵、近づいて攻撃してくる
/// </summary>
class Slasher : public Enemy
{
private:
    int runH = -1;
    int slashH = -1;
    int frame_ = 0;
    int animFrame_ = 0;
	Enemy* MakeClone() override;
    using Func_t = void (Slasher::*)();

    //更新
    void RunUpdate();
    void FallUpdate();
    void SlashUpdate();
    void JumpUpdate();
    Func_t updater_;

    // 描画
    void RunDraw();
    void SlashDraw();
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
	Slasher(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& effectManager, std::shared_ptr<Camera> c, std::shared_ptr<Stage>stage);
    ~Slasher();

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

