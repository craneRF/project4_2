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

void EnemyObject::setEnemyParts(string partsname, ofVec3f pos, string imagename, int hp, int def, ofVec3f scale, float angle)
{
	m_eParam.eParts[partsname].PartsName = partsname;
	m_eParam.eParts[partsname].Pos = pos;
	m_eParam.eParts[partsname].ImageName = imagename;
	m_eParam.eParts[partsname].HP = hp;
	m_eParam.eParts[partsname].Def = def;
	m_eParam.eParts[partsname].Scale = scale;
	m_eParam.eParts[partsname].angle = angle;
}

//NomalEnemy
NomalEnemy::NomalEnemy() {
	initialize();
}

void NomalEnemy::initialize()
{
	m_eParam.scale = { 2.0f,2.0f };
	//m_eParam.scale = { 0.5,0.5 };
	//m_eParam.scale = { 1.5f,1.5f };
	m_eParam.HP = 20;
	m_eParam.ImageName = "enemy_robot_body1.png";
	setEnemySkill("NomalAttack", 10);

	setEnemyParts("arm_right", { -75,0 }, "enemy_robot_arm_R1.png", 1, 0, { 1.f,1.f }, -20);
	//setEnemyParts("body", { 0,0 }, "enemy_robot_body1.png", 1, 0, { 1.f,1.f });
	setEnemyParts("arm_left", { 55,0 }, "enemy_robot_arm_L1.png", 1, 0, { 1.f,1.f }, 20);
}

//SmalleEnemy
SmallEnemy::SmallEnemy()
{
	initialize();
}

void SmallEnemy::initialize()
{
	m_eParam.scale = { 0.2,0.2 };
	//m_eParam.ImageName = "marine_icon.png";
}
