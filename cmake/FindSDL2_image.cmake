#Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com>

find_library(SDL2_IMAGE_LIBRARIES
             NAMES sdl2_image
             PATHS /lib /usr/lib /usr/local/lib
             PATH_SUFFIXES x64 x86)

find_path(SDL2_IMAGE_INCLUDE_DIRS
          NAMES sdl2_image.h
          PATHS /include /usr/include /usr/local/include)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sdl2_image DEFAULT_MSG SDL2_IMAGE_LIBRARIES SDL2_IMAGE_INCLUDE_DIRS)
mark_as_advanced(SDL2_IMAGE_LIBRARIES SDL2_IMAGE_INCLUDE_DIRS)
