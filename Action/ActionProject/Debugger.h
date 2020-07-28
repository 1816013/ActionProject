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
    /// シングルトン 
    /// </summary> 
    /// <returns>Debuggerインスタンス</returns> 
    static Debugger& Instance();

    /// <summary> 
    /// 今デバッグモードかどうか 
    /// </summary> 
    /// <returns>true：デバッグモード</returns> 
    bool IsDebugMode()const;

    /// <summary> 
    /// 更新
    /// </summary> 
    void Update();

    /// <summary> 
    /// パフォーマンスカウンタを表示する 
    /// </summary> 
    void DisplayPerformance();
};

