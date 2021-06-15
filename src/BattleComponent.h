#pragma once
#include "Component.h"

class BattleComponent :public Component
{
public:
	enum class Result
	{
		NONE,
		WIN,
		LOSE,
	};
	enum class Turn
	{
		NONE,
		ME,
		ENEMY,
	};

private:
	int m_selectIndex = 0;
	// �Ƃ肠�����̘A�ő΍�
	bool m_start = false;

	// ����
	Result m_result = Result::NONE;
	// �^�[��
	Turn m_turn = Turn::NONE;

public:
	BattleComponent(GameActor* _gator);
	virtual ~BattleComponent();
	virtual void update(float _deltatime);

	Result GetResult() { return m_result; }
private:
	// ���s�̃`�F�b�N
	void CheckResult();
};