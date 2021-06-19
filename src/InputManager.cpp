#include "ofMain.h"
#include "InputManager.h"

//�L�[�}�b�v��`
InputManager::KeyDefine InputManager::keyMap_[] = {
	{"Fire",'z',0},
	{"Bomb",'x',0},
	{"Horz",ofKey::OF_KEY_RIGHT,ofKey::OF_KEY_LEFT},
	{"Vert",ofKey::OF_KEY_DOWN,ofKey::OF_KEY_UP},
	{"Start",' ',0},
	{"Down",'s',0},
	{"Up",'w',0},
};
size_t InputManager::keyListSize_ = sizeof(keyMap_) / sizeof(keyMap_[0]);

InputManager::InputManager()
{
	//���O�������ł���map�����
	//�X�e�[�^�X�ۑ��p�\���̂̔z��(vector)�����
	for (size_t i = 0; i < keyListSize_; ++i) {
		keylist_[keyMap_[i].name] = i;
		keyStatus_.push_back({ 0,0 });
	}
}

InputManager::~InputManager()
{
	keylist_.clear();
	keyStatus_.clear();
}

//�S�A�N�V�����ɑ΂��čX�V����
//�|�W�L�[(+1)�ƃl�K�L�[(-1)�̍��v�ŉ�����ԂƂ���
//�O�t���[����Ԃ��c��
void InputManager::update()
{
	for (size_t i = 0; i < keyListSize_; ++i) {
		keyStatus_[i].backValue = keyStatus_[i].nowValue;
		keyStatus_[i].nowValue = static_cast<int>(ofGetKeyPressed(keyMap_[i].posiKey)) -
			static_cast<int>(ofGetKeyPressed(keyMap_[i].negaKey));
	}
}

bool InputManager::getButtonDown(string _keyName)
{
	//����� != �O��� && �����Ă�
	return
		(keyStatus_[keylist_[_keyName]].nowValue !=
			keyStatus_[keylist_[_keyName]].backValue) &&
		keyStatus_[keylist_[_keyName]].nowValue == 1;
}

bool InputManager::getButtonUp(string _keyName)
{
	//����� != �O��� && �����ĂȂ�
	return
		(keyStatus_[keylist_[_keyName]].nowValue !=
			keyStatus_[keylist_[_keyName]].backValue) &&
		keyStatus_[keylist_[_keyName]].nowValue == 0;
}

bool InputManager::getButton(string _keyName)
{
	return 1 == keyStatus_[keylist_[_keyName]].nowValue;
}

int InputManager::getAxis(string _keyName)
{
	return keyStatus_[keylist_[_keyName]].nowValue;
}

