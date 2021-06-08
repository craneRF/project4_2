#pragma once
#include "ofMain.h"

struct AnimFrame
{
	ofImage * mp_image;
	ofVec2f  m_offset;
	bool m_visible;
	int m_time;
	int m_next;
};

class AnimSeq
{
private:
	vector<AnimFrame> mp_seqdata;
public:
	AnimSeq(string _fileName = "");
	virtual ~AnimSeq();
	AnimFrame& getFrame(int idx);
	void loadFromFile(string _fileName);
};

