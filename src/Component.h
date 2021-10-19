#pragma once
#include"ofMain.h"

class GameActor;
class Component
{
public:
	enum class ComponentState {  //Component�̏��
		EActive  //�ʏ�Bupdate()���s��
		, EUnControl  //update()�͍s�����Ainput()�͍s��Ȃ�
		, EPause  //update()���s��Ȃ�
		, EErace  //�폜����
	};
	enum class ComponentDrawState {  //Component�̕`����
		EVisible  //�`�悷��
		, EHidden  //�`�悵�Ȃ�(�폜�͂���Ă��Ȃ�)
	};

private:
	string m_componentName;
protected:
	GameActor* mp_gActor;

	ComponentState m_CpntState;
	ComponentDrawState m_CpntDrawState;
public:
	GameActor* gActor() {
		return mp_gActor;
	}

	virtual void update() = 0;
	virtual void input() = 0;

	Component(GameActor* _gactor, string _name = "") 
		:mp_gActor(_gactor)
		, m_componentName(_name)
		, m_CpntState(ComponentState::EActive)
		, m_CpntDrawState(ComponentDrawState::EVisible)
		{}
	virtual ~Component() {}

public:
	inline string getComponentName() 
	{ 
		return m_componentName;
	
	}
	inline const ComponentState GetComponentState()
	{
		return m_CpntState;
	}
	inline const ComponentDrawState GetComponentDrawState()
	{
		return m_CpntDrawState;
	}
	
	inline void StateCpntActive()
	{
		m_CpntState = ComponentState::EActive;
	}
	inline void StateCpntUnControl()
	{
		m_CpntState = ComponentState::EUnControl;
	}
	inline void StateCpntPause()
	{
		m_CpntState = ComponentState::EPause;
	}
	inline void StateCpntErace()
	{
		m_CpntState = ComponentState::EErace;
	}

	inline void StateCpntVisible()
	{
		m_CpntDrawState = ComponentDrawState::EVisible;
	}
	inline void StateCpntHidden()
	{
		m_CpntDrawState = ComponentDrawState::EHidden;
	}
};