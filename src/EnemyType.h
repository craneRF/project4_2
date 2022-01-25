#pragma once
enum  EnemyType {
	Nomal,
	Slime,
	Totem,
	Crab,
	TYPE_NUM,
	Boss,
};

struct StrEnemyType : public string {
	StrEnemyType(EnemyType type) {
		switch (type)
		{
		case Nomal:
			assign("Nomal");
			break;
		case Slime:
			assign("Slime");
			break;
		case Totem:
			assign("Totem");
			break;
		case Crab:
			assign("Crab");
			break;
		case Boss:
			assign("Boss");
			break;
		default:
			assign("");
			break;
		}
	}
};