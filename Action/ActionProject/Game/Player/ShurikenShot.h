#pragma once
#include "Projectile.h"
class ShurikenShot :
	public Projectile
{
private:
	float angle_;
	int shurikenH = -1;

	void NomalUpdate();
	void DestroyUpdate();

	using UpdateFunction_t = void (ShurikenShot::*)();
	UpdateFunction_t updater_;

public:
	ShurikenShot(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera> c);
	~ShurikenShot();

	void Update()override;

	void Draw()override;
	void OnHit(CollisionInfo& info)override;

};

