#pragma once
#include <tchar.h>
#include <vector>

enum class LayerType
{
	Base,
	Flont
};
struct StageHeader
{
	char id[4];				// �t�@�C�����ʎq(FMF_)
	unsigned int size;		// �w�b�_���������f�[�^�T�C�Y
	unsigned int mapW;		// �}�b�v����
	unsigned int mapH;		// �}�b�v�c��
	unsigned char chipW;	// �p�[�c����
	unsigned char chipH;	// �p�[�c�c��
	unsigned char layerCnt;	// ���C���[��
	unsigned char bitCnt;	// ���C���[�f�[�^�̃r�b�g�J�E���g
};

/// <summary>
/// �X�e�[�W�f�[�^�Ǘ�
/// </summary>
class Stage
{
private:
	using LayerData_t = std::vector<unsigned char>;
	std::vector<LayerData_t>stageData_;
	StageHeader header_;
public:
	Stage();
	void Load(const TCHAR* path);
	void Update();
	void Draw(const size_t layerNo);
};




