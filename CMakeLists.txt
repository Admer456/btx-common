
## C++17 for NVRHI
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( BTX_COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

option( BTX_COMMON_WITH_RHI "Build ElegyRhi too if working with graphics. Else just use its headers" OFF )

if ( BTX_COMMON_WITH_RHI )
	add_subdirectory( extern/elegy-rhi )
endif()

## Set up adm-utils
add_subdirectory( extern/adm-utils )

set( BTX_COMMON_SOURCES
	${BTX_COMMON_DIR}/common/assetmanager/IModel.hpp
	${BTX_COMMON_DIR}/common/assetmanager/ModelUtilities.hpp
	${BTX_COMMON_DIR}/common/assetmanager/ModelUtilities.cpp
	${BTX_COMMON_DIR}/common/assetmanager/RenderData.hpp
	${BTX_COMMON_DIR}/common/assetmanager/RenderData.cpp
	${BTX_COMMON_DIR}/common/interfaces/ICore.hpp
	${BTX_COMMON_DIR}/common/interfaces/IConsole.hpp
	${BTX_COMMON_DIR}/common/interfaces/IConsoleListener.hpp
	${BTX_COMMON_DIR}/common/interfaces/IEngine.hpp
	${BTX_COMMON_DIR}/common/interfaces/IFileSystem.hpp
	${BTX_COMMON_DIR}/common/interfaces/IInput.hpp
	${BTX_COMMON_DIR}/common/interfaces/IMaterialManager.hpp
	${BTX_COMMON_DIR}/common/interfaces/IModelManager.hpp
	${BTX_COMMON_DIR}/common/interfaces/IPluginSystem.hpp
	${BTX_COMMON_DIR}/common/interfaces/plugins/IApplication.hpp
	${BTX_COMMON_DIR}/common/interfaces/plugins/IPlugin.hpp
	${BTX_COMMON_DIR}/common/interfaces/plugins/IRenderFrontend.hpp
	${BTX_COMMON_DIR}/common/console/CVar.hpp
	${BTX_COMMON_DIR}/common/console/CVar.cpp
	${BTX_COMMON_DIR}/common/core/IWindow.hpp
	${BTX_COMMON_DIR}/common/pluginsystem/PluginLibrary.hpp
	${BTX_COMMON_DIR}/common/pluginsystem/PluginLibrary.cpp
	${BTX_COMMON_DIR}/common/pluginsystem/PluginLibraryMetadata.hpp
	${BTX_COMMON_DIR}/common/pluginsystem/PluginLibraryMetadata.cpp
	${BTX_COMMON_DIR}/common/pluginsystem/PluginList.hpp
	${BTX_COMMON_DIR}/common/rendering/Common.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderBatch.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderEntity.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderLight.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderModel.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderTexture.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderView.hpp
	${BTX_COMMON_DIR}/common/rendering/IRenderVolume.hpp
	${BTX_COMMON_DIR}/common/EngineConfig.hpp
	${BTX_COMMON_DIR}/common/EngineConfig.cpp
	${BTX_COMMON_DIR}/common/GameMetadata.hpp
	${BTX_COMMON_DIR}/common/GameMetadata.cpp
	${BTX_COMMON_DIR}/common/Precompiled.hpp 
	CACHE INTERNAL "" )

## Folder organisation
source_group( TREE ${BTX_COMMON_DIR} FILES ${BTX_COMMON_SOURCES} )

## BtxCommon.lib
add_library( BtxCommon STATIC ${BTX_COMMON_SOURCES} )

## Include adm-utils and elegy-rhi
## elegy-rhi is only gonna have its headers included,
## the engine will build and link against it
target_include_directories( BtxCommon PUBLIC
	${BTX_COMMON_DIR}
	extern/adm-utils/src
	extern/elegy-rhi/include
	extern/elegy-rhi/nvrhi/include )

## Link against adm-utils and make every subsequent library do that
target_link_libraries( BtxCommon PUBLIC AdmUtils )

## Precompiled headers
target_precompile_headers( BtxCommon PRIVATE
	${BTX_COMMON_DIR}/common/Precompiled.hpp )
