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
unordered_map<EnemyType, EnemyObject> EnemyComponent::m_enemyMap;

EnemyComponent::EnemyComponent(GameActor * _gactor) :
	Component(_gactor, "Enemy"),
	m_EnemyType(EnemyType::Nomal),
	m_isSelect(false)
{
	// 敵マップの初期化
	if (m_enemyMap.empty()) {
		m_enemyMap.reserve(EnemyType::TYPE_NUM);
		m_enemyMap[EnemyType::Nomal] = NomalEnemy();
		m_enemyMap[EnemyType::Slime] = SlimeEnemy();
		m_enemyMap[EnemyType::Totem] = TotemEnemy();
		m_enemyMap[EnemyType::Crab] = CrabEnemy();
		m_enemyMap[EnemyType::Boss] = BossEnemy();
	}
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize(BattleComponent* _battleCpnt, const EnemyType _enemytype)
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
		actor->initialize(parts.Pos, parts.PartsName.substr(parts.PartsName.find('_') + 1));

		// エネミーパーツコンポーネント
		auto enemyPartsCpnt = actor->addComponent<EnemyPartsComponent>();
		enemyPartsCpnt->Initialize(parts, this);
		// パーツを追加
		m_partsCpntList.emplace_back(enemyPartsCpnt);
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
	m_isAlive = false;
	// 戦闘コンポーネントの敵リストから自身を消去
	mp_battleCpnt->DeleteEnemy(mp_gActor);
	// アクターの消去
	// mp_gActor->StateErace();

	mp_battleCpnt->AddMessage(mp_gActor->Name() + u8"は倒れた\n");
}

const Skill EnemyComponent::SelectSkill()
{
	return m_enemyMap[m_EnemyType].getEnemySkill(1);
}

void EnemyComponent::CheckIsAlive()
{
	for (auto& parts : m_partsCpntList) {
		parts->CheckIsAlive();
	}
	m_partsCpntList.erase(
		remove_if(m_partsCpntList.begin(), m_partsCpntList.end(),
			[](const auto& parts) { return !parts->GetIsAlive(); }),
		m_partsCpntList.end()
	);
}

void EnemyComponent::DeleteParts(EnemyPartsComponent * _partsCpnt)
{
	auto res = find_if(m_partsCpntList.begin(), m_partsCpntList.end(),
		[&](const auto& c) {return c == _partsCpnt; });
	if (res != m_partsCpntList.end()) {
		m_partsCpntList.erase(res);
	}
}

const EnemyParam & EnemyComponent::getEnemy() const
{
	auto it = m_enemyMap.find(m_EnemyType);
	if (it == m_enemyMap.end()) {
		return m_stdEnemy.m_eParam;
	}

	return m_enemyMap[static_cast<EnemyType>(m_EnemyType)].m_eParam;
}

EnemyParam EnemyComponent::getEnemy(EnemyType _enemytype)
{
	auto it = m_enemyMap.find(_enemytype);
	if (it == m_enemyMap.end()) {
		return m_stdEnemy.m_eParam;
	}

	return m_enemyMap[static_cast<EnemyType>(_enemytype)].m_eParam;
}

void EnemyComponent::SetColor(const ofColor _color)
{
	for (auto & partsCpnt : m_partsCpntList) {
		partsCpnt->gActor()->getComponent<SpriteComponent>()->Color() = _color;
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
	if (mp_enemyCpnt->getEnemy().isPowerByParts) {
		auto boxCpnt = mp_gActor->getComponent<BoxComponent>();
		if (mp_enemyCpnt->GetPartsCpntList().size() != 1 && m_isCore) {
			boxCpnt->mp_cobj->m_ctype = CollisionType::DEFAULT;
		}
		else {
			boxCpnt->mp_cobj->m_ctype = CollisionType::ENEMY_OBJECT;
		}
	}
}

void EnemyPartsComponent::input()
{
}

void EnemyPartsComponent::onCollision(CollisionComponent * _other)
{
}

void EnemyPartsComponent::CheckIsAlive()
{
	// 体力チェック
	if (m_hp <= 0) {
		m_hp = 0;

		m_isAlive = false;

		// パーツ破壊メッセージ
		mp_enemyCpnt->GetBattleCpnt()->AddMessage(mp_enemyCpnt->gActor()->Name() + u8"の" + mp_gActor->Name() + u8"を破壊した");

		// 重要な部位だったら、本体に消去命令を出す
		if (m_isCore) {
			mp_enemyCpnt->onDestroy();
		}
		else {
			mp_gActor->StateErace();
		}
	}
}

bool EnemyPartsComponent::onDamage(const string& _fromName, const int _damage)
{
	if (mp_enemyCpnt->getEnemy().isPowerByParts) {
		if(mp_enemyCpnt->GetPartsCpntList().size() != 1 && m_isCore){
			return false;
		}
	}

	m_hp -= _damage;

	// コマンド追加
	mp_enemyCpnt->GetBattleCpnt()->AddCommand(make_unique<Command>(_fromName, mp_enemyCpnt->gActor()->Name(), 0, _damage));

	//// 体力チェック
	//if (m_hp <= 0) {
	//	m_hp = 0;

	//	// 敵コンポーネントから自身（パーツ）を削除
	//	mp_enemyCpnt->DeleteParts(this);

	//	// パーツ破壊メッセージ
	//	mp_enemyCpnt->GetBattleCpnt()->AddMessage(mp_enemyCpnt->gActor()->Name() + u8"の" + mp_gActor->Name() + u8"を破壊した");

	//	// 重要な部位だったら、本体に消去命令を出す
	//	if (m_isCore) {
	//		mp_enemyCpnt->onDestroy();
	//	}
	//	else {
	//		mp_gActor->StateErace();
	//	}
	//}

	return true;
}

bool EnemyPartsComponent::onDamage(const string& _fromName, const int _charaAttack, const int _bulletAttack)
{
	// ダメージ
	int damage = (_charaAttack - m_def) * _bulletAttack;
	// ダメージが0以下だったら、1にしておく
	damage = damage > 0 ? damage : 1;
	return onDamage(_fromName, damage);
}
