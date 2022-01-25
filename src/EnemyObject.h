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
	string PartsName;				// 名前
	string ImageName;				// 画像名
	int HP;							// 体力
	int Def;						// 防御力
	ofVec3f Pos;					// 座標
	ofVec3f Scale;					// スケール
	float angle;					// 角度
	bool isCore;					// 重要な部位か
};

struct EnemyParam
{
	string EnemyName;				// 名前
	ofVec3f scale;					// スケール
	int HP;							// 体力
	int Attack;						// 攻撃力
	int Def;						// 防御力
	bool isPowerByParts;			// パーツがある間無敵
	map<string, EnemyParts>eParts;	// パーツマップ
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