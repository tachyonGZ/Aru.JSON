#include "CJSONObject.hpp"

CJSONObject::CJSONObject()
{
	
}

CJSONObject& CJSONObject::ParseFromFile(std::ifstream fs)
{
	json_ = nlohmann::json::parse(fs);
}