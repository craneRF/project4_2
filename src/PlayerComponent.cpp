#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :
	Component(_gactor, "Player"),
	m_imageSize({0,0,0})
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

void PlayerComponent::update()
{
}

void PlayerComponent::input()
{
}

void PlayerComponent::onCollision(CollisionComponent* _other)
{

}
