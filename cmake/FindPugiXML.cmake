#Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com>

find_library(PUGIXML_LIBRARIES
             NAMES pugixml
             DOC "The PugiXML library")

find_path(PUGIXML_INCLUDE_DIR 
          NAMES pugixml.hpp
          HINTS /usr/include /usr/local/include
          DOC "The PugiXML include directory")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pugixml DEFAULT_MSG PUGIXML_LIBRARIES PUGIXML_INCLUDE_DIR)
mark_as_advanced(PUGIXML_INCLUDE_DIR PUGIXML_LIBRARIES)