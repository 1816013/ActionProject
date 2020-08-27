#pragma once
#include "Spawner.h"
#include <memory>
#include <list>

class CollisionManager;
/// <summary>
/// ��ʗ��[����o�������锭����̃N���X
/// </summary>
class SideSpawner : public Spawner
{
private:
	int frame_ = 0;	// �t���[��
	int limitSpawnNum_ = 0;
	int averageSpawnFrame_ = 0;
	bool needBalance_ = false;
	struct Regurator
	{
		std::weak_ptr<Enemy>ownedWeakRef;
		bool isRight;
		Regurator(std::weak_ptr<Enemy> wref, bool isright) :
			ownedWeakRef(wref),
			isRight(isright) {};
	};
	std::list <Regurator>regurators_;
	std::list<std::weak_ptr<Enemy>>ownedEnemiesWeakRefs_;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="prototype">�G�̃v���g�^�C�v</param>
	/// <param name="em">�G�Ǘ��N���X</param>
	/// <param name="cm">�Փˏ��Ǘ��N���X</param>
	/// <param name="c">�J����</param>
	/// <param name="averageSpawnFrame">���ϔ�������</param>
	/// <param name="limitCnt">������</param>
	/// <param name="needBalance">�E�ƍ��̔������𓯂����ɂ��邩</param>
	SideSpawner(const Position2f& pos, Enemy* prototype,  
		std::shared_ptr<EnemyManager> em,
		std::shared_ptr<CollisionManager> cm, 
		std::shared_ptr<Camera>c,
		int averageSpawnFrame = 60,
		int limitCnt = -1,
		bool needBalance = false);
	~SideSpawner() = default;
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update()override;
};

