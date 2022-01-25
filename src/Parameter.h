#pragma once
#include "ofMain.h"

class Parameter
{
public:
	const static int Error = -1;

	Parameter();
	virtual ~Parameter() = default;

	void initialize();

	void setInt(string key, int val);
	int getInt(string key) const;

	void setPlayerParam(string key, int val);
	int getPlayerParam(string key) const;

	void AddSkill(struct Skill _skill);
	const vector<Skill>& GetSkillList() const;
private:
	map<string, int> m_imap;
	map<string, int> m_playermap;
	vector<Skill> m_skillList;
};