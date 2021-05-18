#pragma once
#include "ofMain.h"

class GameActor;
class CollisionComponent;
enum CollisionType;

class CollisionObj
{
private:
	ofRectangle m_rect;
public:
	CollisionObj(CollisionComponent* _compo);
	virtual ~CollisionObj() {};
	bool checkCollide(const CollisionObj& _other) const;
	void setCollisionParam(ofRectangle _rect);
	CollisionType m_ctype;
	CollisionComponent* mp_compo;
};
