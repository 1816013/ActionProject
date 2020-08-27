#pragma once
#include "../Projectile.h"
#include <functional>
class BombShot : public Projectile
{
private:
	float angle_;
	int bombH = -1;
	int frame_ = 0;;

	void NomalUpdate();
	void ExprotionUpdate();
	

	void NomalDraw();
	void ExprotionDraw();


	using Func_t = void (BombShot::*)();
	Func_t updater_;
	Func_t drawer_;

public:
	BombShot(const Position2f& pos, const Vector2f& vel, std::shared_ptr<Camera>c);
	~BombShot();
	
	void Update()override;
	
	void Draw()override;

	void OnHit(CollisionInfo& mine, CollisionInfo& another)override;
};

