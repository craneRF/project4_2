#pragma once
#include "ofMain.h"

struct EnemySkill {
	int attackpower;
	string attackStatement;
};

struct EnemyParam
{
	string name;
	string ImageName;
	ofVec3f scale;
	int HP;
	int Def;
	map<string, EnemySkill> eSkill;
};

class EnemyObject
{
public:
	const static int Error = -1;
	struct EnemySkill error_enemyskill = { -1,"Error" };

	EnemyObject();
	virtual ~EnemyObject() {};

	virtual void initialize() {};

	void setEnemyStatus(string key, int val);
	int getEnemyStatus(string key) const;

	void setEnemySkill(string key, int val);
	EnemySkill getEnemySkill(string key) const;

	EnemyParam m_eParam;
private:
	map<string, int> m_enemyStatus;
	map<string, EnemySkill> m_enemySkill;
};

class NomalEnemy : public EnemyObject
{
public:
	NomalEnemy();
	virtual void initialize();
};

class SmallEnemy final : public NomalEnemy
{
public:
	SmallEnemy();
	virtual void initialize();
};