#Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com>

find_library(
  SDL2_LIBRARIES
  NAMES sdl2 sdl2main
  PATHS /lib /usr/lib /usr/local/lib D:/Libraries/SDL2/lib
  PATH_SUFFIXES x64 x86
)

find_path(
  SDL2_INCLUDE_DIRS
  NAMES SDL.h
  PATHS /include /usr/include /usr/local/include D:/Libraries/SDL2/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sdl2 DEFAULT_MSG SDL2_LIBRARIES SDL2_INCLUDE_DIRS)
mark_as_advanced(SDL2_LIBRARIES SDL2_INCLUDE_DIRS)
