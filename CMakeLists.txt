cmake_minimum_required(VERSION 3.10)
project(dwarfs CXX)

macro(add_sources)
	file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
	foreach(_src ${ARGN})
		if(_relPath)
			file(TO_NATIVE_PATH "${_relPath}/${_src}" _nativePath)
		else()
			file(TO_NATIVE_PATH ${_src} _nativePath)
		endif()
		set_property(TARGET dwfs APPEND PROPERTY SRC_LIST ${_nativePath})
	endforeach()
endmacro()

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(EXEC_NAME "dwarfs")
set(LIB_NAME "dwfs")
set(PYTHON_ENV_DIR ${CMAKE_BINARY_DIR}/python_env)

set(SDL2_INSTALL_DIR "D:/Libraries/SDL2" CACHE STRING "Choose SDL2 installation path"  FORCE)
set(SDL2_IMAGE_INSTALL_DIR "D:/Libraries/SDL2_image" CACHE STRING "Choose SDL2_image installation path" FORCE)
set(PUGIXML_INSTALL_DIR "D:/Libraries/pugixml" CACHE STRING "Choose pugixml installation path" FORCE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_PREFIX_PATH / /usr /usr/local)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose build type" FORCE)
endif()

add_executable(${EXEC_NAME} "src/Main.cpp")
add_library(${LIB_NAME} "")
target_link_libraries(${EXEC_NAME} ${LIB_NAME})

#message(STATUS CMAKE_CXX_COMPILER_ID)
if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${LIB_NAME} PRIVATE -Wall -fmax-errors=1 -Werror)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${LIB_NAME} PRIVATE -Wall -ferror-limit=1 -Werror)
elseif (MSVC)
    target_compile_options(${LIB_NAME} PRIVATE /W4 /MP)
endif()

add_subdirectory(src)

get_property(SRCS TARGET ${LIB_NAME} PROPERTY SRC_LIST)
target_sources(${LIB_NAME} PRIVATE ${SRCS})

target_include_directories(${EXEC_NAME} PRIVATE src)
target_include_directories(${LIB_NAME} PRIVATE src)

target_link_libraries(${LIB_NAME} PRIVATE ${CMAKE_DL_LIBS})

find_package(SDL2 REQUIRED)
target_link_libraries(${LIB_NAME} PRIVATE ${SDL2_LIBRARIES})
target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${EXEC_NAME} SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
target_link_libraries(${LIB_NAME} PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${EXEC_NAME} SYSTEM PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

find_package(PugiXML REQUIRED)
target_link_libraries(${LIB_NAME} PRIVATE ${PUGIXML_LIBRARIES})
target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${PUGIXML_INCLUDE_DIRS})
target_include_directories(${EXEC_NAME} SYSTEM PRIVATE ${PUGIXML_INCLUDE_DIRS})

add_custom_target(python-env
	   	  COMMAND python3 -m venv ${PYTHON_ENV_DIR} &&
			  source ${PYTHON_ENV_DIR}/bin/activate &&
			  pip install --upgrade pip &&
			  pip install -r requirements.txt
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/resource_generation/)

add_custom_target(atlas
		  COMMAND source ${PYTHON_ENV_DIR}/bin/activate &&
			  src/resource_generation/generate.py
			  	--xml-file resources/atlas.xml
				--result-dir ${CMAKE_BINARY_DIR}/
				--render-script src/resource_generation/render/render_object.py
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/)

add_dependencies(atlas python-env)

add_custom_target(archivate-resources
			COMMAND tar -zcvf resources.tar.gz --exclude='*.blend1' resources/
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(extract-resources
			COMMAND tar -xvzf resources.tar.gz
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(setup
			COMMAND "")
add_dependencies(setup extract-resources)
add_dependencies(setup atlas)
