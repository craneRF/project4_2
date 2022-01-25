#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"
#include "BattleComponent.h"
#include "Effect.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :
	Component(_gactor, "Player"),
	m_imageSize({ 0,0,0 })
{
	const string lifeSpritePathList[] =
	{
		"HP_.png",
		"HP.png"
	};

	for (const auto & path : lifeSpritePathList)
	{
		auto spriteCpnt = mp_gActor->addComponent<SpriteComponent>();
		spriteCpnt->initialize(path);
		spriteCpnt->AlignPivotCenter();
		auto imageSize = spriteCpnt->ImageSize();
		if (m_imageSize.x < imageSize.x)
		{
			m_imageSize.x = imageSize.x;
		}
		if (m_imageSize.y < imageSize.y)
		{
			m_imageSize.y = imageSize.y;
		}
	}
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Initialize(BattleComponent * _battleCpnt)
{
	mp_battleCpnt = _battleCpnt;

	ofVec3f baseSize = m_imageSize * 0.4f;
	ofVec3f incrementSize = m_imageSize * 0.3f;
	// 本体
	{
		auto actor = mp_gActor->addChild<GameActor>("CORE");

		// プレイヤーパーツコンポーネント
		auto partsCont = actor->addComponent<PlayerPartsComponent>();
		partsCont->Initialize(true, 3, this);

		// 当たり判定コンポーネント
		auto boxCpnt = actor->addComponent<BoxComponent>();
		boxCpnt->initialize(ofVec3f(0, 0), baseSize.x, baseSize.y, CollisionType::PLAYER_OBJECT);
		boxCpnt->m_onCollisionFunc = bind(&PlayerPartsComponent::onCollision, partsCont, std::placeholders::_1);

		actor->drawfuncVec.emplace_back([baseSize] {
			auto offset = baseSize * -0.5f;
			ofSetColor(ofColor::red, 25);
			ofDrawRectangle(offset, baseSize.x, baseSize.y);
			}
		);
	}

	// ガード追加
	for (int i = 1; i <= 2; i++)
	{
		auto actor = mp_gActor->addChild<GameActor>("GUARD" + to_string(i));

		// プレイヤーパーツコンポーネント
		auto partsCont = actor->addComponent<PlayerPartsComponent>();
		partsCont->Initialize(false, i, this);

		// 当たり判定コンポーネント
		auto boxCpnt = actor->addComponent<BoxComponent>();
		auto guardSize = baseSize + i * incrementSize;
		boxCpnt->initialize(ofVec3f(0, 0), guardSize.x, guardSize.y, CollisionType::PLAYER_OBJECT);
		boxCpnt->m_onCollisionFunc = bind(&PlayerPartsComponent::onCollision, partsCont, std::placeholders::_1);

		actor->drawfuncVec.emplace_back([guardSize] {
			auto offset = guardSize * -0.5f;
			ofSetColor(ofColor::red, 25);
			ofDrawRectangle(offset, guardSize.x, guardSize.y);
			}
		);
	}
}

void PlayerComponent::update()
{
}

void PlayerComponent::input()
{
}

void PlayerComponent::onCollision(CollisionComponent* _other)
{

}

void PlayerComponent::AddCommand(const string& _fromName, const int _commandType, const int _commandval)
{
	mp_battleCpnt->AddCommand(make_unique<Command>(_fromName, mp_gActor->Name(), _commandType, _commandval));
}

PlayerPartsComponent::PlayerPartsComponent(GameActor * _gactor) :
	Component(_gactor, "PlayerParts")
{
}

PlayerPartsComponent::~PlayerPartsComponent()
{
}

void PlayerPartsComponent::Initialize(const bool _isCore, const int _damageMultiplier, PlayerComponent * _playerCpnt)
{
	m_isCore = _isCore;
	m_damageMultiplier = _damageMultiplier;
	mp_playerCpnt = _playerCpnt;
}

void PlayerPartsComponent::update()
{
}

void PlayerPartsComponent::input()
{
}

void PlayerPartsComponent::onCollision(CollisionComponent * _other)
{
}

void PlayerPartsComponent::onDamage(const string & _fromName, const int _damage)
{
	// コマンド追加
	mp_playerCpnt->AddCommand(_fromName, 0, _damage);

	Effect::healHP(_damage * -1);
	int hp = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
	if (hp < 0) {
		ofApp::getInstance()->mp_prm->setPlayerParam("HP", 0);
	}

#ifdef _DEBUG
	std::cout << "Playerの" << mp_gActor->Name() << "に当たりました。\n";
#endif // _DEBUG
}

void PlayerPartsComponent::onDamage(const string & _fromName, const int _charaAttack, const int _bulletAttack)
{
	const int def = ofApp::getInstance()->mp_prm->getPlayerParam("DEF");

	// ダメージ
	int damage = (_charaAttack - def) * _bulletAttack * m_damageMultiplier;
	// ダメージが0以下だったら、1にしておく
	damage = damage > 0 ? damage : 1;
	onDamage(_fromName, damage);
}
