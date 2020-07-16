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

using namespace std;

namespace
{
	int _runH[6] = {};
	int runCount = 0;
	
}
Player::Player( GamePlayingScene* gs)
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
			if (input.IsPressed("left"))
			{
				player_.direction_ = Direction::LEFT;
			//	player_.Move({ -5, 0 });
			}
			if (input.IsPressed("right"))
			{
				player_.direction_ = Direction::RIGHT;
				//player_.Move({ 5, 0 });
			}
			if (input.IsTriggered("shot"))
			{
				player_.Attack(input);
			}
			if (input.IsTriggered("change"))
			{
				player_.NextEquip();
			}
		}
	};
	collisionManager_ =  gs->GetCollisionManager();
	gs->AddListner(make_shared<PlayerInputListner>(*this));
	equipments_.emplace_back(make_shared<BombEquip>(gs->GetProjectileManager(), collisionManager_));
	equipments_.emplace_back(make_shared<ShurikenEquip>(gs->GetProjectileManager(), collisionManager_));
	equipments_.emplace_back(make_shared<ChainEquip>(*this, collisionManager_));
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

void Player::SetPosition(const Position2f& pos )
{
	pos_ = pos;
}

void Player::Move(const Vector2f& v)
{
	pos_ += v;
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
}

void Player::Draw()
{
	for (auto e : equipments_)
	{
		e->Draw();
	}
	if (direction_ == Direction::RIGHT)
	{
		DrawRotaGraph(pos_.x, pos_.y, 3.0f, 0.0f, _runH[runCount / 5 % _countof(_runH)], true);
	}
	else
	{
		DrawRotaGraph(pos_.x, pos_.y, 3.0f, 0.0f, _runH[runCount / 5 % _countof(_runH)], true, true);
	}
}

//const Position2f Player::Position()const
//{
//	return pos_;
//}

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
