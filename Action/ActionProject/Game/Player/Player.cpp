#include "Player.h"
#include <DxLib.h>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "../../Geometry.h"
#include "../../System/Input.h"
#include "../../Scene/GamePlayingScene.h"
#include "BombEquip.h"
#include "ShurikenEquip.h"
#include "ChainEquip.h"
#include "../Camera.h"
#include "../Stage.h"
#include "../../System/FileManager.h"
#include "../../System/File.h"

using namespace std;

namespace
{
	
	int shadowMaskH = -1;
	int frame_ = 0;
	//constexpr int groundLine = 480;
	constexpr float maxGraviry = 1.0f;
	constexpr float jampPower = 25.0f;
	constexpr float jampGravityRate = 10.0f;
	constexpr float epsilon = 0.01f;
	Position2f lastPos_;
}

Player::Player(GamePlayingScene* gs) :
	Character(gs->GetCamera()), 
	updater_(&Player::NomalUpdate),
	drawer_(&Player::RunDraw)
{
	gs_ = gs;
	gravity_ = maxGraviry;
	direction_ = Direction::RIGHT;
	auto& fileMng = FileManager::Instance();
	LoadGraphPlayer("run", runH_, _countof(runH_), fileMng);
	LoadGraphPlayer("jump", jumpH_, _countof(jumpH_ ), fileMng);
	LoadGraphPlayer("fall", fallH_, _countof(fallH_), fileMng);
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
				player_.ExtendAttack(input);
			}
			if (input.IsPressed("down"))
			{
			//	player_.Move({ 0, 5 });
				player_.ExtendAttack(input);
			}
			
			if (input.IsPressed("right"))
			{
				player_.direction_ = Direction::RIGHT;
				player_.Move({ 5, 0 });
				player_.ExtendAttack(input);
			}
			if (input.IsPressed("left"))
			{
				player_.direction_ = Direction::LEFT;
				player_.Move({ -5, 0 });
				player_.ExtendAttack(input);
			}
			if (input.IsTriggered("shot"))
			{
				player_.Attack(input);
			}
			if (input.IsTriggered("change"))
			{
				player_.NextEquip();
			}
			
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
	equipments_[currentEquipmentNo_]->ExtensionAttack(*this, input);
}

void Player::SetPosition(const Position2f& pos )
{
	pos_ = pos;
	lastPos_ = pos;
	fill(moveHistory_.begin(), moveHistory_.end(), pos_);
}

void Player::Move(const Vector2f& v)
{
	auto rc = camera_->GetViewRange();
	auto movePos = pos_ + v;
	if (movePos.x - 30 < rc.Left() || rc.Right() < movePos.x + 30)return;
	pos_ += v;
	auto vec = gs_->GetStage()->ComputeOverlapWall(pos_, 24);
	pos_ += vec;
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
	auto groundLine = gs_->GetStage()->GetGroundY(pos_);
	if (groundLine < pos_.y)
	{
		pos_.y = groundLine;
	}
	if (groundLine > pos_.y)
	{
		updater_ = &Player::FallUpdate;
		drawer_ = &Player::FallDraw;
	}
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
	auto groundLine = gs_->GetStage()->GetGroundY(pos_);
	if (groundLine < pos_.y)
	{
		velY_ = 0.0f;
		pos_.y = groundLine;
		updater_ = &Player::NomalUpdate;
		drawer_ = &Player::RunDraw;
	}
}

void Player::LoadGraphPlayer(const char* key, int* handle, int size, FileManager& fmanager)
{
	for (int i = 0; i < size; i++)
	{
		wstringstream wss;
		wss << L"Resource/Image/Player/adventurer-" << key << "-";
		wss << setw(2) << setfill(L'0') << i;
		wss << ".png";
		handle[i] = fmanager.Load(wss.str().c_str())->Handle();
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
	auto idx = frame_ / 5 % _countof(runH_);
	auto gH = runH_[idx];
	int w = 0, h = 0;
	GetGraphSize(gH, &w, &h);
	auto& fpos = GetBackTimePosition(20);	
	DrawFillMask(fpos.x + offset.x - 100, fpos.y -50, fpos.x + offset.x + 100, fpos.y + 50, shadowMaskH);
	DrawRotaGraph2(fpos.x + offset.x, fpos.y, w / 2, h - 1, 3.0f, 0.0f, runH_[frame_ / 5 % _countof(runH_)], true, !isRight);

	auto& spos = GetBackTimePosition(40);
	DrawFillMask(spos.x + offset.x - 100, spos.y - 50, spos.x + offset.x + 100, spos.y + 50, shadowMaskH);
	DrawRotaGraph2(spos.x + offset.x, spos.y,w / 2, h - 1, 3.0f, 0.0f, runH_[frame_ / 5 % _countof(runH_)], true, !isRight);
	
	DeleteMaskScreen();
	(this->*drawer_)(offset, isRight);
}

void Player::RunDraw(Vector2f offset, bool isRight)
{	
	auto idx = frame_ / 5 % _countof(runH_);
	auto gH = runH_[idx];
	int w = 0, h = 0;
	GetGraphSize(gH, &w, &h);
	DrawRotaGraph2(pos_.x + offset.x, pos_.y,w / 2, h - 1, 3.0f, 0.0f, runH_[idx], true, !isRight);
}

void Player::RizeDraw(Vector2f offset, bool isRight)
{
	auto idx = min(frame_ / 10, _countof(jumpH_) - 1);
	auto gH = jumpH_[idx];
	int w = 0, h = 0;
	GetGraphSize(gH, &w, &h);
	DrawRotaGraph2(pos_.x + offset.x, pos_.y, w / 2, h - 1,  3.0f, 0.0f, jumpH_[idx], true, !isRight);
}

void Player::FallDraw(Vector2f offset, bool isRight)
{
	auto idx = frame_ / 5 % _countof(fallH_);
	auto gH = fallH_[idx];
	int w = 0, h = 0;
	GetGraphSize(gH, &w, &h);
	DrawRotaGraph2(pos_.x + offset.x, pos_.y, w / 2, h - 1, 3.0f, 0.0f, fallH_[idx], true, !isRight);
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
