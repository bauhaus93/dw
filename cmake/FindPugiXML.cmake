#Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com>

set(PUGIXML_LIB_SEARCH_PATH ${PUGIXML_INSTALL_DIR}/lib)
set(PUGIXML_INCLUDE_SEARCH_PATH ${PUGIXML_INSTALL_DIR}/include)

find_library(
    PUGIXML_LIBRARIES
    NAMES pugixml
    PATHS ${PUGIXML_LIB_SEARCH_PATH}
    PATH_SUFFIXES x64 x86
)

find_path(
    PUGIXML_INCLUDE_DIRS
    NAMES pugixml.hpp
    PATHS ${PUGIXML_INCLUDE_SEARCH_PATH}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pugixml DEFAULT_MSG PUGIXML_LIBRARIES PUGIXML_INCLUDE_DIRS)
mark_as_advanced(PUGIXML_INCLUDE_DIRS PUGIXML_LIBRARIES)
