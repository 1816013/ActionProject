#include "Debugger.h"
#include <DxLib.h>

namespace
{
    bool keyPressed = false;
}

Debugger& Debugger::Instance()
{
	static Debugger debugger;
	return debugger;
}

bool Debugger::IsDebugMode() const
{
    return debugDisp_;
}

void Debugger::Update()
{
#ifdef _DEBUG 
    if (CheckHitKey(KEY_INPUT_F1))
    {
        if (!keyPressed)
        {
            debugDisp_ = !debugDisp_;
        }
        keyPressed = true;
    }
    else
    {
        keyPressed = false;
    }
#endif
}

void Debugger::DisplayPerformance()
{
#ifdef _DEBUG 
    if (IsDebugMode()) {
        DrawFormatString(30, 30, 0xffffff, L"FPS=%f", DxLib::GetFPS());
        DrawFormatString(30, 60, 0xffffff, L"DCCount=%d", DxLib::GetDrawCallCount());
    }
#endif
}
