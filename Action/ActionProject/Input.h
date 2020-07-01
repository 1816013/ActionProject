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

	// 現在押しているか 
	/// <param name= "cmd">コマンド文字列</param>
	/// <returns>押されていたらtrue
	/// </returns>
	bool IsPressed(const char* cmd)const;

	// 離された瞬間なのか
	bool IsReleased(const char* cmd)const;

	// 押された瞬間なのか
	bool IsTriggered(const char* cmd)const;
};

//bool& CurrentInput(const std::string &cmd);
