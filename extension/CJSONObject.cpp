#include "CJSONObject.hpp"

aru::CJSONObject::CJSONObject()
{
	;
}

aru::CJSONObject &aru::CJSONObject::ParseFromFile(std::ifstream &fs)
{
	json_ = nlohmann::json::parse(fs);
	return *this;
}