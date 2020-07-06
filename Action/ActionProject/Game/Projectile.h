#pragma once
#include "Character.h"
class Projectile : public Character
{
protected:
	Vector2f vel_;	// 速度
public:
	virtual ~Projectile() = default;
	///<summary>
	/// 現在座標に速度を加算する
	/// </summary>
	virtual void Update()override;
	///<summary>
	/// Drawは最後の派生クラスで実装する
	/// </summary>
	virtual void Draw() = 0;
};

