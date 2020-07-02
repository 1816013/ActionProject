#include "Player.h"
#include <DxLib.h>
#include <sstream>
#include <iomanip>
#include "../Geometry.h"

using namespace std;

namespace
{
	int _runH[6] = {};
	int runCount = 0;
}
Player::Player()
{
	for (int i = 0; i < _countof(_runH); i++)
	{
		wstringstream wss;
		wss << L"Resourse/Image/Player/adventurer-run-";
		wss << setw(2) << setfill(L'0') << i;
		wss << ".png";
		_runH[i] = LoadGraph(wss.str().c_str());
	}
}

Player::~Player()
{
	for (auto& run : _runH)
	{
		DeleteGraph(run);
	}
}

void Player::SetPosition(const Position2& p )
{
	pos_ = p;
}

void Player::Update(const Input&)
{
	++runCount;
}

void Player::Draw()
{
	DrawRotaGraph(350, 500, 3.0f, 0.0f, _runH[runCount / 5 % _countof(_runH)], true);
}
