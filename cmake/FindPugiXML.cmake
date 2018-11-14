#Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com>

find_library(
    PUGIXML_LIBRARIES
    NAMES pugixml
    PATHS ${PUGIXML_INSTALL_DIR}
    PATH_SUFFIXES x64 x86
)

find_path(
    PUGIXML_INCLUDE_DIRS
    NAMES pugixml.hpp
    PATHS ${PUGIXML_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pugixml DEFAULT_MSG PUGIXML_LIBRARIES PUGIXML_INCLUDE_DIRS)
mark_as_advanced(PUGIXML_INCLUDE_DIRS PUGIXML_LIBRARIES)
