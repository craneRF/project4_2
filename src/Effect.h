#pragma once
#include "ofMain.h"
#include "Parameter.h"

class Effect
{
public:
	Effect();
	~Effect();

	void healHP(int val);
	void increaseHP(int val);

	void increaseATK(int val);

	void increaseDEF(int val);
private:
};


