#pragma once
#include <unordered_map>
#include <string>
#include <tchar.h>
#include <memory>

class File;
/// <summary>
/// シングルトンクラス
/// ファイル管理
/// </summary>
class FileManager
{
private:
	FileManager();
	FileManager(const FileManager&) = delete;
	void operator=(const FileManager&) = delete;

	std::unordered_map<std::wstring, std::shared_ptr<File>>resourceTable_;

public:
	/// <summary>
	/// FileManagerのシングルインスタンスを返す
	/// </summary>
	/// <returns>FileManagerのシングルインスタンス</returns>
	static FileManager& Instance();

	/// <summary>
	/// 画像をロード
	/// </summary>
	/// <param name="filePath">画像へのパス</param>
	/// <returns></returns>
	std::shared_ptr<File> Load(const wchar_t* filePath, const char* tag = "");

	/// <summary>
	/// 
	/// </summary>
	void DeleteAllResources();

	void DeleteResourcesByTag(const char* tag);
};

