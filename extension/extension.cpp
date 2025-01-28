#include "extension.h"

CJSONExtension g_json_ext;

SMEXT_LINK(&g_json_ext);

cell_t ObjectConstructor(IPluginContext* p_context, const cell_t* params)
{
	aru::CJSONObject *j = new aru::CJSONObject;

	Handle_t h = handlesys->CreateHandle(
		g_json_ext.json_object_type_,
		j,
		p_context->GetIdentity(),
		myself->GetIdentity(),
		nullptr
	);
	if (!h)
	{
		delete j;
	}
	return h;
}
cell_t ObjectParseFromFile(IPluginContext* p_context, const cell_t* params)
{
	// sourcepawn: bool(Handle json, const char[] path)
	
	// get handle
	aru::CJSONObject* obj = nullptr;
	HandleSecurity sec(p_context->GetIdentity(), myself->GetIdentity());
	if (
		HandleError err = handlesys->ReadHandle(params[1], g_json_ext.json_object_type_, &sec, (void**)&obj);
		err != HandleError_None
		)
	{
		return p_context->ThrowNativeError("%x %d", params[1], err);
	}

	// get path
	char* path = nullptr;
	p_context->LocalToString(params[2], &path);

	// parse from file
	std::ifstream ifs;
	if (ifs.open(path, std::ios::in); !ifs.is_open())
	{
		return p_context->ThrowNativeError("invalid path");
	}
	obj->ParseFromFile(ifs);
	ifs.close();

	return true;
}

cell_t ObjectParseFromString(IPluginContext* p_context, const cell_t* params)
{
	return 0;
}

template<typename T>
cell_t ObjectGet(IPluginContext* p_context, const cell_t* params)
{
	// sourcepawn: T(Handle json, char[] json_ptr)

	// get handle
	aru::CJSONObject *obj = nullptr;
	HandleSecurity sec(p_context->GetIdentity(), myself->GetIdentity());
	if (
		HandleError err = handlesys->ReadHandle(params[1], g_json_ext.json_object_type_, &sec, (void**)&obj);
		err != HandleError_None
	)
	{
		return p_context->ThrowNativeError("%x %d", params[1], err);
	}

	// get json pointer
	char *json_ptr = nullptr;
	p_context->LocalToString(params[2], &json_ptr);

	// get T in json by json pointer
	return static_cast<cell_t>(obj->Get<T>(json_ptr));
}

template <>
cell_t ObjectGet<std::string>(IPluginContext* p_context, const cell_t* params)
{
	// sourcepawn: int(Handle json, char[] json_ptr, char[] buffer, int maxlength)

	// get handle
	aru::CJSONObject* obj = nullptr;
	HandleSecurity sec(p_context->GetIdentity(), myself->GetIdentity());
	if (
		HandleError err = handlesys->ReadHandle(params[1], g_json_ext.json_object_type_, &sec, (void**)&obj);
		err != HandleError_None
	)
	{
		return p_context->ThrowNativeError("%x %d", params[1], err);
	}

	// get json pointer
	char *json_ptr = nullptr;
	p_context->LocalToString(params[2], &json_ptr);

	// get string in json by json pointer
	size_t num_written = 0;
	p_context->StringToLocalUTF8(params[3], params[4], obj->Get<std::string>(json_ptr).c_str(), &num_written);
	return static_cast<cell_t>(num_written);
}


const sp_nativeinfo_t my_natives[] = {
	{"Aru_JSONObject.Aru_JSON", ObjectConstructor},
	{"Aru_JSONObject.GetBool", ObjectGet<bool>},
	{"Aru_JSONObject.GetFloat", ObjectGet<float>},
	{"Aru_JSONObject.GetInt", ObjectGet<int>},
	{"Aru_JSONObject.GetString", ObjectGet<std::string>},
	{"Aru_JSONObject.ParseFromFile", ObjectParseFromFile},
	//{"Aru_JSONObject.ParseFromString", ObjectParseFromString},
	
	{nullptr, nullptr}
};
void CJSONExtension::SDK_OnAllLoaded()
{
	json_object_type_ = g_pHandleSys->CreateType(
		"Aru_JSON",
		&json_type_handler_,
		0,
		nullptr,
		nullptr,
		myself->GetIdentity(),
		nullptr
	);

	//sharesys->AddNatives(myself, my_natives);
}

void CJSONExtension::SDK_OnUnload()
{
	g_pHandleSys->RemoveType(
		json_object_type_,
		myself->GetIdentity()
	);
}