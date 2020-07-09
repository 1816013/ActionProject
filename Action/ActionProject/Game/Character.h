#pragma once
#include <memory>
#include "../Geometry.h"

enum class Direction
{
	RIGHT,
	LEFT
};


class Input;
class Character
{
protected:
	Position2 pos_;
public:
	Character();
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
};

