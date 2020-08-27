#pragma once
#include "../Projectile.h"

class EffectManager;
class Kunai : public Projectile
{
private:
    int frame_ = 0;
    int bulletH_ = -1;
    float speed_ = 1.0f;
    float centripetalSpeed_ = 0.0f;
    Vector2f initVel_;
 //   std::shared_ptr<EffectManager>effectManager_;
public:
    /// <summary> 
    /// ���C���e�R���X�g���N�^ 
    /// </summary> 
    /// <param name="pos">�������W</param> 
    /// <param name="vel">�������x</param> 
    /// <param name="camera">�J����</param> 
    Kunai(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera>c, std::shared_ptr<EffectManager> effectManager = nullptr);

    /// <summary>
    /// �X�V
    /// </summary>
    void Update()override;

    ///<summary>
    /// �`��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// ��������������
    /// </summary>
    /// <param name="colInfo">�Փˏ��</param>
    void OnHit(CollisionInfo& mine, CollisionInfo& another);
};

