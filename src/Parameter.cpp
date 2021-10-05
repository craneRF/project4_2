#include "Parameter.h"

Parameter::Parameter()
{
	initialize();
}

void Parameter::initialize()
{
	m_playermap["HP"] = 10;
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