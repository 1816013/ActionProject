#pragma once
#include <memory>
#include <string>


constexpr const char* tagPlayerAtack = "pAtk";
constexpr const char* tagEnemyDamage = "eDmg";
constexpr const char* tagPlayerDamage = "pDmg";
constexpr const char* tagEnemyBullet = "eblt";
constexpr const char* tagEnemyAttack = "eAtk";

class Camera;
class Character;
/// <summary>
/// �Փˏ����N���X
/// </summary>
class Collider
{
private:
	std::string tag_;
	std::weak_ptr<Character> owner_;
protected:
	bool isDeletable_ = false;	// �����Ă悢�t���O
	bool isImmortal_ = false;	// �s�Ńt���O
	bool isActive_ = true;	// �A�N�e�B�u�ȃt���O
public:
	Collider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	virtual ~Collider() = default;

	/// <summary>
	/// �Փˏ���ێ����Ă���L����������
	/// </summary>
	/// <returns>true:����</returns>
	bool OwnerIsDead()const;	

	/// <summary>
	/// �Փˏ��������Ă悢��
	/// </summary>
	/// <returns>true:�����Ă悢</returns>
	bool IsDeletable()const;

	/// <summary>
	/// �Փˏ��������Ă���L�����N�^�[���擾����
	/// </summary>
	/// <returns>�Փˏ��������Ă���L�����N�^�[</returns>
	std::shared_ptr<Character>GetOwner();

	/// <summary>
	/// �����蔻�蓯�m������������
	/// </summary>
	/// <param name="col">����̓����蔻��</param>
	/// <returns></returns>
	virtual bool IsHit(std::shared_ptr<Collider> col) = 0;

	/// <summary>
	/// �Փˏ��̃^�O���擾����
	/// </summary>
	/// <returns>�Փˏ��̃^�O</returns>
	const std::string& GetTag()const;

	/// <summary>
	/// �Փˏ�������
	/// </summary>
	void Suside();

	/// <summary>
	/// �Փˏ����ꎞ�I�ɖ���������
	/// </summary>
	void Sleep();

	/// <summary>
	/// �����������Փˏ���L��������
	/// </summary>
	void Awake();

	/// <summary>
	/// �Փˏ�񂪗L�����ǂ���
	/// </summary>
	/// <returns>true:�L��</returns>
	bool IsAcrive()const;

	virtual void Draw(std::shared_ptr<Camera>c) {};
};

/// <summary>
/// �Փˏ��\����
/// </summary>
struct CollisionInfo
{
	std::shared_ptr<Collider>collider;	// �Փˏ��̎Q��
};

