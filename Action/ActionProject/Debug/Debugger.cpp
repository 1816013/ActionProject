#include "Debugger.h"
#include <DxLib.h>

namespace
{
	bool pressedF1 = false;
}


void Debugger::Update()
{
	if (CheckHitKey(KEY_INPUT_F1))
	{
		if (!pressedF1)
		{
			isDebug_ = !isDebug_;
		}
		pressedF1 = true;
	}
	else
	{
		pressedF1 = false;
	}

}

void Debugger::DisplayPerformance()
{
#ifdef _DEBUG
	if (IsDebugMode()) {
		DrawFormatString(30, 30, 0xffffff, L"FPS=%f", DxLib::GetFPS());
		DrawFormatString(30, 60, 0xffffff, L"DCCount=%d",
			DxLib::GetDrawCallCount());
	}
#endif
}

bool Debugger::IsDebugMode()
{
	return isDebug_;
}
