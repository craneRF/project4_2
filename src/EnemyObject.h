#pragma once
#include "ofMain.h"

enum class BulletType;

struct EnemySkill {
	int attackpower;
	string attackStatement;
	BulletType type;
	int bulletCount;
};

struct EnemyParts {
	string PartsName;				// ���O
	string ImageName;				// �摜��
	int HP;							// �̗�
	int Def;						// �h���
	ofVec3f Pos;					// ���W
	ofVec3f Scale;					// �X�P�[��
	float angle;					// �p�x
	bool isCore;					// �d�v�ȕ��ʂ�
};

struct EnemyParam
{
	string EnemyName;				// ���O
	ofVec3f scale;					// �X�P�[��
	int HP;							// �̗�
	int Attack;						// �U����
	int Def;						// �h���
	bool isPowerByParts;			// �p�[�c������Ԗ��G
	map<string, EnemyParts>eParts;	// �p�[�c�}�b�v
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

	void setEnemySkill(string key, int val, BulletType type, int bulletCount);
	EnemySkill getEnemySkill(string key) const;
	EnemySkill getEnemySkill(int elem) const;

	void setEnemyParts(string partsname, ofVec3f pos, string imagename, bool _isCore,int hp = 1, int def = 0, ofVec3f scale = { 1,1,1 }, float angle = 0.f);

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

class SmallEnemy final : public EnemyObject
{
public:
	SmallEnemy();
	virtual void initialize();
};

class TotemEnemy final : public EnemyObject
{
public:
	TotemEnemy();
	virtual void initialize();
};

class CrabEnemy final : public EnemyObject
{
public:
	CrabEnemy();
	virtual void initialize();
};

class SlimeEnemy final : public EnemyObject
{
public:
	SlimeEnemy();
	virtual void initialize();
};