#pragma once

#include "CJSONObject.hpp"

class CJSONObjectTypeHandle : public IHandleTypeDispatch
{
public:
	virtual void OnHandleDestroy(HandleType_t type, void* object) override final
	{
		if (nullptr == object)
		{
			return;
		}

		delete reinterpret_cast<aru::CJSONObject *>(object);
	}
};