#pragma once
#include <tchar.h>
#include <vector>
#include <memory>
#include "Geometry.h"

enum class LayerType
{
	Base,
	Flont,
	Collision
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
	void Load(const TCHAR* path);
	void Update();
	void Draw(const size_t layerNo);
	void DebugDraw();

	float GetGroundY(const Position2f& pos)const;
};




