#pragma once
#include "../Projectile.h"
#include <functional>
class BombShot : public Projectile
{
private:
	float angle_;
	int bombH = -1;

	void NomalUpdate();
	void DestroyUpdate();

	using UpdateFunction_t = void (BombShot::*)();
	UpdateFunction_t updater_;

public:
	BombShot(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera>c);
	~BombShot();
	
	void Update()override;
	
	void Draw()override;

	void OnHit(CollisionInfo& c)override;
};

