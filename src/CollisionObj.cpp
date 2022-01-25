#include "GameActor.h"
#include "CollisionObj.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"
#include "CollisionManager.h"

CollisionObj::CollisionObj(CollisionComponent* _compo) :
	m_rect(ofRectangle()),
	mp_compo(_compo),
	m_ctype(CollisionType::DEFAULT)
{
}

bool CollisionObj::checkCollide(const CollisionObj& _other) const {
	if (mp_compo->m_shape == CollisionComponent::Shape::ERectangle) {
		auto interval = ofVec2f(mp_compo->gActor()->WorldPos() - _other.mp_compo->gActor()->WorldPos());

		ofVec2f ea1 = ofVec2f{ 0, m_rect.getBottom() - m_rect.getTop() }.rotate(mp_compo->gActor()->WorldRotAngle()) * 0.5f;
		ofVec2f ea2 = ofVec2f{ m_rect.getRight() - m_rect.getLeft(), 0 }.rotate(mp_compo->gActor()->WorldRotAngle()) *0.5f;
		ofVec2f eb1 = ofVec2f{ 0, _other.m_rect.getBottom() - _other.m_rect.getTop() }.rotate(_other.mp_compo->gActor()->WorldRotAngle()) *0.5f;
		ofVec2f eb2 = ofVec2f{ _other.m_rect.getRight() - _other.m_rect.getLeft(), 0 }.rotate(_other.mp_compo->gActor()->WorldRotAngle()) *0.5f;

		ofVec2f L;
		//•ª—£Ž²
		// ea1
		{
			L = ea1.getNormalized();

			// rA‚¨‚æ‚ÑrB‚ðŽZo
			float ra = ea1.length();
			float rb = fabs(L.dot(eb1)) + fabs(L.dot(eb2));

			// ’†S“_ŠÔ‚Ì‹——£‚ðŽZo
			float Interval = fabs(interval.dot(L));

			// Õ“Ë”»’è
			if (Interval > ra + rb)
				return false;
		}
		// ea2
		{
			L = ea2.getNormalized();

			// rA‚¨‚æ‚ÑrB‚ðŽZo
			float ra = ea2.length();
			float rb = fabs(L.dot(eb1)) + fabs(L.dot(eb2));

			// ’†S“_ŠÔ‚Ì‹——£‚ðŽZo
			float Interval = fabs(interval.dot(L));

			// Õ“Ë”»’è
			if (Interval > ra + rb)
				return false;
		}
		// eb1
		{
			L = eb1.getNormalized();

			// rA‚¨‚æ‚ÑrB‚ðŽZo
			float ra = fabs(L.dot(ea1)) + fabs(L.dot(ea2));
			float rb = eb1.length();

			// ’†S“_ŠÔ‚Ì‹——£‚ðŽZo
			float Interval = fabs(interval.dot(L));

			// Õ“Ë”»’è
			if (Interval > ra + rb)
				return false;
		}
		// eb2
		{
			L = eb2.getNormalized();

			// rA‚¨‚æ‚ÑrB‚ðŽZo
			float ra = fabs(L.dot(ea1)) + fabs(L.dot(ea2));
			float rb = eb2.length();

			// ’†S“_ŠÔ‚Ì‹——£‚ðŽZo
			float Interval = fabs(interval.dot(L));

			// Õ“Ë”»’è
			if (Interval > ra + rb)
				return false;
		}
		return true;
	}
	return false;
}

void CollisionObj::setCollisionBox(ofRectangle _rect)
{
	m_rect = _rect;
}
