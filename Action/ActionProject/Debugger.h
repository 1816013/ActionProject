#pragma once
class Debugger
{
private:
    Debugger() = default;
    Debugger(const Debugger&) = delete;
    void operator =(const Debugger&) = delete;

    bool debugDisp_ = false;
public:
    /// <summary> 
    /// �V���O���g�� 
    /// </summary> 
    /// <returns>Debugger�C���X�^���X</returns> 
    static Debugger& Instance();

    /// <summary> 
    /// ���f�o�b�O���[�h���ǂ��� 
    /// </summary> 
    /// <returns>true�F�f�o�b�O���[�h</returns> 
    bool IsDebugMode()const;

    /// <summary> 
    /// �X�V
    /// </summary> 
    void Update();

    /// <summary> 
    /// �p�t�H�[�}���X�J�E���^��\������ 
    /// </summary> 
    void DisplayPerformance();
};

