#pragma once
#include <string>
#include <vector>


class FileManager;

/// <summary>
/// ファイル情報クラス
/// </summary>
///// <note>
///// 画像とサウンドファイルに関しては実体がない
///// データファイルは実体をもっている
///// <note/>
class File
{
	friend FileManager;
public:
	enum class Type
	{
		image,	// 画像
		mask,	// マスク画像
		sound,	// 効果音
		data	// それ以外のデータ
	};
private:
	std::vector<uint8_t>::iterator cursor_;
	std::string tag_;// タグ
	Type type_;		// ファイル種別
	int handle_;	// ファイルハンドル
	std::vector<uint8_t>data_;	// データ型の場合
	File(int h, Type type, const char* tag = "");
	void FCopyRead(void* data, size_t size);
public:

	~File();
	int Handle()const;
	std::vector<uint8_t>Data();
	bool IsLoaded()const;
	const std::string& GetTag()const;

	template<typename T>
	void CopyRead(T* data, size_t num)
	{
		FCopyRead(data, sizeof(T) * num);
	}

	template<typename T>
	void CopyRead(T& data)
	{
		FCopyRead(&data, sizeof(T));
	}
};

