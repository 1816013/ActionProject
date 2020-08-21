#pragma once
#include "Spawner.h"
#include <memory>

class CollisionManager;
class BossSpawner : public Spawner
{
private:
	std::shared_ptr<CollisionManager>collisionManager_;

	using Updater_t = void (BossSpawner::*)();
	Updater_t updater_;

	/// <summary>
	/// �{�X�����������Ƃ������ɌĂ΂��X�V
	/// </summary>
	void SpawnUpdate();
	/// <summary>
	/// �������ꂽ��Ă΂��X�V(�������Ȃ�)
	/// </summary>
	void SleepUpdate();
public:
	/// <summary>
	/// �{�X���o��������X�|�i�[
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="prototype">�G�l�~�[�̃v���g�^�C�v</param>
	/// <param name="enemyManager">�G�l�~�[�Ǘ��N���X</param>
	/// <param name="collisionManager">�ՓˊǗ��N���X</param>
	/// <param name="camera">�J����</param>
	BossSpawner(const Position2f& pos,
		Enemy* prototype,
		std::shared_ptr<EnemyManager>enemyManager,
		std::shared_ptr<CollisionManager>collisionManager,
		std::shared_ptr<Camera> camera);
	~BossSpawner() = default;
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

};

