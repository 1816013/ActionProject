#pragma once
#include <vector>
#include <memory>

class Camera;
class Background
{
private:
	std::vector<int> bgH_;
	int frame_ = 0;
	std::shared_ptr<Camera> camera_;
public:
	Background(std::shared_ptr<Camera> c);
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

