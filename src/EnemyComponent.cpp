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
	// �p�[�c�쐬
	for (auto& c : enemyParam.eParts)
	{
		auto parts = c.second;

		auto actor = mp_gActor->addChild<GameActor>();
		actor->SetParam(parts.Pos, parts.Scale, parts.angle);
		actor->initialize(parts.Pos, parts.PartsName);

		// �G�l�~�[�p�[�c�R���|�[�l���g
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
	// �퓬�R���|�[�l���g�̓G���X�g���玩�g������
	mp_battleCpnt->DeleteEnemy(mp_gActor);
	// �A�N�^�[�̏���
	mp_gActor->StateErace();

	cout << mp_gActor->Name() << "�͓|�ꂽ\n";
}

void EnemyComponent::AddCommand(const string _fromName, const string _toName, const int _commandType, const int _commandval)
{
	mp_battleCpnt->AddCommand(make_unique<Command>(_fromName, mp_gActor->Name() + u8"��" + _toName, _commandType, _commandval));
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
	// ���ʂ����G�̃R���|�[�l���g���擾
	mp_enemyCpnt = _enemyCpnt;

	// �X�v���C�g�R���|�[�l���g
	auto sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	sprCpnt->initialize(_enemyParts.ImageName);
	sprCpnt->AlignPivotCenter();
	auto imageSize = sprCpnt->ImageSize();

	// �d�v�ȕ��ʂ��ݒ�
	m_isCore = _enemyParts.isCore;
	// �̗͐ݒ�
	m_hp = _enemyParts.HP;
	// �h��͐ݒ�
	m_def = _enemyParts.Def;

	// �����蔻��R���|�[�l���g
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

	// �R�}���h�ǉ�
	mp_enemyCpnt->AddCommand(_fromName, mp_gActor->Name(), 0, _damage);

	// �̗̓`�F�b�N
	if (m_hp <= 0) {
		m_hp = 0;

		// �d�v�ȕ��ʂ�������A�{�̂ɏ������߂��o��
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
	// �_���[�W
	int damage = (m_def - _charaAttack) * _bulletAttack;
	// �_���[�W���}�C�i�X��������A0�ɂ��Ă���
	damage = damage > 0 ? damage : 1;
	onDamage(_fromName, damage);
}
