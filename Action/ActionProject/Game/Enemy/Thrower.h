#pragma once
#include "Enemy.h"

class EffectManager;
class Stage;
class ProjectileManager;
class Thrower : public Enemy
{
private:
    int runH = -1;
    int throwH_ = -1;
    int frame_ = 0;
    int animFrame_ = 0;
    Enemy* MakeClone() override;
    using Func_t = void (Thrower::*)();
    int specialAttackTimmer = 30;

    void SpecialAttack();

    //�X�V
    void RunUpdate();
    void RunawayUpdate();
    void FallUpdate();
    void JumpUpdate();
    void ThrowUpdate();
    void SpecialAttackUpdate();
    Func_t updater_;

    // �`��
    void RunDraw();
    void ThrowDraw();

    Func_t drawer_;

    std::shared_ptr<EffectManager>effectManager_;
    std::shared_ptr<Stage>stage_;
    ProjectileManager& projectileManager_;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="p">�v���C���[</param>
    /// <param name="effectManager">�G�t�F�N�g�Ǘ��p�N���X</param>
    /// <param name="c">�J����</param>
    /// <param name="stage">�X�e�[�W</param>
    Thrower(const std::shared_ptr<Player>& p, 
        std::shared_ptr<EffectManager>& effectManager, 
        std::shared_ptr<Camera> c,
        std::shared_ptr<Stage>stage,
        ProjectileManager& pm);
    ~Thrower();

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

