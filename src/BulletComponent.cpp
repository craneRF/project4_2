#include "ofApp.h"
#include "stdComponent.h"

BulletObject BulletComponent::m_stdBullet;
NomalBullet BulletComponent::m_nomalBullet;
SmallBullet BulletComponent::m_smallBullet;

BulletComponent::BulletComponent(GameActor * _gactor) :Component(_gactor, "Bullet")
{
}

BulletComponent::~BulletComponent()
{
	// 消滅時の音声ファイルを鳴らす
	int destroySoundIndex = getBullet(m_bulletType).destroySoundIndex;
	ofApp::getInstance()->mp_soundManager->play(destroySoundIndex);
}

void BulletComponent::initialize(const ofVec3f& _target, const BulletType _bulletType)
{
	m_target = _target;
	m_bulletType = _bulletType;

	// 生成時の音声ファイルを鳴らす
	int generationSoundIndex = getBullet(m_bulletType).generationSoundIndex;
	ofApp::getInstance()->mp_soundManager->play(generationSoundIndex);

	//画像の適用
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->initialize(getBullet(_bulletType).imageName);
	mp_sprCpnt->AlignPivotCenter();

	// 移動コンポーネント
	mp_moveCpnt = mp_gActor->addComponent<MoveComponent>();
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
	default:
		m_stdBullet.Move(this, mp_moveCpnt);
		break;
	}

	// 応急処置
	mp_gActor->caluculateWorldTransform();
}

void BulletComponent::input()
{
}

void BulletComponent::onCollision(CollisionComponent * _other)
{
}

BulletParam BulletComponent::getBullet(BulletType _bulletType)
{
	switch (_bulletType)
	{
	case BulletType::Nomal:
		return m_nomalBullet.m_bParam;
	case BulletType::Small:
		return m_smallBullet.m_bParam;
	default:
		return m_stdBullet.m_bParam;
	}
}
