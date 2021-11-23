#include "GameActor.h"
#include "CollisionObj.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"
#include "CollisionManager.h"

//CollisionObj::CollisionObj(GameActor* _actor) :
CollisionObj::CollisionObj(CollisionComponent* _compo) :
	m_rect(ofRectangle()),
	mp_compo(_compo),
	m_ctype(CollisionType::DEFAULT)
{
}

bool CollisionObj::checkCollide(const CollisionObj& _other) const {
	if (mp_compo->m_shape == CollisionComponent::Shape::ERectangle) {
		return m_rect.intersects(_other.m_rect);
	}
	/*if (typeid(mp_compo) == typeid(BoxComponent)) {
		return m_rect.intersects(_other.m_rect);
	}*/
	return false;
}

void CollisionObj::setCollisionBox(ofRectangle _rect)
{
	m_rect = _rect;
}
