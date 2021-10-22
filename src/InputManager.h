#pragma once
#include "ofMain.h"

class InputManager
{
private:
	//�L�[�}�b�v��`�\����
	struct KeyDefine {
		string name;
		int posiKey;
		int negaKey;
	};
	static KeyDefine keyMap_[];
	static size_t keyListSize_;
	//���t���[���̃L�[��Ԃ�ۑ�����\����
	struct KeyStatus {
		int nowValue;
		int backValue;
	};
	vector<KeyStatus> keyStatus_;
	//�A�N�V�������Ō������邽�߂�map
	map<string, int> keylist_;
public:
	InputManager();
	virtual ~InputManager();
	bool getButtonDown(string _keyName);
	bool getButtonUp(string _keyName);
	bool getButtonHold(string _keyName);
	bool getButton(string _keyName);
	int getAxis(string _keyName);
	void update();
};

