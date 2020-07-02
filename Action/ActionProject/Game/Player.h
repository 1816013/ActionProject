#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();
	void SetPosition(const Position2&);
	void Update(const Input&)override;
	void Draw()override;

};

