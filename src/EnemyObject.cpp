#include "EnemyObject.h"
#include "BulletObject.h"

EnemyObject::EnemyObject() {
	m_eParam.EnemyName = "";
	m_eParam.scale = { 1.f,1.f };
	m_eParam.HP = 1;
	m_eParam.Attack = 1;
	m_eParam.Def = 0;
	m_eParam.isPowerByParts = false;
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

void EnemyObject::setEnemySkill(string key, int val, BulletType type, int bulletCount)
{
	m_enemySkill[key] = { val,key, type, bulletCount };
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

EnemySkill EnemyObject::getEnemySkill(int elem) const
{
	elem = rand() % m_enemySkill.size();

	if (m_enemySkill.size() <= elem || elem < 0) {
		return error_enemyskill;
	}

	auto it = m_enemySkill.begin();
	for (int i = 0; i < elem; ++i) {
		it++;
	}
	return it->second;
}

void EnemyObject::setEnemyParts(string partsname, ofVec3f pos, string imagename, bool _isCore, int hp, int def, ofVec3f scale, float angle)
{
	m_eParam.eParts[partsname].PartsName = partsname;
	m_eParam.eParts[partsname].Pos = pos;
	m_eParam.eParts[partsname].ImageName = imagename;
	m_eParam.eParts[partsname].HP = hp;
	m_eParam.eParts[partsname].Def = def;
	m_eParam.eParts[partsname].Scale = scale;
	m_eParam.eParts[partsname].angle = angle;
	m_eParam.eParts[partsname].isCore = _isCore;
}

//NomalEnemy
NomalEnemy::NomalEnemy() {
	initialize();
}

void NomalEnemy::initialize()
{
	m_eParam.scale = { 2.0f,2.0f };
	m_eParam.HP = 20;
	m_eParam.Attack = 2;

	setEnemySkill("SmallAttack", 10, BulletType::Small, 1);
	setEnemySkill("NomalAttack", 10, BulletType::Nomal, 1);
	setEnemySkill("KeyAttack", 10, BulletType::KeyGuard, 3);
	
	setEnemyParts("1_arm_right", { -85,-40 }, "enemy_robot_arm_R1.png", false, 1, 0, { 1.f,1.f }, -20);
	setEnemyParts("2_body", { 0,0 }, "enemy_robot_body1.png", true,1, 0, { 1.f,1.f });
	setEnemyParts("3_arm_left", { 60,-45 }, "enemy_robot_arm_L1.png", false, 1, 0, { 1.f,1.f }, 20);
}

//SmalleEnemy
SmallEnemy::SmallEnemy()
{
	initialize();
}

void SmallEnemy::initialize()
{
	m_eParam.scale = { 0.2,0.2 };
}

TotemEnemy::TotemEnemy()
{
	initialize();
}

void TotemEnemy::initialize()
{
	m_eParam.scale = { 0.5f,0.5f };
	m_eParam.HP = 20;
	m_eParam.isPowerByParts = true;
	setEnemySkill("NomalAttack", 10, BulletType::KeyGuard, 3);

	setEnemyParts("body1", { 0,-20 }, "enemy_pole_body1.png", true, 1, 0, { 1.f,1.f }, 0);
	setEnemyParts("body2", { 0,350 }, "enemy_pole_body2.png", false, 1, 0, { 1.f,1.f }, 0);
	setEnemyParts("body3", { 0,279 + 350 }, "enemy_pole_body3.png", false, 1, 0, { 1.f,1.f }, 0);
}

CrabEnemy::CrabEnemy()
{
	initialize();
}

void CrabEnemy::initialize()
{
	m_eParam.scale = { 1.0f,1.0f };
	m_eParam.HP = 20;
	setEnemySkill("NomalAttack", 10, BulletType::Nomal, 1);

	setEnemyParts("3_arm_right", { -125,50 }, "enemy_crab_arm_R1.png", false, 1, 0, { 1.f,1.f }, 0);
	setEnemyParts("1_body", { 0,0 }, "enemy_crab_body1.png", true, 1, 0, { 1.f,1.f });
	setEnemyParts("2_arm_left", { 100,100 }, "enemy_crab_arm_L1.png", false, 1, 0, { 1.f,1.f }, 0);
}

SlimeEnemy::SlimeEnemy()
{
	initialize();
}

void SlimeEnemy::initialize()
{
	m_eParam.scale = { 1.0f,1.0f };
	m_eParam.HP = 20;
	setEnemySkill("NomalAttack", 10, BulletType::Nomal, 1);

	setEnemyParts("body", { 0,0 }, "enemy_slime.png", true, 1, 0, { 1.f,1.f });
}
