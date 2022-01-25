#include "ofApp.h"
#include "stdComponent.h"
#include "HitEffectComponent.h"

unordered_map<BulletType, unique_ptr<BulletObject>> BulletComponent::m_bulletMap;

BulletComponent::BulletComponent(GameActor * _gactor) :
	Component(_gactor, "Bullet"),
	m_target(0, 0),
	m_bulletType(BulletType::Nomal),
	m_vec(1, 1)
{
	m_vec.normalize();
}

BulletComponent::~BulletComponent()
{
	// 消滅時の音声ファイルを再生
	int destroySoundIndex = getBullet(m_bulletType).destroySoundIndex;
	ofApp::getInstance()->mp_soundManager->play(destroySoundIndex);
}

void BulletComponent::initialize(const ofVec3f& _target, const BulletType _bulletType, const CollisionType _colType, const int _bulletAttack, const int _charaAttack, const ofVec3f& _vec)
{
	m_target = _target;
	m_bulletType = _bulletType;
	m_vec = _vec;
	m_charaAttack = _charaAttack;
	m_bulletAttack = _bulletAttack;

	// 生成時の音声ファイルを再生
	int generationSoundIndex = getBullet(m_bulletType).generationSoundIndex;
	ofApp::getInstance()->mp_soundManager->play(generationSoundIndex);

	//画像の適用
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->initialize(getBullet(_bulletType).imageName);
	mp_sprCpnt->AlignPivotCenter();
	// 画像サイズ取得
	auto imageSize = mp_sprCpnt->ImageSize();

	// 移動コンポーネント
	mp_moveCpnt = mp_gActor->addComponent<MoveComponent>();

	// 当たり判定コンポーネント
	auto boxCpnt = mp_gActor->addComponent<BoxComponent>();
	boxCpnt->m_onCollisionFunc = bind(&BulletComponent::onCollision, this, std::placeholders::_1);
	boxCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, _colType);
	mp_collisionCpnt = boxCpnt;

	// 弾タイプに応じた初期化を行う
	m_bulletMap[m_bulletType]->initialize(this);
}

void BulletComponent::update()
{
	m_bulletMap[m_bulletType]->Move(this, mp_moveCpnt);

	// 応急処置
	mp_gActor->caluculateWorldTransform();
}

void BulletComponent::input()
{
}

void BulletComponent::onCollision(CollisionComponent * _other)
{
	if (m_isHit) {
		return;
	}
	auto enemyPartsCpnt = _other->gActor()->getComponent<EnemyPartsComponent>();
	auto playerPartsCpnt = _other->gActor()->getComponent<PlayerPartsComponent>();

	if (enemyPartsCpnt)
	{
		Destroy();

		// ダメージを与える
		if (enemyPartsCpnt->onDamage(mp_gActor->Name(), m_charaAttack, m_bulletAttack)) {
			m_isHit = true;
		}

		//// エフェクトアクター作成
		//{
		//	auto actor = mp_battleCpnt->gActor()->addChild<GameActor>();
		//	actor->Pos() = _other->gActor()->Pos() + _other->gActor()->mp_parent->Pos();
		//	actor->addComponent<HitEffectComponent>()->Initialize("ATKeffect.png", 200);
		//}

	}
	else if (playerPartsCpnt)
	{
		if (playerPartsCpnt->GetIsCore() || (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire") && m_needKey.empty())) {
			m_isHit = true;
			// ダメージを与える
			playerPartsCpnt->onDamage(mp_gActor->Name(), m_charaAttack, m_bulletAttack);
			Destroy();

			//// エフェクトアクター作成
			//{
			//	auto actor = mp_battleCpnt->gActor()->addChild<GameActor>();
			//	actor->Pos() = mp_gActor->Pos();
			//	actor->addComponent<HitEffectComponent>()->Initialize("ATKeffect.png", 200);
			//}
		}
	}
}

void BulletComponent::Destroy()
{
	if (mp_gActor->GetActorState() == GameActor::ActorState::EErace)
	{
		return;
	}

	// エフェクトアクター作成
	{
		auto actor = mp_battleCpnt->gActor()->addChild<GameActor>();
		actor->Pos() = mp_gActor->Pos();
		actor->addComponent<HitEffectComponent>()->Initialize("ATKeffect.png", 200);
	}

	// 戦闘コンポーネントの弾リストから削除
	mp_battleCpnt->DeleteBullet(mp_gActor);
	// アクターの消去
	mp_gActor->StateErace();
}

BulletParam BulletComponent::getBullet(BulletType _bulletType)
{
	return m_bulletMap[_bulletType]->m_bParam;
}

void BulletComponent::InitBulletMap()
{
	if (m_bulletMap.empty()) {
		m_bulletMap[BulletType::Nomal] = make_unique<NomalBullet>();
		m_bulletMap[BulletType::Small] = make_unique<SmallBullet>();
		m_bulletMap[BulletType::Big] = make_unique<BoundBullet>();
		m_bulletMap[BulletType::KeyGuard] = make_unique<KeyGuardBullet>();
	}
}
