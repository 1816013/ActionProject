#include "Stage.h"
#include <DxLib.h>
#include "Geometry.h"
#include <cassert>
#include "Camera.h"
using namespace std;


namespace
{
	int stageAtlasH = -1;
}



Stage::Stage(std::shared_ptr<Camera>c) : camera_(c)
{
	header_ = {};
	stageAtlasH = LoadGraph(L"Resource/Image/BackGround/level/Atlas.png");
	scale_ = 2.0f;
}

void Stage::Load(const TCHAR* path)
{
	auto h = DxLib::FileRead_open(path);
	assert( h > 0);
	FileRead_read(&header_, sizeof(header_), h);	// ÉwÉbÉ_ì«Ç›çûÇ›
	
	auto layerSize = header_.mapH * header_.mapW;
	stageData_.resize(header_.layerCnt);

	for (size_t i = 0; i < header_.layerCnt; ++i)
	{
		stageData_[i].resize(layerSize);
		FileRead_read(stageData_[i].data(), layerSize, h);
	}
	camera_->SetStageSize(Size(header_.mapW * header_.chipW * scale_, header_.mapH * header_.chipH * scale_));
	FileRead_close(h);
}

void Stage::Update()
{
}

void Stage::Draw(const size_t layerNo)
{
	constexpr int groundLine = 600;
	const int yoffset = groundLine - (header_.chipH * scale_ * header_.mapH);
	auto& offset = camera_->ViewOffset();

	for (unsigned int y = 0; y < header_.mapH; ++y)
	{
		for (unsigned int x = 0; x < header_.mapW; ++x)
		{
			auto& data = stageData_[layerNo][x + y * static_cast<size_t> (header_.mapW)];
			DrawRectRotaGraph2(
				x * header_.chipW * scale_ + offset.x,
				yoffset + y * header_.chipH * scale_,
				(data % 16) * header_.chipW,
				(data / 16) * header_.chipH,
				header_.chipW,
				header_.chipH,
				0,0,
				scale_,
				0.0f,
				stageAtlasH,
				true);
		}
	}
}