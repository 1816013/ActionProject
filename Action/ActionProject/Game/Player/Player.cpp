#include "Player.h"
#include <DxLib.h>
#include <sstream>
#include <iomanip>
#include "../../Geometry.h"
#include "../../Input.h"
#include "../../Scene/GamePlayingScene.h"
#include "BombEquip.h"
#include "ShurikenEquip.h"
#include "ChainEquip.h"
#include "../../Camera.h"

using namespace std;

namespace
{
	int _runH[6] = {};
	int runCount = 0;
	
}
Player::Player(GamePlayingScene* gs) : 
	Character(gs->GetCamera()), 
	jampUpdater_(&Player::FallUpdate)
{
	direction_ = Direction::RIGHT;
	for (int i = 0; i < _countof(_runH); i++)
	{
		wstringstream wss;
		wss << L"Resource/Image/Player/adventurer-run-";
		wss << setw(2) << setfill(L'0') << i;
		wss << ".png";
		_runH[i] = LoadGraph(wss.str().c_str());
	}
	class PlayerInputListner : public InputListner
	{
	public:
		Player& player_;
		PlayerInputListner(Player& p) : player_(p) {};
		~PlayerInputListner()
		{
			OutputDebugStringA("\n listner is delete\n");
		}
		void Notify(const Input& input)override
		{
			if (input.IsPressed("up"))
			{
			//	player_.Move({ 0, -5 });
			}
			if (input.IsPressed("down"))
			{
			//	player_.Move({ 0, 5 });
			}
			
			if (input.IsPressed("right"))
			{
				player_.direction_ = Direction::RIGHT;
				player_.Move({ 5, 0 });
			}
			if (input.IsPressed("left"))
			{
				player_.direction_ = Direction::LEFT;
				player_.Move({ -5, 0 });
			}
			if (input.IsTriggered("shot"))
			{
				player_.Attack(input);
			}
			if (input.IsTriggered("change"))
			{
				player_.NextEquip();
			}
			player_.ExtendAttack(input);
			if (input.IsTriggered("jump"))
			{
				player_.Jump();
			}
		}
	};
	collisionManager_ =  gs->GetCollisionManager();
	gs->AddListner(make_shared<PlayerInputListner>(*this));
	equipments_.emplace_back(make_shared<BombEquip>(gs->GetProjectileManager(), collisionManager_, camera_));
	equipments_.emplace_back(make_shared<ShurikenEquip>(gs->GetProjectileManager(), collisionManager_, camera_));
	equipments_.emplace_back(make_shared<ChainEquip>(gs->GetPlayer(), collisionManager_, camera_));
}


Player::~Player()
{
	for (auto& run : _runH)
	{
		DeleteGraph(run);
	}
}

void Player::Attack(const Input& input)
{
	equipments_[currentEquipmentNo_]->Attack(*this, input);
}

void Player::ExtendAttack(const Input& input)
{
	equipments_[currentEquipmentNo_]->ExtendAttack(*this, input);
}

void Player::SetPosition(const Position2f& pos )
{
	pos_ = pos;
}

void Player::Move(const Vector2f& v)
{
	pos_ += v;
}

void Player::Jump()
{
	gravity_ = 1.0f;
	velY_ = -25.0f;
	jampUpdater_ = &Player::RiseUpdate;
}

void Player::RiseUpdate()
{
	velY_ += gravity_;
	pos_.y += velY_;
	if (velY_ >= 0.0f)
	{
		jampUpdater_ = &Player::FallUpdate;
	}
}

void Player::FallUpdate()
{
	velY_ += gravity_;
	pos_.y += velY_;
	if (500 < pos_.y)
	{
		velY_ = 0.0f;
		pos_.y = 500;
	}
}

void Player::NextEquip()
{
	currentEquipmentNo_ = (currentEquipmentNo_ + 1) % equipments_.size();
}

void Player::Update()
{
	++runCount;
	for (auto e : equipments_)
	{
		e->Update();
	}
	(this->*jampUpdater_)();
}

void Player::Draw()
{
	auto& offset = camera_->ViewOffset();
	for (auto e : equipments_)
	{
		e->Draw();
	}
	if (direction_ == Direction::RIGHT)
	{
		DrawRotaGraph(pos_.x + offset.x, pos_.y, 3.0f, 0.0f, _runH[runCount / 5 % _countof(_runH)], true);
	}
	else
	{
		DrawRotaGraph(pos_.x + offset.x, pos_.y, 3.0f, 0.0f, _runH[runCount / 5 % _countof(_runH)], true, true);
	}
}

size_t Player::CurrentEquipmentNo() const
{
	return currentEquipmentNo_;
}

Direction Player::Direction() const
{
	return direction_;
}

void Player::OnHit(CollisionInfo& c)
{
}
