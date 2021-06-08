#include "AnimSeq.h"

AnimSeq::AnimSeq(string _fileName)
{
	mp_seqdata.reserve(100);
	if (_fileName == "") return;
	loadFromFile(_fileName);
}

AnimSeq::~AnimSeq()
{
}

AnimFrame & AnimSeq::getFrame(int _idx)
{
	return mp_seqdata[_idx];
}

void AnimSeq::loadFromFile(string _fileName)
{
}
