#include "Stage.h"
#include <DxLib.h>
#include "Geometry.h"
#include <cassert>
#include "Camera.h"
#include "Debugger.h"
using namespace std;


namespace
{
	int stageAtlasH = -1;
	constexpr float scale_ = 2.0f;
	constexpr int groundLine = 600;
	constexpr float narakuY = 1000.0f;
}

void Stage::CreateSegment(Position2f& startPos, const Position2f& endPos)
{
	if (startPos.IsNil())
	{
		terrainSegment_.push_back(Segment::NIL);
	}
	else
	{
		terrainSegment_.emplace_back(startPos, endPos - startPos);
	}
	
	startPos = endPos;
}

Stage::Stage(std::shared_ptr<Camera>c) : camera_(c)
{
	header_ = {};
	stageAtlasH = LoadGraph(L"Resource/Image/BackGround/level/Atlas.png");
}

void Stage::Load(const TCHAR* path)
{
	auto h = DxLib::FileRead_open(path);
	assert( h > 0);
	FileRead_read(&header_, sizeof(header_), h);	// ヘッダ読み込み
	
	auto layerSize = header_.mapH * header_.mapW;
	stageData_.resize(header_.layerCnt);
	std::vector<LayerData_t>rawStageData(header_.layerCnt);
	for (size_t i = 0; i < header_.layerCnt; ++i)
	{
		stageData_[i].resize(layerSize);
		rawStageData[i].resize(layerSize);
		FileRead_read(rawStageData[i].data(), layerSize, h);
	}
	for (size_t i = 0; i < header_.layerCnt; ++i)
	{
		for (unsigned int y = 0; y < header_.mapH; ++y)
		{
			for (unsigned int x = 0; x < header_.mapW; ++x)
			{
				stageData_[i][y + x * static_cast<size_t>(header_.mapH)] = rawStageData[i][x + y * static_cast<size_t>(header_.mapW)];
			}
		}
	}
	FileRead_close(h);
	camera_->SetStageSize(Size(header_.mapW * header_.chipW * scale_, header_.mapH * header_.chipH * scale_));

	//最後のレイヤーを「線」のデータに変換 
	constexpr uint8_t tr_point = 1;
	constexpr uint8_t tr_end = 2;
	constexpr uint8_t tr_point_end = 3;
	constexpr uint8_t tr_change_point = 4;
	const auto lastLayerNo = header_.layerCnt - 1;
	Position2f lastPos = Position2f::NIL; // 無効な数値
	Position2f pendingPos = Position2f::NIL; // 無効な数値
	terrainSegment_.clear();
	auto yOffset = groundLine - header_.mapH * header_.chipH * scale_;
	for (size_t x = 0; x < header_.mapW; ++x) {
		for (size_t y = 0; y < header_.mapH; ++y) {
			auto data = stageData_[lastLayerNo][y + x * header_.mapH];
			if (data == 0)continue;
			auto pos = Position2f(x * header_.chipW, y * header_.chipH) * scale_ + Vector2f(0, yOffset);
			switch (data) {
			case tr_point://左上の点
				if (pendingPos.IsNil())
				{
					CreateSegment(lastPos, pos);
				}
				else
				{
					CreateSegment(lastPos, pos);
					CreateSegment(pos, pendingPos);
					lastPos = pendingPos;
					pendingPos = Position2f::NIL;
				}
				break;
			case tr_end://右上の終点 
				pos += Vector2f(header_.chipW , 0) * scale_;
				CreateSegment(lastPos, pos);
				lastPos = Position2f::NIL;
				break;
			case tr_point_end://左上右下の終点 
				CreateSegment(lastPos, pos);
				pos += Vector2f(header_.chipW, header_.chipH) * scale_;
				CreateSegment(lastPos, pos);
				lastPos = Position2f::NIL;
				break;
			case tr_change_point://
				pendingPos = pos;
				break;
			}
		}
	}
}

void Stage::Update()
{
}

void Stage::Draw(const size_t layerNo)
{
	const int yoffset = groundLine - (header_.chipH * scale_ * header_.mapH);
	auto& offset = camera_->ViewOffset();
	auto rc = camera_->GetViewRange();

	for (unsigned int x = 0; x < header_.mapW; ++x)
	{
		int xpos = x * header_.chipW * scale_;
		int xmargin = header_.chipW * scale_;
		if (xpos < rc.Left() + xmargin || rc.Right() - xmargin < xpos) {
			continue;
		}
		for (unsigned int y = 0; y < header_.mapH; ++y)
		{		
			auto& data = stageData_[layerNo][y + x * static_cast<size_t>(header_.mapH)];
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

void Stage::DebugDraw()
{
#ifdef _DEBUG
	if (!Debugger::Instance().IsDebugMode())return;

	for (auto seg : terrainSegment_)
	{
		auto sPos = seg.start;
		auto ePos = seg.start + seg.vec;
		auto offset = camera_->ViewOffset();
		DrawLine(sPos.x + offset.x, sPos.y, ePos.x + offset.x, ePos.y, 0xffffff, 3);
	}
#endif // _DEBUG

}

float Stage::GetGroundY(const Position2f& pos) const
{
	auto it = find_if(terrainSegment_.begin(), terrainSegment_.end(),
		[pos](const Segment& seg)
		{	
			if (seg.vec.x == 0.0f)return false;
			auto sPos = seg.start;
			auto ePos = sPos + seg.vec;
			return sPos.x <= pos.x && pos.x <= ePos.x;
		});
	if (it == terrainSegment_.end())
	{
		return narakuY;
	}
	float yVariation = it->vec.y / it->vec.x;
	return it->start.y + yVariation * (pos.x - it->start.x);
}

Vector2f Stage::GetOverlapWall(const Position2f& pos, float r) const
{
	auto it = find_if(terrainSegment_.begin(), terrainSegment_.end(),
		[pos, r](const Segment& seg)
		{
			if (seg.vec.IsNil())return false;
			if (seg.vec.x > 0.0f)return false;
			auto v = pos - seg.start;
			// 垂線の長さ
			auto nlen = fabs(Closs(seg.vec.Nomarized(), v));
			if (r < nlen)return false;
			// 射影の長さ
			auto slen = Dot(v, seg.vec.Nomarized());
			if (slen > seg.vec.Magnitude() || slen < 0.0f)return false;
			return true;
		});
	if (it == terrainSegment_.end())
	{
		return Vector2f::ZERO;
	}
	auto v = pos - it->start;
	auto v2 = it->vec * Dot(v, it->vec) / it->vec.SQMagnitude();
	auto n = (v - v2);
	auto mag = n.Magnitude();
	if (mag == 0.0f)return Vector2f::ZERO;
	
	return n.Nomarized() * (r - mag);
}

std::array<Segment, 3> Stage::GetThreeSegment(const Position2f& pos) const
{
	std::array<Segment, 3>ret = { Segment::NIL, Segment::NIL, Segment::NIL };
	auto it = find_if(terrainSegment_.begin(), terrainSegment_.end(),
		[pos](const Segment& seg)
		{
			const auto& sPos = seg.start;
			auto ePos = sPos + seg.vec;
			return sPos.x <= pos.x && pos.x <= ePos.x;
		});
	if (it == terrainSegment_.end())
	{
		return ret;
	}
	ret[1] = *it;
	if (it != terrainSegment_.begin())
	{
		ret[0] = *prev(it);
	}
	if (next(it) != terrainSegment_.end())
	{
		ret[2] = *next(it);
	}

	return ret;
}
