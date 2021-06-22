#pragma once
#include "ofMain.h"

struct EnemySkill {
	int attackpower;
	string attackStatement;
};

class EnemyObject
{
public:
	const static int Error = -1;
	struct EnemySkill error_enemyskill = { -1,"Error" };

	EnemyObject() {};
	virtual ~EnemyObject() {};

	virtual void initialize() {};

	void setEnemyStatus(string key, int val);
	int getEnemyStatus(string key) const;

	void setEnemySkill(string key, int val);
	EnemySkill getEnemySkill(string key) const;
private:
	map<string, int> m_enemyStatus;
	map<string, EnemySkill> m_enemySkill;
};

class NomalEnemy final : public EnemyObject
{
public:
	NomalEnemy();
	virtual void initialize();
};