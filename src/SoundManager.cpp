#include "ofMain.h"
#include "SoundManager.h"

const string SoundManager::soundList[] = {
	"BGM01.mp3",
	"effect01.mp3",
	"shotse.wav",
	"explosion.mp3",
};

SoundManager::SoundManager()
{
	for (auto& snd : soundList) {
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
