#pragma once
#include "../Projectile.h"
class EffectManager;
class AsuraBullet : public Projectile
{
private:
    int frame_ = 0;
    int bulletH_ = -1;
    float speed_ = 1.0f;
    float centripetalSpeed_ = 0.0f;
    Vector2f initVel_;
    std::shared_ptr<EffectManager>effectManager_;
public:
    /// <summary> 
    /// 阿修羅弾コンストラクタ 
    /// </summary> 
    /// <param name="pos">初期座標</param> 
    /// <param name="vel">初期速度</param> 
    /// <param name="camera">カメラ</param> 
    AsuraBullet(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera>c, std::shared_ptr<EffectManager> effectManager);

    void Update()override;
    ///<summary>
    /// Drawは最後の派生クラスで実装する
    /// </summary>
    void Draw()override;

    void OnHit(CollisionInfo& colInfo);
};
