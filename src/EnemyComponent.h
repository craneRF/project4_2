#pragma once
#include "ofMain.h"
#include "Component.h"
#include "EnemyObject.h"

class GameActor;
class CollisionComponent;
class SpriteComponent;
class EnemyPartsComponent;

enum EnemyType;
struct EnemyParam;
struct EnemyParts;

class EnemyComponent  final : public Component
{
	friend class NomalEnemy;
private:
	SpriteComponent * mp_sprCpnt;
	int m_EnemyType = 0;

	static EnemyObject m_stdEnemy;
	static NomalEnemy m_nomalEnemy;
	static SmallEnemy m_smallEnemy;
public:
	EnemyComponent(GameActor* _gactor);
	virtual ~EnemyComponent();

	std::shared_ptr<EnemyPartsComponent>  mp_epCpnt;

	virtual void update(float _deltatime);
	virtual void input(float _deltatime);
	void onCollision(CollisionComponent*);

	EnemyParam getEnemy(int _enemytype);
	void setEnemyType(int _enemytype) { m_EnemyType = _enemytype; }

	//void setImage(GameActor* _parent, EnemyType _enemytype);

};

class EnemyPartsComponent : public Component
{
private:
	void CreateParts(GameActor * _parent, ofVec3f _pos, EnemyType _enemytype);

protected:
	ofVec3f m_pos = { 0,0 };
	EnemyComponent* enemyCpnt;
public:

	void setPos(ofVec3f _pos) { m_pos = _pos; }
	ofVec3f getPos() { return m_pos; }

	void EnemyPartsComponent::CreateEnemyBody(GameActor* _parent, ofVec3f _pos, EnemyType _enemytype, string _name = "EnemyBody");
};