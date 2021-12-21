#pragma once

#include "GameActor.h"

class CreateActor
{
public:
	/*CreateActor();
	~CreateActor();*/

	static GameActor* CreatePlayer(string _name = "");
	static GameActor* CreateEnemy(string _name = "");
};


// CreateActor::SetTable(const std::string _filename, std::vector<std::vector<std::string>>& _table, const char _delimiter)
//{
//	std::fstream filestream(_filename);
//	if (!filestream || !filestream.is_open()) {
//		return false;
//	}
//
//	while (!filestream.eof()) {
//		std::string buffer;
//		filestream >> buffer;
//
//		std::vector<std::string> record;
//		std::istringstream streamBuffer(buffer);
//		std::string token;
//
//		while (std::getline(streamBuffer, token, _delimiter)) {
//			record.emplace_back(token);
//		}
//		_table.emplace_back(record);
//	}
//	_table.pop_back();
//
//	return true;
//}