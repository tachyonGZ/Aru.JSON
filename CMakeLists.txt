cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (
	"Aru.JSON"
	VERSION 1.0.0
	DESCRIPTION "Aru.JSON"
	LANGUAGES CXX
)

get_filename_component(build_root ".." ABSOLUTE)

# git clone -b 1.12-dev https://github.com/alliedmodders/sourcemod.git sourcemod-1.12-dev
# Can be a symlink to your Window's drive system but IntelliSense won't figure it out
if(IS_DIRECTORY ${build_root}/sourcemod-1.12-dev)
	set(SM "${build_root}/sourcemod-1.12-dev")
	MESSAGE(STATUS "Found SourceMod directory at ${SM}")
else()
	MESSAGE(FATAL_ERROR "Couldn't find SourceMod SDK at ")
endif()

if(IS_DIRECTORY ${build_root}/hl2sdk)
	set (HL2SDK "${build_root}/hl2sdk")
	MESSAGE(STATUS "Found HL2SDK directory at ${HL2SDK}")
elseif()
	MESSAGE(FATAL_ERROR "Couldn't find hl2sdk at ")
endif()

# git clone -b 1.12-dev https://github.com/alliedmodders/sourcepawn.git sourcepawn-1.12-dev
if(IS_DIRECTORY ${build_root}/sourcepawn-1.12-dev)
	set(SOURCEPAWN_SDK "${build_root}/sourcepawn-1.12-dev")
	MESSAGE(STATUS "Found sourcepawn directory at ${SOURCEPAWN_SDK}")
elseif()
	MESSAGE(FATAL_ERROR "Couldn't find sourcepawn at ")
endif()

if(IS_DIRECTORY ${build_root}/amtl-master)
	set(AMTL_SDK "${build_root}/amtl-master")
	MESSAGE(STATUS "Found amtl directory at ${SOURCEPAWN_SDK}")
elseif()
	MESSAGE(FATAL_ERROR "Couldn't find amtl at ")
endif()

add_subdirectory ("extension")
