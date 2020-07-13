#pragma once
#include <memory>
#include "../Geometry.h"
#include <list>


class Effect
{
protected:
	int frame_ = 0;
	Position2f pos_;
	bool isDeleatable;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class EffectManager
{
private:
	std::list<std::shared_ptr<Effect>>effectManager_;
public:
	void Update();
	void Draw();
};