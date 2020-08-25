#include "File.h"
#include <DxLib.h>

File::File(int handle, Type type, const char* tag) :
	handle_(handle),
	type_(type),
	tag_(tag)
{
	if (type == Type::data)
	{
		auto bgnIdx = FileRead_tell(handle_);
		FileRead_seek(handle_, 0, SEEK_END);
		auto endIdx = FileRead_tell(handle_);
		auto fsize = endIdx - bgnIdx;
		FileRead_seek(handle_, 0, SEEK_SET);
		data_.resize(fsize);
		FileRead_read(data_.data(), static_cast<int>(fsize), handle);
		FileRead_close(handle);
		cursor_ = data_.begin();
	}
}

void File::FCopyRead(void* data, size_t size)
{
	uint8_t* d = static_cast<uint8_t*>(data);
	//auto itBgn = data_.begin();
	copy_n(cursor_, size, d);
	advance(cursor_, size);
	//cursor_ += size;
}

File::~File()
{
	switch (type_)
	{
	case File::Type::image:
		DeleteGraph(handle_);
		break;
	case File::Type::mask:
		DeleteMask(handle_);
		break;
	case File::Type::sound:
		DeleteSoundMem(handle_);
		break;
	case File::Type::data:
		data_.clear();
		data_.shrink_to_fit();
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
