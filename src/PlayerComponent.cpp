#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :Component(_gactor, "Player")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->initialize("enemy_robot.png");
	mp_sprCpnt->AlignPivotCenter();

	const string lifeSpritePathList[] =
	{
		"HP_.png",
		"HP.png"
	};

	int count = 0;
	for (const auto & path : lifeSpritePathList)
	{
		auto lifeActor = mp_gActor->addChild<GameActor>();
		lifeActor->Scale() *= 0.25f;
		lifeActor->initialize({ 0,0,0 }, "lifeSpriteActor" + to_string(count));

		auto spriteCpnt = lifeActor->addComponent<SpriteComponent>();
		spriteCpnt->initialize(path);
		spriteCpnt->AlignPivotCenter();

		++count;
	}
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float _deltatime)
{
}

void PlayerComponent::input(float _deltatime)
{
}

void PlayerComponent::onCollision(CollisionComponent* _other)
{

}
