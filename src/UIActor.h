#pragma once
#include "ofMain.h"
#include "Actor.h"

/*
* ��{�I�ɃR���|�[�l���g�������Ƃ��ł��Ȃ�GameActor�݂����Ȃ���
*/
class UIActor : public Actor
{
public:
	enum class UIActorState {
		EActive  //�`�揈���E�`��𓮂��������E���쏈���̑S�Ă��s��
		, EDrawing  //�`�揈���E�`��𓮂����������s��(���쏈���͂���Ȃ�)
		, EDrew  //�`�揈���̂ݍs��(�`��͂���邪�����Ȃ����A���쏈��������Ȃ�)
		, EClosing  //�폜�����(GameActor�̍폜�Ɠ�������)
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

