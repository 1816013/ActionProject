#pragma once
#include "Spawner.h"
//class Enemy;
class CollisionManager;
/// <summary>
/// ��ʗ��[����o�������锭����
/// </summary>
class SideSpawner : public Spawner
{
private:
	int frame_ = 0;	// �t���[��
	//std::shared_ptr<CollisionManager>collisionManeger_;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="prototype">�G�̃v���g�^�C�v</param>
	/// <param name="em">�G�Ǘ��N���X</param>
	/// <param name="cm">�Փˏ��Ǘ��N���X</param>
	/// <param name="c">�J����</param>
	SideSpawner(const Position2f& pos, Enemy* prototype,  
		std::shared_ptr<EnemyManager> em,
		std::shared_ptr<CollisionManager> cm, 
		std::shared_ptr<Camera>c);
	~SideSpawner() = default;
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update()override;
};

