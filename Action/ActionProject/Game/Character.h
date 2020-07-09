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
	/// キャラクターの更新を行う
	/// </summary>
	/// <memo>プレイヤー以外に必要ないパラメータだが必要ない奴は無視する</memo>
	virtual void Update() = 0;
	///<summary>
	/// キャラクターの描画を行う
	/// </summary>
	virtual void Draw() = 0;	
};

