#pragma once
#include <tchar.h>
#include <vector>
#include <memory>
#include <array>
#include "../Geometry.h"

#define LayerTypeCast(layerType) static_cast<int>(layerType);

enum class LayerType
{
	Back,		// 背景(後ろ)
	Base,		// 背景(前)
	Flont,		// 正面
	Collision,	// 床コリジョン
	Enemy		// 敵配置
};



struct StageHeader
{
	char id[4];				// ファイル識別子(FMF_)
	unsigned int size;		// ヘッダを除いたデータサイズ
	unsigned int mapW;		// マップ横幅
	unsigned int mapH;		// マップ縦幅
	unsigned char chipW;	// パーツ横幅
	unsigned char chipH;	// パーツ縦幅
	unsigned char layerCnt;	// レイヤー数
	unsigned char bitCnt;	// レイヤーデータのビットカウント
};

class Camera;
/// <summary>
/// ステージデータ管理
/// </summary>
class Stage
{
private:
	using LayerData_t = std::vector<unsigned char>;
	std::vector<LayerData_t>stageData_;
	StageHeader header_;
	std::shared_ptr<Camera>camera_;
	
	std::vector<Segment>terrainSegment_;

	void CreateSegment(Position2f& lastPos, const Position2f& pos);
public:
	Stage(std::shared_ptr<Camera>c);
	/// <summary>
	/// マップデータの読み込みデータの縦横変換
	/// </summary>
	/// <param name="path">マップデータのパス</param>
	void Load(const TCHAR* path);

	/// <summary>
	/// ステージ更新
	/// </summary>
	void Update();

	/// <summary>
	/// ステージ描画
	/// </summary>
	/// <param name="layerNo">レイヤー番号</param>
	void Draw(const size_t layerNo);

	/// <summary>
	/// 床のデバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 座標から今いる床の高さを返す
	/// </summary>
	/// <param name="pos">座標</param>
	/// <returns>床の高さ</returns>
	float GetGroundY(const Position2f& pos)const;
	
	/// <summary>
	/// 壁へのめり込み量を返す
	/// </summary>
	/// <param name="pos">中心座標</param>
	/// <param name="r">半径</param>
	/// <returns>めり込み量</returns>
	Vector2f ComputeOverlapWall(const Position2f& pos, float r)const;

	std::array<Segment, 3>GetThreeSegment(const Position2f& pos)const;

	/// <summary>
	/// ボス戦かどうか(スクロール禁止)
	/// </summary>
	/// /<returns>true:ボス戦</returns>
	bool IsBossMode()const;
};




