#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class LoadCSVFile
{
public:
	LoadCSVFile(const std::string _filename, std::vector<std::vector<std::string>>& _table, const char _delimiter = ',');
	~LoadCSVFile();

	void SetTable(std::vector<std::vector<std::string>>& _table, const char _delimiter = ',');

private:
	std::fstream mFilestream;
};

