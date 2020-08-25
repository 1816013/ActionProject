#pragma once
#include <memory>
#include "../Geometry.h"

enum class Direction
{
	RIGHT,
	LEFT
};

class Input;
struct CollisionInfo;
class Camera;
class Character
{
protected:
	Position2f pos_;
	std::shared_ptr<Camera>camera_;
	bool isActive_ = false;
	int life_ = 0;
public:
	Character(std::shared_ptr<Camera> camera);
	virtual ~Character() = default;
	/// <summary>
	/// キャラクターの更新を行う
	/// </summary>
	/// <memo>プレイヤー以外に必要ないパラメータだが必要ない奴は無視する</memo>
	virtual void Update() = 0;
	///<summary>
	/// キャラクターの描画を行う
	/// </summary>
	virtual void Draw() = 0;	
	/// <summary>
	/// キャラクターの座標を返す
	/// </summary>
	/// <returns>キャラクターの現在座標(今は足元)</returns>
	virtual const Position2f GetPosition()const;

	/// <summary>
	/// 何かに当たったら
	/// </summary>
	/// <param name="mine">衝突情報自分</param>
	/// <param name="another">衝突情報相手</param>
	virtual void OnHit(CollisionInfo& mine, CollisionInfo& another) = 0;
	bool IsActive()const { return isActive_; }
};

