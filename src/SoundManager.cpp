#include "ofMain.h"
#include "SoundManager.h"

//ファイル名が日本語だと読み込まない
const string SoundManager::soundList[] = {
		"titleBGM.mp3",
		"mapBGM.mp3",
		"battleBGM.mp3",
		"select.mp3",
		"enter.mp3",
		"cancel.mp3",
		"guard.mp3",
		"slash.mp3",
		"explosion.mp3",
		"UnicornBGM.mp3",
		"SnakeBeep.mp3",
		"explosion.mp3",
		"missile.mp3",
		"beam-gun.mp3",
};

SoundManager::SoundManager()
{
	for (auto & snd : soundList) {
		ofSoundPlayer p;
		p.load("sounds\\" + snd);
		soundResources.push_back(p);
	}
}

SoundManager::~SoundManager()
{
	for (auto& snd : soundResources) {
		snd.unload();
	}
}

void SoundManager::play(int _id)
{
	soundResources[_id].play();
}

void SoundManager::stop(int _id)
{
	soundResources[_id].stop();
}

void SoundManager::loop(int _id)
{
	soundResources[_id].setLoop(true);
	soundResources[_id].play();
}

void SoundManager::setVolume(int _id, float _vol)
{
	soundResources[_id].setVolume(_vol);
}
