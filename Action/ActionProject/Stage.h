#pragma once
#include <tchar.h>
#include <vector>
#include <memory>

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
	float scale_;
public:
	Stage(std::shared_ptr<Camera>c);
	void Load(const TCHAR* path);
	void Update();
	void Draw(const size_t layerNo);
};




