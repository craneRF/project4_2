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
	virtual GameState* update() = 0;
	virtual void exit(Parameter& _pprm) = 0;


	shared_ptr<Parameter> m_prmInState = make_shared<Parameter>();
};

// �^�C�g���V�[��
class GameStateTitle final : public GameState {
private:
	ofPath path;

public:
	virtual void enter(Parameter _pprm);
	virtual GameState* update();
	virtual void exit(Parameter& _pprm);

	class UIPanelCanvas* mp_BHUD;
	class GameActor* mp_rect;
	class GameActor* mp_rect2;
	class GameActor* mp_marin;
};

class MapComponent;
// �}�b�v�V�[��
class GameStateMap final : public GameState {
private:
	MapComponent* mp_mapComp;

public:
	virtual void enter(Parameter _pprm);
	virtual GameState* update();
	virtual void exit(Parameter& _pprm);
	

};

class BattleComponent;
// �퓬�V�[��
class GameStateBattle final : public GameState {
private:
	// �퓬�V�X�e��
	BattleComponent* mp_BattleComp;

public:
	virtual void enter(Parameter _pprm);
	virtual GameState* update();
	virtual void exit(Parameter& _pprm);

	float m_angle;
	class MoveComponent* m_move;

};