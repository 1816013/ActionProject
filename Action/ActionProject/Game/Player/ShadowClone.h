#pragma once
#include <memory>
#include <vector>
#include "../../Geometry.h"

class Player;
class Camera;
class Equipment;
class GamePlayingScene;
class Input;
/// <summary>
/// プレイヤーの分身
/// </summary>
class ShadowClone
{
	friend Player;
private:
	size_t currentEquipmentNo_ = 0;
	Position2f pos_;
	Player* player_;
	std::shared_ptr<Camera>camera_;
	std::vector<std::shared_ptr<Equipment>>equipments_;
	void ExtensionAttack(const Input& input);
public:
	ShadowClone(GamePlayingScene* gs, Player* player, std::shared_ptr<Camera> camera);
	~ShadowClone() = default;

	const Position2f& GetPosition()const;

	void Attack(const Input& input, size_t equipNo);

	void Update(const Position2f& pos);

	void Draw();
	
};

