#pragma once
#include <memory>
#include <deque>
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
	//std::shared_ptr<Scene>_scene;
public:		
	~SceneController() = default;
	// シーン遷移　
	void ChangeScene(Scene*);
	// シーンスタックの先頭に積む
	void PushScene(Scene*);
	// シーンスタックから先頭を取り除く
	void PopScene();
	// シーンスタックに積まれているものをすべてクリアしてから遷移する
	// 前のシーンは呼出し語に削除されるため,この関数の呼び出し元が削除対象だった場合には、関数呼び出し後に処理を行ってはならない
	void CleanChangeScene(Scene*);

	// 持っている先頭シーンのUpdateを呼ぶ
	void Update(const Input&);

	// シーンスタックに積まれているすべてのシーンのDrawを呼ぶ
	void Draw();
};

