#pragma once
#include "Enemy.h"

class EffectManager;

/// <summary>
/// �G���G�A�߂Â��čU�����Ă���
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

    //�X�V
    void RunUpdate();
    void FallUpdate();
    void SlashUpdate();
    void JumpUpdate();
    Func_t updater_;

    // �`��
    void RunDraw();
    void SlashDraw();
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
	Slasher(const std::shared_ptr<Player>& p, std::shared_ptr<EffectManager>& effectManager, std::shared_ptr<Camera> c, std::shared_ptr<Stage>stage);
    ~Slasher();

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

