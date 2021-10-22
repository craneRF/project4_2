#include "EnemyObject.h"

EnemyObject::EnemyObject() {
	m_eParam.EnemyName = "";
	m_eParam.ImageName = "";
	m_eParam.scale = { 1.f,1.f };
	m_eParam.HP = 1;
	m_eParam.Def = 0;
}

void EnemyObject::setEnemyStatus(string key, int val)
{
	m_enemyStatus[key] = val;
}

int EnemyObject::getEnemyStatus(string key) const
{
	auto it = m_enemyStatus.find(key);
	if (m_enemyStatus.end() == it) {
		return Error;
	}
	else {
		return it->second;
	}
}

void EnemyObject::setEnemySkill(string key, int val)
{
	m_enemySkill[key] = { val,key };
}

EnemySkill EnemyObject::getEnemySkill(string key) const
{
	auto it = m_enemySkill.find(key);
	if (m_enemySkill.end() == it) {
		return error_enemyskill;
	}
	else {
		return it->second;
	}
}

//NomalEnemy
NomalEnemy::NomalEnemy() {
	initialize();
}

void NomalEnemy::initialize()
{
	//m_eParam.scale = { 1.5f,1.5f };
	m_eParam.scale = { 0.5,0.5 };
	m_eParam.HP = 20;
	m_eParam.ImageName = "enemy_robot.png";
	setEnemySkill("NomalAttack", 10);
}

SmallEnemy::SmallEnemy()
{
	initialize();
}

void SmallEnemy::initialize()
{
	m_eParam.scale = { 0.2,0.2 };
	//m_eParam.ImageName = "marine_icon.png";
}
