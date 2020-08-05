#pragma once
#include <tchar.h>
#include <vector>
#include <memory>
#include <array>
#include "../Geometry.h"

#define LayerTypeCast(layerType) static_cast<int>(layerType);

enum class LayerType
{
	Back,		// �w�i(���)
	Base,		// �w�i(�O)
	Flont,		// ����
	Collision,	// ���R���W����
	Enemy		// �G�z�u
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

class Camera;
/// <summary>
/// �X�e�[�W�f�[�^�Ǘ�
/// </summary>
class Stage
{
private:
	using LayerData_t = std::vector<unsigned char>;
	std::vector<LayerData_t>stageData_;
	StageHeader header_;
	std::shared_ptr<Camera>camera_;
	
	std::vector<Segment>terrainSegment_;

	void CreateSegment(Position2f& lastPos, const Position2f& pos);
public:
	Stage(std::shared_ptr<Camera>c);
	/// <summary>
	/// �}�b�v�f�[�^�̓ǂݍ��݃f�[�^�̏c���ϊ�
	/// </summary>
	/// <param name="path">�}�b�v�f�[�^�̃p�X</param>
	void Load(const TCHAR* path);

	/// <summary>
	/// �X�e�[�W�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �X�e�[�W�`��
	/// </summary>
	/// <param name="layerNo">���C���[�ԍ�</param>
	void Draw(const size_t layerNo);

	/// <summary>
	/// ���̃f�o�b�O�`��
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// ���W���獡���鏰�̍�����Ԃ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <returns>���̍���</returns>
	float GetGroundY(const Position2f& pos)const;
	
	/// <summary>
	/// �ǂւ̂߂荞�ݗʂ�Ԃ�
	/// </summary>
	/// <param name="pos">���S���W</param>
	/// <param name="r">���a</param>
	/// <returns>�߂荞�ݗ�</returns>
	Vector2f ComputeOverlapWall(const Position2f& pos, float r)const;

	std::array<Segment, 3>GetThreeSegment(const Position2f& pos)const;

	/// <summary>
	/// �{�X�킩�ǂ���(�X�N���[���֎~)
	/// </summary>
	/// /<returns>true:�{�X��</returns>
	bool IsBossMode()const;
};




