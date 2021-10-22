#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :
	Component(_gactor, "Player"),
	m_imageSize({0,0,0})
{
	const string lifeSpritePathList[] =
	{
		"HP_.png",
		"HP.png"
	};

	int count = 0;
	for (const auto & path : lifeSpritePathList)
	{
		auto lifeActor = mp_gActor->addChild<GameActor>();
		lifeActor->initialize({ 0,0,0 }, "lifeSpriteActor" + to_string(count));

		auto spriteCpnt = lifeActor->addComponent<SpriteComponent>();
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
