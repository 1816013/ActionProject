#pragma once
#include "Character.h"
#include <memory>
#include <vector>

// プレイヤークラス
class GamePlayingScene;
class Equipment;
class Player : public Character
{
private:
	std::vector<std::shared_ptr<Equipment>>equipments_;
	size_t currentEquipmentNo_ = 0;
public:
	Player(GamePlayingScene* g);
	Player();
	~Player();
	void Attack(const Input& input);
	void SetPosition(const Position2&);
	void Move(const Vector2& v);
	void Update()override;
	void Draw()override;
	const Position2 Position()const;

};

