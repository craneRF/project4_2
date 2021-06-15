#pragma once
#include "Parameter.h"

class GameState
{
private:

protected:
	GameActor* mp_fontActor;

public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter(Parameter _inportprm) = 0;
	virtual GameState* update(float _deltatime) = 0;
	virtual void exit(Parameter& _reprm) = 0;

	GameActor* mp_actor;
	GameActor* mp_actor1;
	GameActor* mp_actor2;

	Parameter m_prmInState;
};

// �^�C�g���V�[��
class GameStateTitle final : public GameState {
private:

public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};

// �}�b�v�V�[��
class GameStateMap final : public GameState {
private:
	GameActor* mp_mapActor;

public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};

// �퓬�V�[��
class BattleComponent;
class GameStateBattle final : public GameState {
private:
	// �v���C���[
	GameActor* mp_Player;
	// �G�l�~�[�z��
	vector<GameActor*> m_EnemyList;
	// �퓬�V�X�e���A�N�^�[
	BattleComponent* mp_BattleComp;
	//GameActor* mp_BattleActor;


public:
	virtual void enter(Parameter _inportprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _reprm);
};