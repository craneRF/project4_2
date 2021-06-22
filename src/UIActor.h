#pragma once
#include "ofMain.h"
#include "Actor.h"

/*
* 基本的にコンポーネントを持つことができないGameActorみたいなもの
*/
class UIActor : public Actor
{
public:
	enum class UIActorState {
		EActive  //描画処理・描画を動かす処理・操作処理の全てを行う
		, EDrawing  //描画処理・描画を動かす処理を行う(操作処理はされない)
		, EDrew  //描画処理のみ行う(描画はされるが動かないし、操作処理もされない)
		, EClosing  //削除される(GameActorの削除と同じ処理)
	};

	UIActor(string _name = "");
	virtual ~UIActor();

	void caluculateWorldTransform() override;

	//void initialize(ofVec3f _pos, string _name);
	void update(float _deltaTime);
	void input(float _deltaTime);
	void draw(float _deltaTime);

	void Close();

	//void setParam(ofVec3f _pos = { 0,0,0 }, ofVec3f _scale = { 1,1 }, float _angle = 0.0f);
	UIActor* addUIChild();
	void RemoveAllChild();


	//function<void()> drawfunc;

	UIActor* mp_UIparent;

protected:
	/*ofVec3f m_pos;
	ofVec3f m_worldPos;

	float m_rotAngle;
	float m_worldRotAngle;

	ofVec3f m_scale;
	ofVec3f m_worldScale;

	string m_name;*/

	vector<unique_ptr<UIActor>> m_UIchildList;
	queue<unique_ptr<UIActor>> m_UIchildAddQue;

	UIActorState m_UIActorState;

public:
	/*inline ofVec3f& Pos() 
	{
		return m_pos; 
	}
	inline float& RotAngle()
	{
		return m_rotAngle;
	}
	inline ofVec3f& Scale() 
	{
		return m_scale; 
	}
	inline string& Name()
	{ 
		return m_name;
	}*/
	inline const UIActorState GetUIActorState() 
	{
		return m_UIActorState; 
	}
};

