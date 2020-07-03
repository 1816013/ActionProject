#pragma once
class Input
{
public:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;
	~Input() = default;

	//入力内容の更新
	void Update();
	/// <summary>
	///   現在押しているか 
	/// </summary>
	/// <param name= "cmd">コマンド文字列</param>
	/// <returns>押されていたらtrue
	/// </returns>
	bool IsPressed(const char* cmd)const;

	/// <summary>
	/// 離された瞬間なのか
	/// </summary>
	/// <param name= "cmd">コマンド文字列</param>
	/// <returns>前回押していて話されていたらtrue
	/// </returns>
	
	bool IsReleased(const char* cmd)const;

	// 押された瞬間なのか
	bool IsTriggered(const char* cmd)const;
};

// 入力通知を受け取る(インターフェース)
class InputListner
{
public:
	virtual ~InputListner() = default;
	virtual void Notify(const Input& input) = 0;
};

//bool& CurrentInput(const std::string &cmd);
