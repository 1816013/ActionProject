#include "Player.h"
#include <DxLib.h>
#include <sstream>
#include <iomanip>
#include "../Geometry.h"
#include "../Input.h"
#include "../Scene/GamePlayingScene.h"
#include "BombEquip.h"

using namespace std;

namespace
{
	int _runH[6] = {};
	int runCount = 0;
}
Player::Player( GamePlayingScene* gs)
{
	for (int i = 0; i < _countof(_runH); i++)
	{
		wstringstream wss;
		wss << L"Resourse/Image/Player/adventurer-run-";
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
				player_.Move({ 0, -5 });
			}
			if (input.IsPressed("down"))
			{
				player_.Move({ 0, 5 });
			}
			if (input.IsPressed("left"))
			{
				player_.Move({ -5, 0 });
			}
			if (input.IsPressed("right"))
			{
				player_.Move({ 5, 0 });
			}
			if (input.IsTriggered("shot"))
			{
				player_.Attack(input);
			}
		}
	};
	gs->AddListner(make_shared<PlayerInputListner>(*this));
	equipments_.emplace_back(make_shared<BombEquip>(gs->GetProjectileManager()));
}

Player::Player()
{
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

void Player::SetPosition(const Position2& p )
{
	pos_ = p;
}

void Player::Move(const Vector2& v)
{
	pos_ += v;
}

void Player::Update()
{
	++runCount;
	
}

void Player::Draw()
{
	DrawRotaGraph(pos_.x, pos_.y, 3.0f, 0.0f, _runH[runCount / 5 % _countof(_runH)], true);
}

const Position2 Player::Position()const
{
	return pos_;
}
