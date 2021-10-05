#pragma once
enum  EnemyType {
	NONE,
	Nomal,
	Small,
	Big
};

struct StrEnemyType : public string {
	StrEnemyType(EnemyType type) {
		switch (type)
		{
		case NONE:
			assign("NONE");
			break;
		case Nomal:
			assign("Nomal");
			break;
		case Small:
			assign("Small");
			break;
		case Big:
			assign("Big");
			break;
		default:
			assign("");
			break;
		}
	}
};