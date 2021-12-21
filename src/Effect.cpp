#include "Effect.h"
#include "ofApp.h"

Effect::Effect()
{
	
}

Effect::~Effect()
{
}

void Effect::healHP(int val) {
	auto HP = val + ofApp::getInstance()->mp_prm->getPlayerParam("HP");
	if (HP > ofApp::getInstance()->mp_prm->getPlayerParam("MAXHP")) {
		HP = ofApp::getInstance()->mp_prm->getPlayerParam("MAXHP");
	}

	ofApp::getInstance()->mp_prm->setPlayerParam("HP", HP);
}

void Effect::increaseHP(int val) {
	ofApp::getInstance()->mp_prm->setPlayerParam("MAXHP", val + ofApp::getInstance()->mp_prm->getPlayerParam("MAXHP"));
}

void Effect::increaseATK(int val) {
	ofApp::getInstance()->mp_prm->setPlayerParam("ATTACK", val + ofApp::getInstance()->mp_prm->getPlayerParam("ATTACK"));
}

void Effect::increaseDEF(int val) {
	ofApp::getInstance()->mp_prm->setPlayerParam("DEF", val + ofApp::getInstance()->mp_prm->getPlayerParam("DEF"));
}
