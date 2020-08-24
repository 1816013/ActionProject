#include "Boss.h"
#include "../../Scene/GamePlayingScene.h"

Boss::Boss(GamePlayingScene* gs) : Enemy(gs->GetPlayer(), gs->GetCamera()),gameScene_(gs),effectManager_(gs->GetEffectMng())
{
}
