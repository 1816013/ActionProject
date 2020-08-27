#include "Boss.h"
#include "../../Scene/GamePlayingScene.h"

Boss::Boss(GamePlayingScene* gs) : Enemy(gs->GetPlayer(), gs->GetCamera(), gs->GetStage()),gameScene_(gs),effectManager_(gs->GetEffectMng())
{
}
