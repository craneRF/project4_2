#pragma once
enum  EnemyType {
	//NONE,
	Nomal,
	//Small,
	//Big,
	Slime,
	Totem,
	Crab,
	TYPE_NUM,
};

struct StrEnemyType : public string {
	StrEnemyType(EnemyType type) {
		switch (type)
		{
		//case NONE:
		//	assign("NONE");
		//	break;
		case Nomal:
			assign("Nomal");
			break;
		//case Small:
		//	assign("Small");
		//	break;
		//case Big:
		//	assign("Big");
		//	break;
		case Slime:
			assign("Slime");
			break;
		case Totem:
			assign("Totem");
			break;
		case Crab:
			assign("Crab");
			break;
		default:
			assign("");
			break;
		}
	}
};