#pragma once
#include <string>
#include <vector>


class FileManager;

/// <summary>
/// �t�@�C�����N���X
/// </summary>
///// <note>
///// �摜�ƃT�E���h�t�@�C���Ɋւ��Ă͎��̂��Ȃ�
///// �f�[�^�t�@�C���͎��̂������Ă���
///// <note/>
class File
{
	friend FileManager;
public:
	enum class Type
	{
		image,	// �摜
		mask,	// �}�X�N�摜
		sound,	// ���ʉ�
		data	// ����ȊO�̃f�[�^
	};
private:
	std::vector<uint8_t>::iterator cursor_;
	std::string tag_;// �^�O
	Type type_;		// �t�@�C�����
	int handle_;	// �t�@�C���n���h��
	std::vector<uint8_t>data_;	// �f�[�^�^�̏ꍇ
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

