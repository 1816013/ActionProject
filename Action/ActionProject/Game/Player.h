#pragma once
#include "Character.h"
#include <memory>

// プレイヤークラス
class GamePlayingScene;
class Player : public Character
{
public:
	Player(GamePlayingScene* g);
	Player();
	~Player();
	void SetPosition(const Position2&);
	void Move(const Vector2& v);
	void Update()override;
	void Draw()override;

};

