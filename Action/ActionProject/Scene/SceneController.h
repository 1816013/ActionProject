#pragma once
#include <memory>
#include <deque>
#include <functional>

class Input;
class Application;
class Scene;
class SceneController
{
	friend class Application;
private:
	// シーンスタック(FIFO)※コンテナを使うためdeque
	std::deque<std::shared_ptr<Scene>>scene_;	
	SceneController();
	// シーン切り替えの時Drawの後にシーン切り替えの関数を呼ぶためのもの
	// 普通に呼び出していると前のシーンのDrawが呼び出されたりして
	// 見えちゃいけないものが見える可能性がある
	std::function<void(void)> postDrawExecuter_;
	//std::shared_ptr<Scene>_scene;
public:		
	~SceneController() = default;
	/// <summary>
	/// シーン遷移
	/// </summary>
	/// <param name="scene">次のシーン</param>
	void ChangeScene(Scene* scene);
	// シーンスタックの先頭に積む
	void PushScene(Scene* scene);
	// シーンスタックから先頭を取り除く
	void PopScene();
	// シーンスタックに積まれているものをすべてクリアしてから遷移する
	// 前のシーンは呼出し語に削除されるため,この関数の呼び出し元が削除対象だった場合には、関数呼び出し後に処理を行ってはならない
	void CleanChangeScene(Scene* scene);

	// 持っている先頭シーンのUpdateを呼ぶ
	void Update(const Input& input);

	// シーンスタックに積まれているすべてのシーンのDrawを呼ぶ
	void Draw();

	void ClearScene();
};

