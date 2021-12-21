#pragma once
#include "ofMain.h"
#include "Parameter.h"

class Effect
{
public:
	Effect();
	~Effect();

	static void healHP(int val);
	static void increaseHP(int val);

	static void increaseATK(int val);

	static void increaseDEF(int val);
private:
};


