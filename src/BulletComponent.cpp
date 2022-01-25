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
	// ���Ŏ��̉����t�@�C�����Đ�
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

	// �������̉����t�@�C�����Đ�
	int generationSoundIndex = getBullet(m_bulletType).generationSoundIndex;
	ofApp::getInstance()->mp_soundManager->play(generationSoundIndex);

	//�摜�̓K�p
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->initialize(getBullet(_bulletType).imageName);
	mp_sprCpnt->AlignPivotCenter();
	// �摜�T�C�Y�擾
	auto imageSize = mp_sprCpnt->ImageSize();

	// �ړ��R���|�[�l���g
	mp_moveCpnt = mp_gActor->addComponent<MoveComponent>();

	// �����蔻��R���|�[�l���g
	auto boxCpnt = mp_gActor->addComponent<BoxComponent>();
	boxCpnt->m_onCollisionFunc = bind(&BulletComponent::onCollision, this, std::placeholders::_1);
	boxCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, _colType);
	mp_collisionCpnt = boxCpnt;

	// �e�^�C�v�ɉ��������������s��
	m_bulletMap[m_bulletType]->initialize(this);
}

void BulletComponent::update()
{
	m_bulletMap[m_bulletType]->Move(this, mp_moveCpnt);

	// ���}���u
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

		// �_���[�W��^����
		if (enemyPartsCpnt->onDamage(mp_gActor->Name(), m_charaAttack, m_bulletAttack)) {
			m_isHit = true;
		}

		//// �G�t�F�N�g�A�N�^�[�쐬
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
			// �_���[�W��^����
			playerPartsCpnt->onDamage(mp_gActor->Name(), m_charaAttack, m_bulletAttack);
			Destroy();

			//// �G�t�F�N�g�A�N�^�[�쐬
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

	// �G�t�F�N�g�A�N�^�[�쐬
	{
		auto actor = mp_battleCpnt->gActor()->addChild<GameActor>();
		actor->Pos() = mp_gActor->Pos();
		actor->addComponent<HitEffectComponent>()->Initialize("ATKeffect.png", 200);
	}

	// �퓬�R���|�[�l���g�̒e���X�g����폜
	mp_battleCpnt->DeleteBullet(mp_gActor);
	// �A�N�^�[�̏���
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
