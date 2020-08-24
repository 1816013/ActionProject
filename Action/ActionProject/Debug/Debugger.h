#pragma once

/// <summary>
/// デバッグ用クラス(シングルトン)
/// </summary>
class Debugger
{
private:
	bool isDebug_;	// デバッグモード用
public:
	static Debugger& Instance()
	{
		static Debugger app;
		return app;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// fpsと表示オブジェクトの数を画面に表示する
	/// </summary>
	void DisplayPerformance();

	/// <summary>
	/// デバッグモードか
	/// </summary>
	/// <returns>true: デバッグモード</returns>
	bool IsDebugMode();
};

