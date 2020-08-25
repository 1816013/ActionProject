#pragma once
#include <memory>
#include <list>


class Enemy;
using EnemyList = std::list<std::shared_ptr<Enemy>>;
/// <summary>
/// �G���Ǘ�����
/// </summary>
class EnemyManager
{
private:
	EnemyList enemies_;
public:
	/// <summary>
	/// �G���Ǘ��ɒǉ�����
	/// </summary>
	/// <param name="enemy">�G�̖{��</param>
	void AddEnemy(Enemy* enemy);

	/// <summary>
	/// �Ǘ����Ă���G�S�Ă��擾����
	/// </summary>
	/// <returns></returns>
	EnemyList& Enemies();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};


