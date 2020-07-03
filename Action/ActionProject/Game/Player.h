#pragma once
#include "Character.h"
#include <memory>

// �v���C���[�N���X
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

