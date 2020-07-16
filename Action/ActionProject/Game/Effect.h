#pragma once
#include <memory>
#include "../Geometry.h"
#include <list>
#include <random>


class Effect
{
protected:
	int frame_ = 0;
	Position2f pos_;
	bool isDeleatable = false;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool IsDeletable();
};

class EffectManager
{
private:
	std::list<std::shared_ptr<Effect>>effects_;
	std::mt19937 mt_;
public:
	void EmitBlood(const Position2f& p, bool isTurn);
	void EmitBlow3(const Position2f& p, bool isTurn);
	void Update();
	void Draw();
};

class Blood : public Effect
{
private:
	bool isTurn_ = false;
public:
	Blood(const Position2f& p, bool isTurn);
	void Update();
	void Draw();
};

class Blow : public Effect
{
private:
	bool isTurn_ = false;
	float delay_ = 0.0f;
public:
	Blow(const Position2f& p, bool isTurn, float delay = 0.0f);
	void Update();
	void Draw();
};