#pragma once
class GameState
{
private:

protected:
	GameActor* mp_fontActor;

public:
	GameState() {};
	virtual ~GameState() {};
	virtual void enter() = 0;
	virtual GameState* update(float _deltatime) = 0;
	virtual void exit() = 0;
};

// �^�C�g���V�[��
class GameStateTitle final : public GameState {
private:

public:
	virtual void enter();
	virtual GameState* update(float _deltatime);
	virtual void exit();
};

// �}�b�v�V�[��
class GameStateMap final : public GameState {
private:
	GameActor* mp_mapActor;

public:
	virtual void enter();
	virtual GameState* update(float _deltatime);
	virtual void exit();
};

// �퓬�V�[��
class GameStateBattle final : public GameState {
private:

public:
	virtual void enter();
	virtual GameState* update(float _deltatime);
	virtual void exit();
};
