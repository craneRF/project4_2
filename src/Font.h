#pragma once
#include "ofMain.h"

template<typename T> class ResourceManager;  //template�t���N���X�̑O���錾

class Font
{
public:
	Font();
	~Font();

	inline const unordered_map<string, unordered_map<int, shared_ptr<ofTrueTypeFont>>> GetFontMap(){ return m_FontData; }

private:
	bool Load();

	string m_fontname;  //m_FontData�̃L�[�ƂȂ�ϐ�

	unique_ptr< ResourceManager<string>> mp_fontManager;

	const vector<int> m_fontSize = {  //�g�p����ł��낤�t�H���g�̃T�C�Y�����炩���ߗp�ӂ��Ă���
		8, 18, 28/*, 38, 48, 58*/
		//�t�H���g�T�C�Y�𑝂₷�ƃ������s���������ŃG���[���o�ċN�����Ȃ��͗l
	};

	unordered_map<string, unordered_map<int, shared_ptr<ofTrueTypeFont>>> m_FontData;  //�t�H���g�̎�ފǗ��}�b�v
};

