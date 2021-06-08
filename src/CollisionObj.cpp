#include "GameActor.h"
#include "CollisionObj.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"

//CollisionObj::CollisionObj(GameActor* _actor) :
CollisionObj::CollisionObj(CollisionComponent* _compo) :
	m_rect(ofRectangle()),
	mp_compo(_compo),
	m_ctype(CollisionType::DEFAULT)
{
}

bool CollisionObj::checkCollide(const CollisionObj& _other) const {
	return m_rect.intersects(_other.m_rect);
}


void CollisionObj::setCollisionParam(ofRectangle _rect){
	m_rect = _rect;
}
