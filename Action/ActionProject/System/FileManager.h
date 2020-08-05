#pragma once
#include <unordered_map>
#include <string>
#include <tchar.h>
#include <memory>

class File;
/// <summary>
/// �V���O���g���N���X
/// �t�@�C���Ǘ�
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
	/// FileManager�̃V���O���C���X�^���X��Ԃ�
	/// </summary>
	/// <returns>FileManager�̃V���O���C���X�^���X</returns>
	static FileManager& Instance();

	/// <summary>
	/// �摜�����[�h
	/// </summary>
	/// <param name="filePath">�摜�ւ̃p�X</param>
	/// <returns></returns>
	std::shared_ptr<File> Load(const wchar_t* filePath, const char* tag = "");

	/// <summary>
	/// 
	/// </summary>
	void DeleteAllResources();

	void DeleteResourcesByTag(const char* tag);
};

