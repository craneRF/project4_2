#include "Parameter.h"
#include "EnemyObject.h"
#include "BulletObject.h"

Parameter::Parameter()
{
	initialize();
}

void Parameter::initialize()
{
	m_playermap["MAXHP"] = 50;
	m_playermap["HP"] = 1;
	//m_playermap["HP"] = 15;
	m_playermap["ATTACK"] = 1;
	m_playermap["DEF"] = 1;
	m_playermap["LIFE"] = 0;

	// スキルリスト初期化
	{
		m_skillList.clear();
		m_skillList.emplace_back(5, "NormalSkill", BulletType::Nomal, 1);
		m_skillList.emplace_back(3, "SmallSkill", BulletType::Small, 1);
		m_skillList.emplace_back(6, "BigSkill", BulletType::Big, 1);
		m_skillList.emplace_back(6, "aaaa", BulletType::KeyGuard, 3);
	}
}

void Parameter::setInt(string key, int val) {
	m_imap[key] = val;
}

int Parameter::getInt(string key)const {
	auto it = m_imap.find(key);
	if (m_imap.end() == it) {
		return Error;
	}
	else {
		return it->second;
	}
}

void Parameter::setPlayerParam(string key, int val) {
	m_playermap[key] = val;
}

int Parameter::getPlayerParam(string key)const {
	auto it = m_playermap.find(key);
	if (m_playermap.end() == it) {
		return Error;
	}
	else {
		return it->second;
	}
}

void Parameter::AddSkill(Skill _skill)
{
	m_skillList.emplace_back(_skill);
}

const vector<Skill>& Parameter::GetSkillList() const
{
	return m_skillList;
}
