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

using PeripheralReferenceTable_t = std::unordered_map<std::string, std::vector<PeripheralInfo>>;
class KeyConfigScene;
class Input
{
friend KeyConfigScene;
private:
	//PeripheralReferenceTable_t peripheralReferenceTable_;
	int currentInputIndex = 0;	// 現在の入力バッファを指すインデックス
	using InputStateTable_t = std::unordered_map<std::string, bool>;
	std::array <InputStateTable_t, inputRecordSize>_inputStateTable;	// 入力格納テーブル
	mutable bool isRawMode_ = false;	// 生モード
	mutable std::vector<char> rawKeyState_;	// 生キーボード情報
	mutable int rawPadState_;	//生パッドステート(1コンのみ)
	mutable PeripheralReferenceTable_t peripheralReferenceTable_;///外側からいじれる用

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
	bool CheckPressed(const char* eventname, const char* keystate = 0, int padstate = 0);
	
	
	/// <summary>
	/// 生キーボード情報を取得する
	/// ロック中は中身が空
	/// </summary>
	/// <returns>生キーボード情報配列</returns>
	const std::vector<char>& GetRawKeyboardState()const;

	/// <summary>
	/// 生パッド情報を取得
	/// 一回だけ
	/// </summary>
	/// <returns>生パッド情報</returns>
	const int GetRawPadState()const;

	/// <summary>
	/// 生モードをアンロックする
	/// 生キーボード、生パッド情報が保持され参照できるようになる
	/// </summary>
	void UnLockRawMode()const;

	/// <summary>
	/// 生モードをロックする
	/// このモードで生データにアクセスしようとするとアサーションを起こす
	/// </summary>
	void LockRawMode()const;

	void SetPeripheralReferenceTable(const PeripheralReferenceTable_t& prt)const;
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
