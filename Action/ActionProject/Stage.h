#pragma once
#include <tchar.h>
#include <vector>

enum class LayerType
{
	Base,
	Flont
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

/// <summary>
/// ステージデータ管理
/// </summary>
class Stage
{
private:
	using LayerData_t = std::vector<unsigned char>;
	std::vector<LayerData_t>stageData_;
	StageHeader header_;
public:
	Stage();
	void Load(const TCHAR* path);
	void Update();
	void Draw(const size_t layerNo);
};




