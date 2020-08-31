#pragma once
#include "Enemy.h"

class EffectManager;
class CollisionManager;
class Collider;
/// <summary>
/// ���G���G
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

    //�X�V
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

    // �`��
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
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="p">�v���C���[</param>
    /// <param name="effectManager">�G�t�F�N�g�Ǘ��p�N���X</param>
    /// <param name="c">�J����</param>
    /// <param name="stage">�X�e�[�W</param>
    Samurai(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& effectManager, std::shared_ptr<CollisionManager>& collisionManager, std::shared_ptr<Camera> c, std::shared_ptr<Stage>stage);
    ~Samurai();

    /// <summary>
    /// �_���[�W���󂯂�
    /// </summary>
    /// <param name="damage">�_���[�W�l</param>
    void OnDamage(int damage);

    /// <summary>
    /// ����
    /// </summary>
    void OnDead();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    /// <summary>
    /// ��������������
    /// </summary>
    /// <param name="c">������������̃R���W�������</param>
    void OnHit(CollisionInfo& mine, CollisionInfo& another)override;

    /// <summary>
    /// �L�����������Ă���~�Փˏ���S�Ď擾����
    /// </summary>
    /// <returns></returns>
    const std::vector<Circle>& GetCircles()const override;
};

