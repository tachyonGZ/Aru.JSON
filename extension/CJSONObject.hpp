#pragma once

#include <nlohmann/json.hpp>

#include <fstream>
#include <stack>
#include <string>

namespace aru{

class CJSONObject
{
public:
	CJSONObject();
	CJSONObject &ParseFromFile(std::ifstream &fs);
	//CJSONObject &ParseFromString(std::string );

	template<typename T>
	T Get(std::string);
private:
	nlohmann::json json_;
};

template<typename T>
T CJSONObject::Get(std::string json_ptr)
{
	return json_.at(nlohmann::json::json_pointer(json_ptr));
}

}