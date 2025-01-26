#include "extension.h"

CJSONExtension g_json_ext;

SMEXT_LINK(&g_json_ext);

cell_t ObjectConstructor(IPluginContext* p_context, const cell_t* params)
{
	CJSONObject *j = new CJSONObject;

	Handle_t h = handlesys->CreateHandle(
		g_json_ext.json_object_type_,
		j,
		p_context->GetIdentity(),
		myself->GetIdentity(),
		nullptr
	);
}
cell_t ObjectParseFromFile(IPluginContext* p_context, const cell_t* params)
{

}

cell_t ObjectParseFromString(IPluginContext* p_context, const cell_t* params)
{
	
}

const sp_nativeinfo_t my_natives[] = {
	{"Aru_JSON.Aru_JSON", ObjectConstructor},
	{"Aru_JSON.ParseFromFile", ObjectParseFromFile},
	{"Aru_JSON.ParseFromString", ObjectParseFromString},
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

	sharesys->AddNatives(myself, my_natives);
}

void CJSONExtension::SDK_OnUnload()
{
	g_pHandleSys->RemoveType(
		json_object_type_,
		myself->GetIdentity()
	);
}