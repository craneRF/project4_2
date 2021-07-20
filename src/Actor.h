#pragma once
#include"ofMain.h"

/*
* ���ۃN���X(�p����p�̃N���X)
* �����A�N�^�[����肽����΁AGameActor��UIActor���g�p����悤�ɁB
* �������́AActor���p�������N���X�����悤�ɁB
*/
class Actor
{
public:
	enum class ActorState {  //Actor�̏��
		EActive  //�ʏ�Bupdate()���s��
		,EUnControl  //update()�͍s�����Ainput()�͍s��Ȃ�
		,EPause  //update()�Einput()���s��Ȃ�
		,EErace  //�폜����
	};
	enum class ActorDrawState {  //Actor�̕`����
		EVisible  //�`�悷��
		,EHidden  //�`�悵�Ȃ�(�폜�͂���Ă��Ȃ�)
	};

protected:
	ofVec3f m_pos;
	ofVec3f m_worldPos;

	float m_rotAngle;
	float m_worldRotAngle;

	ofVec3f m_scale;
	ofVec3f m_worldScale;

	string m_name;

	ActorState m_ActorState;
	ActorDrawState m_ActorDrawState;

public:
	Actor(string _name = "");
	virtual ~Actor() = 0;

	function<void()> drawfunc;

	Actor* mp_parent;


	virtual void caluculateWorldTransform();

	void initialize(ofVec3f _pos, string _name);
	void draw();

	void setParam(ofVec3f _pos = { 0,0,0 }, ofVec3f _scale = { 1,1 }, float _angle = 0.0f);

public:
	inline ofVec3f& Pos()
	{
		return m_pos;
	}
	inline ofVec3f& WorldPos()
	{
		return m_worldPos;
	}
	inline float& RotAngle()
	{
		return m_rotAngle;
	}
	inline float& WorldRotAngle()
	{
		return m_worldRotAngle;
	}
	inline ofVec3f& Scale()
	{
		return m_scale;
	}
	inline ofVec3f& WorldScale()
	{
		return m_worldScale;
	}
	inline string& Name()
	{
		return m_name;
	}


	inline const ActorState GetActorState() 
	{
		return m_ActorState;
	}
	inline const ActorDrawState GetActorDrawState() 
	{
		return m_ActorDrawState;
	}

	inline void StateActive()
	{
		m_ActorState = ActorState::EActive;
	}
	inline void StateUnControl()
	{
		m_ActorState = ActorState::EUnControl;
	}
	inline void StatePause()
	{
		m_ActorState = ActorState::EPause;
	}
	inline void StateErace()
	{
		m_ActorState = ActorState::EErace;
	}

	inline void StateVisible()
	{
		m_ActorDrawState = ActorDrawState::EVisible;
	}
	inline void StateHidden()
	{
		m_ActorDrawState = ActorDrawState::EHidden;
	}
};

