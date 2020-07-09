#pragma once
class Player;
class Input;
class Equipment
{
public:
	virtual ~Equipment() = default;
	/// <summary>
	/// 今の武器で攻撃する
	/// </summary>
	/// <param name="p"> プレイヤーの参照</param>
	/// <param name="i">入力参照</param>
	virtual void Attack(const Player& p, const Input& i) = 0;
	virtual void Update() {};
	virtual void Draw() {};
};

