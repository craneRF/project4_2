#include "ofApp.h"
#include "CreateActor.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"

GameActor* CreateActor::CreatePlayer(string _name)
{
	auto player = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>(_name);
	player->addComponent<PlayerComponent>();

	return player;
}

GameActor* CreateActor::CreateEnemy(string _name)
{
	auto enemy = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>(_name);
	enemy->addComponent<EnemyComponent>();

	return enemy;
}
