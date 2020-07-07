#pragma once
#include "Projectile.h"
#include <functional>
class BombShot : public Projectile
{
private:
	float angle_;

	void NomalUpdate();
	void DestroyUpdate();

	using UpdateFunction_t = void (BombShot::*)();
	UpdateFunction_t updater_;

public:
	BombShot(const Position2& pos, const Vector2f& vel);
	~BombShot();
	
	void Update()override;
	
	void Draw()override;


};

