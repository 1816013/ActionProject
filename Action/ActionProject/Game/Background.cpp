#include "Background.h"
#include <DxLib.h>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "../Geometry.h"
#include "Camera.h"

using namespace std;
namespace
{
	Rect rect = { {400, 300}, {800, 600} };
}

Background::Background(std::shared_ptr<Camera> c) : camera_(c)
{
	bgH_.resize(11);
	int skipNo[2] = { 4 , 7 };
	int no = 9;
	for (int i = 0; i < bgH_.size(); i++)
	{
		wstringstream wss;
		wss << L"Resource/Image/BackGround/Layer_";
		wss << setw(4) << setfill(L'0') << i << "_";
		if (std::count(begin(skipNo), end(skipNo), i) > 0)
		{
			wss << "Lights";
		}
		else
		{
			wss << no;
			--no;
		}
		wss << ".png";
		bgH_[bgH_.size() - 1 - i] = LoadGraph(wss.str().c_str());
	}
	frame_ = 0;
}

Background::~Background()
{
	for (auto& bg : bgH_)
	{
		DeleteGraph(bg);
	}
}

void Background::Update()
{
	++frame_;
}

void Background::Draw()
{
	
	for (int i = 0; i < bgH_.size(); i++)
	{
		auto offset = camera_->ViewOffset();
		int scroll = frame_ / 2 * (i + 1) % rect.size.w;
		auto cameraScroll = offset.x / 10 * ((i + 1) % rect.size.w);
		DrawExtendGraph((int)cameraScroll % rect.size.w, 0, rect.size.w + (int)cameraScroll % rect.size.w, rect.size.h, bgH_[i], true);
		DrawExtendGraph(rect.size.w + (int)cameraScroll % rect.size.w, 0, rect.size.w * 2 + (int)cameraScroll % rect.size.w, rect.size.h, bgH_[i], true);
	}
}
