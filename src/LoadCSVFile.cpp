#include "LoadCSVFile.h"


LoadCSVFile::LoadCSVFile(const std::string _filename, std::vector<std::vector<std::string>>& _table, const char _delimiter)
	: mFilestream(_filename)
{
	if (!mFilestream.is_open()) {
		return;
	}
	SetTable(_table, _delimiter);
}

LoadCSVFile::~LoadCSVFile()
{
}

void LoadCSVFile::SetTable(std::vector<std::vector<std::string>>& _table, const char _delimiter)
{
	while (!mFilestream.eof()) {
		std::string buffer;
		mFilestream >> buffer;

		std::vector<std::string> record;
		std::istringstream streamBuffer(buffer);
		std::string token;

		while (std::getline(streamBuffer, token, _delimiter)) {
			record.emplace_back(token);
		}
		_table.emplace_back(record);
	}
	_table.pop_back();
}
