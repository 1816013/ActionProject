#pragma once
#include "Character.h"
class Projectile : public Character
{
protected:
	Vector2f vel_;	// ���x
public:
	virtual ~Projectile() = default;
	///<summary>
	/// ���ݍ��W�ɑ��x�����Z����
	/// </summary>
	virtual void Update()override;
	///<summary>
	/// Draw�͍Ō�̔h���N���X�Ŏ�������
	/// </summary>
	virtual void Draw() = 0;
};

