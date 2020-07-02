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
	///キャラクターの更新を行う
	///プレイヤー以外に必要ないパラメータだが必要ない奴は無視する
	virtual void Update(const Input&) = 0;
	///<summary>キャラクターの描画を行う</summary>
	virtual void Draw() = 0;	
};

