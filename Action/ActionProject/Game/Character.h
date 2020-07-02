#pragma once
#include <memory>
#include "../Geometry.h"

class Input;
class Character
{
protected:
	Position2 pos_;
public:
	Character();
	virtual ~Character() = default;
	///�L�����N�^�[�̍X�V���s��
	///�v���C���[�ȊO�ɕK�v�Ȃ��p�����[�^�����K�v�Ȃ��z�͖�������
	virtual void Update(const Input&) = 0;
	///<summary>�L�����N�^�[�̕`����s��</summary>
	virtual void Draw() = 0;	
};

