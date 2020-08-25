#pragma once
#include <memory>
#include "../Geometry.h"

enum class Direction
{
	RIGHT,
	LEFT
};

class Input;
struct CollisionInfo;
class Camera;
class Character
{
protected:
	Position2f pos_;
	std::shared_ptr<Camera>camera_;
	bool isActive_ = false;
	int life_ = 0;
public:
	Character(std::shared_ptr<Camera> camera);
	virtual ~Character() = default;
	/// <summary>
	/// �L�����N�^�[�̍X�V���s��
	/// </summary>
	/// <memo>�v���C���[�ȊO�ɕK�v�Ȃ��p�����[�^�����K�v�Ȃ��z�͖�������</memo>
	virtual void Update() = 0;
	///<summary>
	/// �L�����N�^�[�̕`����s��
	/// </summary>
	virtual void Draw() = 0;	
	/// <summary>
	/// �L�����N�^�[�̍��W��Ԃ�
	/// </summary>
	/// <returns>�L�����N�^�[�̌��ݍ��W(���͑���)</returns>
	virtual const Position2f GetPosition()const;

	/// <summary>
	/// �����ɓ���������
	/// </summary>
	/// <param name="mine">�Փˏ�񎩕�</param>
	/// <param name="another">�Փˏ�񑊎�</param>
	virtual void OnHit(CollisionInfo& mine, CollisionInfo& another) = 0;
	bool IsActive()const { return isActive_; }
};

