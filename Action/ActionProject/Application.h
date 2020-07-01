#pragma once
#include <memory>

// アプリケーションクラス
// すべてのおおもとになるクラス
class SceneController;
struct Size;


// 表示すべき画面の情報を持つ
class Viewport
{
public:
//	Viewport();
	Size GetSize() const;
};

class Application
{
private:
	Viewport viewport_;
	std::unique_ptr<SceneController>sceneController_;
	// コンストラクタをprivate
	Application();
	// 代入、コピーの禁止
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;
public:	
	// 生成
	static Application& Instance()
	{
		static Application app;
		return app;
	}

	// 初期化
	bool Initialize();
	// 実行
	void Run();
	// 終了処理
	void Terminate();
	~Application();

	const Viewport& GetViewport()const;

};
// コンストラクタとデストラクタはunique_ptrのやつでインラインにできない

