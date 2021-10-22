#pragma once
#include "ofMain.h"

class InputManager
{
private:
	//キーマップ定義構造体
	struct KeyDefine {
		string name;
		int posiKey;
		int negaKey;
	};
	static KeyDefine keyMap_[];
	static size_t keyListSize_;
	//毎フレームのキー状態を保存する構造体
	struct KeyStatus {
		int nowValue;
		int backValue;
	};
	vector<KeyStatus> keyStatus_;
	//アクション名で検索するためのmap
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

