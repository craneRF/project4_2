#include "ofApp.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"
#include "BattleComponent.h"
#include "BulletComponent.h"
#include "EnemyActor.h"
#include "EnemyType.h"

EnemyObject EnemyComponent::m_stdEnemy;
NomalEnemy EnemyComponent::m_nomalEnemy;
SmallEnemy EnemyComponent::m_smallEnemy;

EnemyComponent::EnemyComponent(GameActor * _gactor) :Component(_gactor, "Enemy")
{
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize(BattleComponent* _battleCpnt, const int _enemytype)
{
	mp_battleCpnt = _battleCpnt;
	m_EnemyType = _enemytype;
	auto enemyParam = getEnemy(m_EnemyType);
	// パーツ作成
	for (auto& c : enemyParam.eParts)
	{
		auto parts = c.second;

		auto actor = mp_gActor->addChild<GameActor>();
		actor->SetParam(parts.Pos, parts.Scale, parts.angle);
		actor->initialize(parts.Pos, parts.PartsName);

		// エネミーパーツコンポーネント
		auto enemyPartsCpnt = actor->addComponent<EnemyPartsComponent>();
		enemyPartsCpnt->Initialize(parts, this);
	}

}

void EnemyComponent::update()
{

}

void EnemyComponent::input()
{
}

void EnemyComponent::onDestroy()
{
	// 戦闘コンポーネントの敵リストから自身を消去
	mp_battleCpnt->DeleteEnemy(mp_gActor);
	// アクターの消去
	mp_gActor->StateErace();

	cout << mp_gActor->Name() << "は倒れた\n";
}

void EnemyComponent::AddCommand(const string _fromName, const string _toName, const int _commandType, const int _commandval)
{
	mp_battleCpnt->AddCommand(make_unique<Command>(_fromName, mp_gActor->Name() + u8"の" + _toName, _commandType, _commandval));
}

EnemyParam EnemyComponent::getEnemy(int _enemytype)
{
	switch (_enemytype)
	{
	case NONE:
		return m_stdEnemy.m_eParam;
	case Nomal:
		return m_nomalEnemy.m_eParam;
	case Small:
		return m_smallEnemy.m_eParam;
	}
}

EnemyPartsComponent::EnemyPartsComponent(GameActor * _gactor) :Component(_gactor, "EnemyParts")
{
}

EnemyPartsComponent::~EnemyPartsComponent()
{
}

void EnemyPartsComponent::Initialize(const EnemyParts & _enemyParts, EnemyComponent* _enemyCpnt)
{
	// 部位を持つ敵のコンポーネントを取得
	mp_enemyCpnt = _enemyCpnt;

	// スプライトコンポーネント
	auto sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	sprCpnt->initialize(_enemyParts.ImageName);
	sprCpnt->AlignPivotCenter();
	auto imageSize = sprCpnt->ImageSize();

	// 重要な部位か設定
	m_isCore = _enemyParts.isCore;
	// 体力設定
	m_hp = _enemyParts.HP;
	// 防御力設定
	m_def = _enemyParts.Def;

	// 当たり判定コンポーネント
	auto boxCpnt = mp_gActor->addComponent<BoxComponent>();
	boxCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::ENEMY_OBJECT);
	boxCpnt->m_onCollisionFunc = bind(&EnemyPartsComponent::onCollision, this, std::placeholders::_1);
}

void EnemyPartsComponent::update()
{
}

void EnemyPartsComponent::input()
{
}

void EnemyPartsComponent::onCollision(CollisionComponent * _other)
{
}

void EnemyPartsComponent::onDamage(const string& _fromName, const int _damage)
{
	m_hp -= _damage;

	// コマンド追加
	mp_enemyCpnt->AddCommand(_fromName, mp_gActor->Name(), 0, _damage);

	// 体力チェック
	if (m_hp <= 0) {
		m_hp = 0;

		// 重要な部位だったら、本体に消去命令を出す
		if (m_isCore) {
			mp_enemyCpnt->onDestroy();
		}
		else {
			mp_gActor->StateErace();
		}
	}
}

void EnemyPartsComponent::onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack)
{
	// ダメージ
	int damage = (m_def - _charaAttack) * _bulletAttack;
	// ダメージがマイナスだったら、0にしておく
	damage = damage > 0 ? damage : 1;
	onDamage(_fromName, damage);
}
