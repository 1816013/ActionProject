#pragma once
#include <memory>
#include "../Geometry.h"
#include <list>
#include <random>

class Camera;
class Effect
{
protected:
	int frame_ = 0;
	Position2f pos_;
	bool isDeleatable = false;
	std::shared_ptr<Camera>camera_;
	int blowH = -1;
public:
	/// <summary>
	/// �G�t�F�N�g�̃R���X�g���N�^
	/// </summary>
	/// <param name="c">�J�����̎Q��</param>
	Effect(std::shared_ptr<Camera> c);
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �����Ă������ǂ���
	/// </summary>
	/// <returns>true:�����Ă悢</returns>
	bool IsDeletable();
};

class EffectManager
{
private:
	std::list<std::shared_ptr<Effect>>effects_;
	std::mt19937 mt_;
	std::shared_ptr<Camera>camera_;
public:
	/// <summary>
	/// ���̃G�t�F�N�g�𔭐�������
	/// </summary>
	/// <param name="p">�o�����W</param>
	/// <param name="isTurn">�G�t�F�N�g�̌������E������</param>
	/// <param name="c">�J�����̎Q��</param>
	void EmitBlood(const Position2f& p, bool isTurn, std::shared_ptr<Camera>c);
	/// <summary>
	/// ���ꔚ���G�t�F�N�g�𔭐�������
	/// </summary>
	/// <param name="p">�o�����W</param>
	/// <param name="isTurn">�G�t�F�N�g�̌������E������</param>
	/// <param name="c">�J�����Q��</param>
	void EmitBlow3(const Position2f& p, bool isTurn, std::shared_ptr<Camera>c);
	void Update();
	void Draw();
};

class Blood : public Effect
{
private:
	bool isTurn_ = false;
public:
	Blood(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c);
	void Update();
	void Draw();
};

class Blow : public Effect
{
private:
	bool isTurn_ = false;
	float delay_ = 0.0f;
public:
	Blow(const Position2f& p, bool isTurn, std::shared_ptr<Camera> c, float delay = 0.0f);
	void Update();
	void Draw();
};