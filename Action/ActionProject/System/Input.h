#pragma once
#include <vector>
#include <utility>
#include <string>
#include <array>
#include <unordered_map>

constexpr int inputRecordSize = 2;	// 入力バッファ格納数

enum class PeripheralType
{
	keyboard,
	gamepad
};

struct PeripheralInfo
{
	PeripheralType type;
	int index;
};

using PeripheralRefarenceTable_t = std::unordered_map<std::string, std::vector<PeripheralInfo>>;
class KeyConfigScene;
class Input
{
friend KeyConfigScene;
private:
	PeripheralRefarenceTable_t peripheralReferenceTable_;
	int currentInputIndex = 0;	// 現在の入力バッファを指すインデックス
	using InputStateTable_t = std::unordered_map<std::string, bool>;
	std::array <InputStateTable_t, inputRecordSize>_inputStateTable;	// 入力格納テーブル
	/// <summary>
	/// 次の入力バッファインデックスを返す
	/// </summary>
	int GetNextIndexBufferIndex();
	/// <summary>
	/// 次の入力情報を返す
	/// </summary>
	/// <param name = "cmd">コマンド文字列</param>
	bool& CurrentInput(const std::string& cmd);
	bool GetCurrentInput(const std::string& cmd)const;

	/// <summary>
	/// 1フレーム前の入力バッファインデックスを返す
	/// </summary>
	size_t GetLastInputBufferIndex()const;

	/// <summary>
	/// 直前の入力情報を返す
	/// </summary>
	bool LastIndex(const std::string& cmd)const;

	/// <summary>
	/// イベントに対応する機器入力を登録する
	/// </summary>
	/// <param name="eventname">入力イベントの名前</param>
	/// <param name="peri">入力情報</param>
	void RegistAcceptPeripheral(const char* eventname, const std::vector<PeripheralInfo>& peri);
	bool CheckPressed(const char* eventname, const char* keystate, int padstate);
	//void SetPeripheral(const char* eventnname)
	
	//std::vector<std::pair<std::string, unsigned int>>keyPair_; // <keyname, keycode>
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
