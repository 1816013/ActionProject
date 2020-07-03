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
	/// ”wŒi‚ÌXV
	/// </summary>
	void Update();
	/// <summary>
	/// ”wŒi‚Ì•`‰æ
	/// </summary>
	void Draw();
};

