#pragma once
#include "ofMain.h"

class SoundManager {
private:
	const static string soundList[];
	vector<ofSoundPlayer> soundResources;
public:
	SoundManager();
	virtual ~SoundManager();
	void play(int _id);
	void stop(int _id);
	void loop(int _id);
	void setVolume(int _id, float _vol);
};