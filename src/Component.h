#pragma once
#include"ofMain.h"

class GameActor;
class Component
{
public:
	enum class ComponentState {  //Componentの状態
		EActive  //通常。update()を行う
		, EUnControl  //update()は行うが、input()は行わない
		, EPause  //update()を行わない
		, EErace  //削除する
	};
	enum class ComponentDrawState {  //Componentの描画状態
		EVisible  //描画する
		, EHidden  //描画しない(削除はされていない)
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