#pragma once
#include <vector>

class Background
{
private:
	std::vector<int>bgH_;
	int frame_ = 0;
public:
	Background();
	~Background();
	/// <summary>
	/// �w�i�̍X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �w�i�̕`��
	/// </summary>
	void Draw();
};

