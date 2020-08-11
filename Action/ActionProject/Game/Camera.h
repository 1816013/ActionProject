#pragma once
#include <memory>
#include "../Geometry.h"

class Player;
class Camera
{
private:
	std::shared_ptr<Player> player_;
	Position2f pos_;	// カメラの中心座標
	Size stageSize_;	// ステージの大きさ
	bool isLocked = false;
public:
	Camera();
	void SetPlayer(std::shared_ptr<Player> player);
	
	/// <summary>
	/// ステージの限界サイズをセットする
	/// </summary>
	/// <param name="size">ステージ全体のサイズ</param>
	void SetStageSize(const Size& size);
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();

	/// <summary>
	/// カメラの現在座標を返す
	/// </summary>
	/// <returns>カメラの現在座標</returns>
	const Position2f& GetPosition()const;

	/// <summary>
	/// カメラの撮影範囲を返す
	/// </summary>
	/// <returns>カメラの撮影範囲</returns>
	const Rect GetViewRange()const;
	
	/// <summary>
	/// カメラの現在座標を返す
	/// </summary>
	/// <returns>カメラの現在座標</returns>
	const Vector2f ViewOffset()const;

	/// <summary>
	/// スクロールを止めるかどうかを返す
	/// </summary>
	/// <returns>true:停止</returns>
	bool Lock();
};

