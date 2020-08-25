#pragma once
#include <memory>
#include "../../Geometry.h"

class Player;
class Camera;
class ShadowClone
{
	friend Player;
private:
	Position2f pos_;
	Player* player_;
	std::shared_ptr<Camera>camera_;
public:
	ShadowClone(Player* player, std::shared_ptr<Camera> camera);

	void Update(Position2f pos);

	void Draw();
	
};

