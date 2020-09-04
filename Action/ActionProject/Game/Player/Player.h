#pragma once
#include "../Character.h"
#include <memory>
#include <vector>
#include <array>

// �v���C���[�N���X
class GamePlayingScene;
class Equipment;
class CollisionManager;
class Stage;
class FileManager;
class ShadowClone;
class Player : public Character
{
private:
	int runH_[6] = {};
	int jumpH_[4] = {};
	int fallH_[2] = {};
	int shadowMaskH = -1;
	std::vector<std::shared_ptr<Equipment>>equipments_;
	size_t currentEquipmentNo_ = 0;
	Direction direction_;
	GamePlayingScene* gameScene_;
	std::shared_ptr<CollisionManager>collisionManager_;
	std::array<Position2f, 41>moveHistory_;
	size_t currentMoveIndex_ = 0;
	int knockbackfFrame = 0;
	std::vector<std::shared_ptr<ShadowClone>> shadowClones_;

	using Updater_t = void(Player::*)();
	Updater_t updater_;

	using Drawer_t = void(Player::*)(Vector2f, bool);

	Drawer_t drawer_;

	void NomalUpdate();

	void RiseUpdate();

	void FallUpdate();

	void DamageUpdate();

	void RunDraw(Vector2f offset, bool isRight);

	void RizeDraw(Vector2f offset, bool isRight);

	void FallDraw(Vector2f offset, bool isRight);

	void DamageDraw(Vector2f offset, bool isRight);

	void LoadGraphPlayer(const char* key, int* handle, int size, FileManager& fmanager);

	void SetCurrentPosition();
	const Position2f& GetBackTimePosition(size_t t)const;
public:
	Player(GamePlayingScene* g);
	Player() = default;
	~Player();

	/// <summary>
	/// �����Ă��镐��ōU������
	/// </summary>
	/// <param name="input">���͎Q��</param>
	void Attack(const Input& input);

	/// <summary>
	/// �ǉ��U��(���͍����̂�)
	/// </summary>
	/// <param name="input">���͎Q��</param>
	void ExtensionAttack(const Input& input);

	/// <summary>
	/// �v���C���[�̍��W��ݒ肷��
	/// </summary>
	/// <param name="pos">�V���ȍ��W</param>
	void SetPosition(const Position2f& pos);

	/// <summary>
	/// �v���C���[���ړ�������
	/// </summary>
	/// <param name="v">�ړ��x�N�g��</param>
	void Move(const Vector2f& v);

	void Jump();

	/// <summary>
	/// ����ύX
	/// </summary>
	void NextEquip();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;

	
	size_t CurrentEquipmentNo()const;
	Direction Direction()const;

	void OnHit(CollisionInfo& mine, CollisionInfo& another)override;

	float gravity_ = 0.0f;
	float velY_ = 0.0f;
};

