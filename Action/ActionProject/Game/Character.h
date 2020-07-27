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
	virtual const Position2f GetPosition()const;

	virtual void OnHit(CollisionInfo& c) = 0;
};

