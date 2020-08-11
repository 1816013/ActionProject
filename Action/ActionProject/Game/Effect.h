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
	/// エフェクトのコンストラクタ
	/// </summary>
	/// <param name="c">カメラの参照</param>
	Effect(std::shared_ptr<Camera> c);
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 消えていいかどうか
	/// </summary>
	/// <returns>true:消えてよい</returns>
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
	/// 血のエフェクトを発生させる
	/// </summary>
	/// <param name="p">出現座標</param>
	/// <param name="isTurn">エフェクトの向きが右か左か</param>
	/// <param name="c">カメラの参照</param>
	void EmitBlood(const Position2f& p, bool isTurn, std::shared_ptr<Camera>c);
	/// <summary>
	/// やられ爆発エフェクトを発生させる
	/// </summary>
	/// <param name="p">出現座標</param>
	/// <param name="isTurn">エフェクトの向きが右か左か</param>
	/// <param name="c">カメラ参照</param>
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