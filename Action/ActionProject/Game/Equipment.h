#pragma once
class Player;
class Input;
class Equipment
{
	/// <summary>
	/// ���̕���ōU������
	/// </summary>
	/// <param name="p"> �v���C���[�̎Q��</param>
	/// <param name="i">���͎Q��</param>
	virtual void Attack(const Player& p, const Input& i) = 0;
};
