#include "File.h"
#include <DxLib.h>

File::File(int h, Type type, const char* tag) :
	handle_(h),
	type_(type),
	tag_(tag)
{
}

File::~File()
{
	switch (type_)
	{
	case File::Type::image:
		DeleteGraph(handle_);
		break;
	case File::Type::sound:
		DeleteSoundMem(handle_);
		break;
	case File::Type::data:
		break;
	default:
		break;
	}
}

int File::Handle() const
{
	return handle_;
}

std::vector<uint8_t> File::Data()
{
	return data_;
}

bool File::IsLoaded() const
{
	return true;
}

const std::string& File::GetTag() const
{
	return tag_;
}
