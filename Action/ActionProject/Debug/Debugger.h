#pragma once
class Debugger
{
private:
	bool isDebug_;
public:
	static Debugger& Instance()
	{
		static Debugger app;
		return app;
	}

	void Update();
	void DisplayPerformance();

	bool IsDebugMode();
};

