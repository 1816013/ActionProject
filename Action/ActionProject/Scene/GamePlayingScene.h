#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class Player;
class Background;
class TitleScene;
class InputListner;
class ProjectileManager;
class EnemyManager;
class Spawner;
class CollisionManager;
class EffectManager;
class Stage;
class Camera;
class GamePlayingScene : public Scene
{
	friend TitleScene;
private:
	GamePlayingScene(SceneController&);

	void InitializeUpdate(const Input& input);
	void FadeoutUpdate(const Input&);
	void FadeinUpdate(const Input&);
	void GamePlayUpdate(const Input&);

	using UpdateFunction_t = void (GamePlayingScene::*)(const Input&);
	UpdateFunction_t updater_;
	void NomalDraw();
	void FadeDraw();

	using DrawerFunction_t = void (GamePlayingScene::*)();
	DrawerFunction_t drawer_;

	std::shared_ptr<Player> player_;
	std::unique_ptr<Background> bg_;
	std::vector<std::shared_ptr<InputListner>> listners_;
	std::unique_ptr<ProjectileManager> projectileManager_;
	std::shared_ptr<EnemyManager> enemyManager_;
	std::vector<std::shared_ptr<Spawner>> spawners_;
	std::shared_ptr<CollisionManager> collisionManager_;
	std::shared_ptr<EffectManager> effectManager_;
	std::shared_ptr<Stage> stage_;
	std::shared_ptr<Camera> camera_;

	
public:
	~GamePlayingScene();
	/// <summary>
	/// 入力通知を受け取るものを追加する
	/// 現在はプレイヤーの入力通知のみ
	/// </summary>
	/// <param name="listner">入力通知を受け取るもの</param>
	void AddListner(std::shared_ptr<InputListner> listner);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力情報</param>
	void Update(const Input& input)override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ProjectileManager& GetProjectileManager();
	std::shared_ptr<CollisionManager> GetCollisionManager();
	std::shared_ptr<EnemyManager> GetEnemyManager();
	std::shared_ptr<Player>& GetPlayer();
	std::shared_ptr<Camera>& GetCamera();
	std::shared_ptr<Stage>& GetStage();
	void AddSpawner(Spawner* spawer);
};

