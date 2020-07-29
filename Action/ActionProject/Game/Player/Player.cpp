#include "Player.h"
#include <DxLib.h>
#include <sstream>
#include <iomanip>
#include <cassert>
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
	int runH_[6] = {};
	int jumpH_[4] = {};
	int fallH_[2] = {};
	int shadowMaskH = -1;
	int frame_ = 0;
	constexpr int groundLine = 500;
	constexpr float maxGraviry = 1.0f;
	constexpr float jampPower = 25.0f;
	constexpr float jampGravityRate = 10.0f;
	Position2f lastPos_;
}

Player::Player(GamePlayingScene* gs) :
	Character(gs->GetCamera()), 
	updater_(&Player::NomalUpdate),
	drawer_(&Player::RunDraw)
{
	direction_ = Direction::RIGHT;
	LoadGraphPlayer("run", runH_, _countof(runH_));
	LoadGraphPlayer("jump", jumpH_, _countof(jumpH_ ));
	LoadGraphPlayer("fall", fallH_, _countof(fallH_));
	/*for (int i = 0; i < _countof(runH_); i++)
	{
		wstringstream wss;
		wss << L"Resource/Image/Player/adventurer-run-";
		wss << setw(2) << setfill(L'0') << i;
		wss << ".png";
		runH_[i] = LoadGraph(wss.str().c_str());
	}*/

	shadowMaskH = LoadMask(L"Resource/Image/Player/shadow_mask.bmp");
	class PlayerInputListner : public InputListner
	{
	public:
		Player& player_;
		bool decidedGravity = false;
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
				decidedGravity = false;
			}

			if (input.IsReleased("jump"))
			{
				if (player_.updater_ == &Player::RiseUpdate && !decidedGravity)
				{
					player_.gravity_ = max(-player_.velY_ / jampGravityRate, maxGraviry);
					decidedGravity = true;
				}
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
	for (auto& run : runH_)
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
	lastPos_ = pos;
	fill(moveHistory_.begin(), moveHistory_.end(), pos_);
}

void Player::Move(const Vector2f& v)
{
	pos_ += v;
}

void Player::Jump()
{
	if (updater_ != &Player::NomalUpdate)return;
	gravity_ = maxGraviry;
	velY_ = -jampPower;
	updater_ = &Player::RiseUpdate;
	drawer_ = &Player::RizeDraw;
}

void Player::NextEquip()
{
	currentEquipmentNo_ = (currentEquipmentNo_ + 1) % equipments_.size();
}

void Player::Update()
{
	++frame_;
	for (auto e : equipments_)
	{
		e->Update();
	}
	(this->*updater_)();

	
	if (pos_ != lastPos_)
	{
		SetCurrentPosition();
	}
	lastPos_ = pos_;
	//Position2f wpos = pos_;
	/*for (auto& spos : shadowPositions)
	{
		auto v = spos - wpos;
		auto d = v.Magnitude();
		if (d == 0.0f)continue;
		spos = wpos + v.Normalized() * min(d, 100.0f);
		wpos = spos;

	}*/
}

void Player::NomalUpdate()
{


}

void Player::RiseUpdate()
{
	velY_ += gravity_;
	pos_.y += velY_;
	if (velY_ >= 0.0f)
	{
		updater_ = &Player::FallUpdate;
		drawer_ = &Player::FallDraw;
	}
}

void Player::FallUpdate()
{
	velY_ += gravity_;
	pos_.y += velY_;
	if (groundLine < pos_.y)
	{
		velY_ = 0.0f;
		pos_.y = groundLine;
		updater_ = &Player::NomalUpdate;
		drawer_ = &Player::RunDraw;
	}
}

void Player::LoadGraphPlayer(const char* key, int* handle, int size)
{
	for (int i = 0; i < size; i++)
	{
		wstringstream wss;
		wss << L"Resource/Image/Player/adventurer-" << key << "-";
		wss << setw(2) << setfill(L'0') << i;
		wss << ".png";
		handle[i] = LoadGraph(wss.str().c_str());
	}
}

void Player::Draw()
{
	auto offset = camera_->ViewOffset();
	for (auto e : equipments_)
	{
		e->Draw();
	}
	bool isRight = false;
	if (direction_ == Direction::RIGHT)
	{
		isRight = true;
	}
	auto rc = camera_->GetViewRange();
	CreateMaskScreen();
	//DrawFillMask(rc.Left(), rc.Top(), rc.Right(),rc.Bottom(), shadowMaskH);

	auto& fpos = GetBackTimePosition(20);	
	DrawFillMask(fpos.x + offset.x - 100, fpos.y -50, fpos.x + offset.x + 100, fpos.y + 50, shadowMaskH);
	DrawRotaGraph(fpos.x + offset.x, fpos.y, 3.0f, 0.0f, runH_[frame_ / 5 % _countof(runH_)], true, !isRight);

	auto& spos = GetBackTimePosition(40);
	DrawFillMask(spos.x + offset.x - 100, spos.y - 50, spos.x + offset.x + 100, spos.y + 50, shadowMaskH);
	DrawRotaGraph(spos.x + offset.x, spos.y, 3.0f, 0.0f, runH_[frame_ / 5 % _countof(runH_)], true, !isRight);
	
	DeleteMaskScreen();
	(this->*drawer_)(offset, isRight);
}

void Player::RunDraw(Vector2f offset, bool isRight)
{	
	DrawRotaGraph(pos_.x + offset.x, pos_.y, 3.0f, 0.0f, runH_[frame_ / 5 % _countof(runH_)], true, !isRight);
}

void Player::RizeDraw(Vector2f offset, bool isRight)
{
	DrawRotaGraph(pos_.x + offset.x, pos_.y, 3.0f, 0.0f, jumpH_[min(frame_ / 10, _countof(jumpH_) - 1)], true, !isRight);
}

void Player::FallDraw(Vector2f offset, bool isRight)
{
	DrawRotaGraph(pos_.x + offset.x, pos_.y, 3.0f, 0.0f, fallH_[min(frame_ / 10, _countof(fallH_) - 1)], true, !isRight);
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

void Player::SetCurrentPosition()
{
	moveHistory_[currentMoveIndex_] = pos_;
	currentMoveIndex_ = (currentMoveIndex_ + 1) % moveHistory_.size();
}

const Position2f& Player::GetBackTimePosition(size_t t) const
{
	assert(t < moveHistory_.size());
	auto historySize = moveHistory_.size();
	auto idx = (currentMoveIndex_ -t + historySize) % historySize;
	return moveHistory_[idx];
}
