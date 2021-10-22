#pragma once
#include "ofMain.h"
#include "PlayerActor.h"
#include "EnemyActor.h"

class Parameter;
class GameState
{
private:

protected:
	GameActor* mp_fontActor;
	GameActor* mp_actor;
	GameActor* mp_actor1;
	GameActor* mp_actor2;

public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter(Parameter _pprm) = 0;
	virtual GameState* update(float _deltatime) = 0;
	virtual void exit(Parameter& _pprm) = 0;


	shared_ptr<Parameter> m_prmInState = make_shared<Parameter>();
};

// �^�C�g���V�[��
class GameStateTitle final : public GameState {
private:
	ofPath path;

public:
	virtual void enter(Parameter _pprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _pprm);
};

// �}�b�v�V�[��
class GameStateMap final : public GameState {
private:
	GameActor* mp_mapActor;

public:
	virtual void enter(Parameter _pprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _pprm);
	

};

// �퓬�V�[��
class BattleComponent;
class GameStateBattle final : public GameState {
private:
	// �v���C���[
	PlayerActor* mp_Player;
	EnemyActor* mp_Enemy;
	// �G�l�~�[�z��
	vector<EnemyActor*> m_EnemyList;
	// �퓬�V�X�e���A�N�^�[
	BattleComponent* mp_BattleComp;
	//GameActor* mp_BattleActor;


public:
	virtual void enter(Parameter _pprm);
	virtual GameState* update(float _deltatime);
	virtual void exit(Parameter& _pprm);

	float m_angle;
	class MoveComponent* m_move;

	class UIPanelCanvas* mp_BHUD;
};