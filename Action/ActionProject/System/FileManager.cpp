#include "FileManager.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "File.h"
#include <functional>

using namespace std;
namespace
{
	/// <summary>
	/// 拡張子を返す
	/// </summary>
	/// <param name="filepath">ファイルパス</param>
	/// <returns>拡張子文字列</returns>
	wstring GetExtension(const wstring& filepath)
	{
		auto idx = filepath.rfind(L".");
		assert(idx != wstring::npos);
		++idx;
		return filepath.substr(idx, filepath.length() - idx);
	}
	struct HandleAndType
	{
		int handle;
		File::Type type;
	};
	unordered_map<wstring, std::function<HandleAndType(const wchar_t*)>>loader_;
	
}

FileManager::FileManager()
{
	loader_[L"png"] = loader_[L"jpg"] = [](const wchar_t* path)->HandleAndType{
		return { LoadGraph(path), File::Type::image };
	};
	loader_[L"wav"] = loader_[L"mp3"] = [](const wchar_t* path)->HandleAndType {
		return { LoadGraph(path), File::Type::sound };
	};
}

FileManager& FileManager::Instance()
{
	static FileManager instance;
	return instance;
}

std::shared_ptr<File> FileManager::Load(const wchar_t* filepath, const char* tag)
{
	assert(DxLib_IsInit());
	if (resourceTable_.count(filepath) == 0) {//なかった
		auto ext = GetExtension(filepath);
		auto file = loader_[ext](filepath);
		resourceTable_[filepath].reset(new File(file.handle,file.type, tag));//新規ロード
	}
	return resourceTable_[filepath];
}

void FileManager::DeleteAllResources()
{
	resourceTable_.clear();
}

void FileManager::DeleteResourcesByTag(const char* tag)
{
	assert(tag != nullptr);
	auto it = resourceTable_.begin();
	while (it != resourceTable_.end())
	{
		if (it->second->GetTag() == tag)
		{
			resourceTable_.erase(it);
		}
		else
		{
			++it;
		}
	}
	/*for (auto& res : resourceTable_)
	{

	}*/
	//auto it = std::remove_if(resourceTable_.begin(), resourceTable_.end(),
	//	[tag](const pair<wstring,shared_ptr<File>>& res)
	//	{
	//		return res.second->GetTag() == tag;
	//	}); 
	//resourceTable_.erase(it, resourceTable_.end());
}
