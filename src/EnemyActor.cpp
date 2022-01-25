#include "stdComponent.h"
#include "ofApp.h"
#include "EnemyActor.h"
#include "EnemyObject.h"
#include "EnemyType.h"

EnemyActor::EnemyActor(string _name)
	:GameActor(_name)
{
}

EnemyActor* EnemyActor::createEnemy(GameActor* _parent, ofVec3f _pos, EnemyType _enemytype, BattleComponent* _battleCpnt)
{
	auto actor = _parent->addChild<EnemyActor>();

	auto enemyCpnt = actor->addComponent<EnemyComponent>();
	enemyCpnt->Initialize(_battleCpnt, _enemytype);

	const auto& enemyParam = enemyCpnt->getEnemy(_enemytype);
	actor->SetParam(_pos, enemyParam.scale);

	if (enemyParam.EnemyName != "") {
		actor->initialize(_pos, enemyParam.EnemyName);
	}
	else {
		actor->initialize(_pos, StrEnemyType(_enemytype));
	}

	return actor;
}
