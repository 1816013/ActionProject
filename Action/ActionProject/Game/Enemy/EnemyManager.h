#pragma once
#include <memory>
#include <list>


class Enemy;
using EnemyList = std::list<std::shared_ptr<Enemy>>;
/// <summary>
/// “G‚ğŠÇ—‚·‚é
/// </summary>
class EnemyManager
{
private:
	EnemyList enemies_;
public:
	/// <summary>
	/// “G‚ğŠÇ—‚É’Ç‰Á‚·‚é
	/// </summary>
	/// <param name="enemy">“G‚Ì–{‘Ì</param>
	void AddEnemy(Enemy* enemy);

	/// <summary>
	/// ŠÇ—‚µ‚Ä‚¢‚é“G‘S‚Ä‚ğæ“¾‚·‚é
	/// </summary>
	/// <returns></returns>
	EnemyList& Enemies();

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();
};


