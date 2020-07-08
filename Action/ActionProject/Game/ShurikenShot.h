#pragma once
#include "Projectile.h"
class ShurikenShot :
	public Projectile
{
private:
	float angle_;

	void NomalUpdate();
	void DestroyUpdate();

	using UpdateFunction_t = void (ShurikenShot::*)();
	UpdateFunction_t updater_;

public:
	ShurikenShot(const Position2& pos, const Vector2f& vel);
	~ShurikenShot();

	void Update()override;

	void Draw()override;

};

