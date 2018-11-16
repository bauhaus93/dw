#Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com>

set(SDL2_LIB_SEARCH_PATH ${SDL2_INSTALL_DIR}/lib)
set(SDL2_INCLUDE_SEARCH_PATH ${SDL2_INSTALL_DIR}/include)

find_library(
  SDL2_LIBRARIES
  NAMES sdl2 SDL2
  PATHS ${SDL2_LIB_SEARCH_PATH}
  PATH_SUFFIXES x64 x86
)

find_path(
  SDL2_INCLUDE_DIRS
  NAMES SDL.h
  PATHS ${SDL2_INCLUDE_SEARCH_PATH}
  PATH_SUFFIXES SDL2 sdl2
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sdl2 DEFAULT_MSG SDL2_LIBRARIES SDL2_INCLUDE_DIRS)
mark_as_advanced(SDL2_LIBRARIES SDL2_INCLUDE_DIRS)
