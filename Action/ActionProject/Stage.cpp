#include "Stage.h"
#include <DxLib.h>

void Stage::Load(const TCHAR* path)
{
	DxLib::FileRead_open(path);
}
