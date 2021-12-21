#include "ofApp.h"
#include "stdComponent.h"

BulletObject BulletComponent::m_stdBullet;
NomalBullet BulletComponent::m_nomalBullet;
SmallBullet BulletComponent::m_smallBullet;
BoundBullet BulletComponent::m_boundBullet;

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

void BulletComponent::initialize(const ofVec3f& _target, const BulletType _bulletType, const CollisionType _colType, const ofVec3f& _vec)
{
	m_target = _target;
	m_bulletType = _bulletType;
	m_vec = _vec;

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
	switch (m_bulletType)
	{
	case BulletType::Nomal:
		m_nomalBullet.initialize(this);
		break;
	case BulletType::Small:
		m_smallBullet.initialize(this);
		break;
	case BulletType::Big:
		m_boundBullet.initialize(this);
		break;
	default:
		m_stdBullet.initialize(this);
		break;
	}
}

void BulletComponent::update()
{
	switch (m_bulletType)
	{
	case BulletType::Nomal:
		m_nomalBullet.Move(this, mp_moveCpnt);
		break;
	case BulletType::Small:
		m_smallBullet.Move(this, mp_moveCpnt);
		break;
	case BulletType::Big:
		m_boundBullet.Move(this, mp_moveCpnt);
		break;
	default:
		m_stdBullet.Move(this, mp_moveCpnt);
		break;
	}

	// ���}���u
	mp_gActor->caluculateWorldTransform();
}

void BulletComponent::input()
{
}

void BulletComponent::onCollision(CollisionComponent * _other)
{
	auto enemyPartsCpnt = _other->gActor()->getComponent<EnemyPartsComponent>();
	if (enemyPartsCpnt)
	{
		// �_���[�W��^����
		enemyPartsCpnt->onDamage(mp_gActor->Name(), m_attack, getBullet(m_bulletType).damage);
		//// �퓬�R���|�[�l���g�̒e���X�g����폜
		mp_battleCpnt->DeleteBullet(mp_gActor);
		// �A�N�^�[�̏���
		mp_gActor->StateErace();
	}
}

BulletParam BulletComponent::getBullet(BulletType _bulletType)
{
	switch (_bulletType)
	{
	case BulletType::Nomal:
		return m_nomalBullet.m_bParam;
	case BulletType::Small:
		return m_smallBullet.m_bParam;
	case BulletType::Big:
		return m_boundBullet.m_bParam;
	default:
		return m_stdBullet.m_bParam;
	}
}
