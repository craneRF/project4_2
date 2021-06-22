#pragma once
#include"ofMain.h"

class Actor
{
public:
	Actor(string _name = "");
	virtual ~Actor();

	function<void()> drawfunc;


	virtual void caluculateWorldTransform();

	void initialize(ofVec3f _pos, string _name);
	void draw();

	void setParam(ofVec3f _pos = { 0,0,0 }, ofVec3f _scale = { 1,1 }, float _angle = 0.0f);

protected:
	ofVec3f m_pos;
	ofVec3f m_worldPos;

	float m_rotAngle;
	float m_worldRotAngle;

	ofVec3f m_scale;
	ofVec3f m_worldScale;

	string m_name;

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
	inline ofVec3f& WOrldScale()
	{
		return m_worldScale;
	}
	inline string& Name()
	{
		return m_name;
	}
};

