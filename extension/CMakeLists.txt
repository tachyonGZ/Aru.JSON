add_library(
	extension
	SHARED
	"extension.cpp"
	"${SM}/public/smsdk_ext.cpp"
	"CJSONObject.cpp")

find_package(nlohmann_json)

set_target_properties(extension PROPERTIES LIBRARY_OUTPUT_NAME "${CMAKE_PROJECT_NAME}.ext")
set_target_properties(extension PROPERTIES CXX_STANDARD 20)
target_compile_options(extension PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)
target_link_options(extension PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)

target_compile_definitions(extension
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>: 
				GNUC -D_LINUX -DPOSIX -Dstricmp=strcasecmp 
				-D_stricmp=strcasecmp -D_snprintf=snprintf
				-D_vsnprintf=vsnprintf -DHAVE_STDINT_H
				$<$<CONFIG:Debug>: 
					-DDEBUG 
				>
				$<$<CONFIG:Release>: 
					-DNDEBUG 
				>
			>
)



target_link_libraries(
	extension 
	PRIVATE
	-static-libgcc
	-static-libstdc++
)

if(nlohmann_json_FOUND)
	target_link_libraries(extension PRIVATE nlohmann_json::nlohmann_json)
else(nlohmann_json_FOUND)
	message(FATAL_ERROR "nlohmann_json not found")
endif(nlohmann_json_FOUND)

target_include_directories(
	extension 
	PUBLIC  
	"${SM}/public" 
	"${SM}/public/extensions"
	"${SOURCEPAWN_SDK}/include"
	"${AMTL_SDK}"
	"${AMTL_SDK}/amtl"
	"." 
	".."
)